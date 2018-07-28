#!/usr/local/bin/python3

import os
import subprocess
from subprocess import check_output, STDOUT, PIPE, Popen
from shutil import copyfile
from test_general import *
import random
import sys

TIMEOUT = 0.5
COREWAR1 = "./ocorewar"
DUMP_FLAG1 = "-s"
COREWAR2 = "../corewar"
DUMP_FLAG2 = "-dump"
VALID_CHAMPS_DIR = "compiled_champs/valid_champs"
INVALID_CHAMPS_DIR = "compiled_champs/invalid_champs"
NUM_OF_CHAMPS = 4

def print_block(block):
	for line in block:
		print(line)

def exec_corewar(cycles, champs):
	com1 = "{}".format(COREWAR1, )
	com2 = "{}".format(COREWAR2, )
	for champ in champs:
		com1 += " " + champ
		com2 += " " + champ
	com1 += " " + DUMP_FLAG1 + " " + str(cycles) + " > d1"
	com2 += " " + DUMP_FLAG2 + " " + str(cycles) + " > d2"
	print(com1)
	p = Popen(com1, stdin=PIPE, shell=True)
	try:
		while p.poll() is None:
			p.stdin.write(b"\n")
	except BrokenPipeError:
		pass
	print(com2)
	p = Popen(com2, stdin=PIPE, shell=True)
	try:
		while p.poll() is None:
			p.stdin.write(b"\n")
	except BrokenPipeError:
		pass

def exec_champ(command):
	p = Popen([command, ""], stdin=PIPE, stdout=PIPE, stderr=PIPE, shell=True)
	print(command)

	stdout, stderr = p.communicate()
	result = str(stdout).split("0x0000")
	for i, block in enumerate(result):
		if i != 0:
			result[i] = "0x0000" + result[i]
		result[i] = result[i].split("\\n")
	return result

def exec_my_vm(command):
	lines = []
	print(command)
	p = Popen([command, ""], stdin=PIPE, stdout=PIPE, stderr=PIPE, shell=True)
	while p.poll() is None:
		p.stdin.write(b"\n")
		p.stdin.flush()
		stdout = str(p.stdout.readline())
		lines.append(stdout)
	lines = "".join(lines)
	result = []
	blocks = lines.split("0x0000")
	result.append(blocks[0].replace("'b'", "").split("\\n"))
	for block in blocks[1:]:
		block = "0x0000" + block
		block = block.replace("'b'", "")
		block = block.split("\\n")
		result.append(block)
	return result

def compare_results(res1, res2):
	res1_len, res2_len = len(res1), len(res2)
	if res1_len != res2_len:
		print("Coreware outputs has different blocks num! {} and {}".format(res1_len, res2_len))
	for block_idx in range(min(len(res1), len(res2))):
		block1_len, block2_len = len(res1[block_idx]), len(res2[block_idx])

		if block1_len != block2_len:
			print("Blocks {} has different lengths! {} and {}".format(block_idx, block1_len, block2_len))
			ans = input("Print blocks? type y if so: ")
			if ans == 'y':
				print_block(res1[block_idx])
				print("------------------------------------------------")
				print_block(res2[block_idx])
			
		for line_idx in range(min(block1_len, block2_len)):
			if res1[block_idx][line_idx] != res2[block_idx][line_idx]:
				print("WRONG LINE NUMBER {} IN {} BLOCK!!".format(line_idx, block_idx))
				ans = input("Print lines? type y if so: ")
				if ans == 'y':
					print(res1[block_idx][line_idx])
					print(res2[block_idx][line_idx])

def main():
	if len(sys.argv) < 2:
		print("Usage: ./vm_execution_test <number of cycles for dump>")
		return
	try:
		cycles = int(sys.argv[1])
	except Exception:
		print("Wrong number")
		return
	champs = get_all_file_names(VALID_CHAMPS_DIR, ".cor")
	choosen = []
	for i in range(NUM_OF_CHAMPS):
		_ = random.choice(champs)
		while (_ in choosen):
			_ = random.choice(champs)
		choosen.append(_)
	#choosen = ['compiled_champs/valid_champs/Rainbow_dash.cor', 'compiled_champs/valid_champs/turtle.cor', 'compiled_champs/valid_champs/darksasuke.cor', 'compiled_champs/valid_champs/mise_a_jour_windows95.cor']
	print(choosen)
	exec_corewar(cycles, choosen)
	res1 = []
	res2 = []
	for line in open("d1", "r"):
		res1.append(line)
	for line in open("d2", "r"):
		res2.append(line)
	res1 = "".join(res1).split("0x0000")
	res1 = ["0x0000" + block for block in res1]
	res1 = [block.split("\n") for block in res1]
	res2 = "".join(res2).split("0x0000")
	res2 = ["0x0000" + block for block in res2]
	res2 = [block.split("\n") for block in res2]
	os.remove("d1")
	os.remove("d2")
	compare_results(res1, res2)

main()
