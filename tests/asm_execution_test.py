#!/usr/local/bin/python3

import os
import subprocess
from subprocess import check_output, STDOUT, PIPE, Popen
from shutil import copyfile
from test_general import *
import random
import sys

ASM1 = "./oasm"
ASM2 = "../asm"
VALID_CHAMPS_DIR = "not_compiled_champs/valid_champs"
INVALID_CHAMPS_DIR = "not_compiled_champs/invalid_champs"

def run_champ(champ_file, src_dir, asm):
    root, ext = os.path.splitext(champ_file)
    if (ext != '.s'):
        return None
    res = []
    filepath = os.path.join(src_dir, champ_file)
    com = "{} {}".format(asm, filepath)
    p = Popen([com, ""], stdin=PIPE, stdout=PIPE, stderr=PIPE, shell=True)
    stdout, stderr = p.communicate()

    corpath = os.path.join(src_dir, root) + ".cor"
    if not os.path.exists(corpath):
        return None
    champ_bytes = []
    with open(corpath, "rb") as compiled:
        for line in compiled:
            champ_bytes.append(line)
    champ_bytes = b"".join(champ_bytes)     
    os.remove(corpath)
    return champ_bytes

def run_champs(champ_file, src_dir, asm1, asm2):
    res = [champ_file]
    if asm1 != None:
        res.append(run_champ(champ_file, src_dir, asm1))
    if asm2 != None:
        res.append(run_champ(champ_file, src_dir, asm2))
    return res

def run_and_print_champs_in_dir(asm1, asm2, champ_dir):
    res = iter_file(champ_dir, run_champs, asm1, asm2)
    res = filter(lambda x: x, res)
    for i, champ_data in enumerate(res):
        print("\x1b[1;33;40m---------------------CHAMPION: '{}'----------------\x1b[0m".format(champ_data[0]))
        if asm1:
            if not champ_data[1]:
                print("asm1 \x1b[1;31;40m {} doesn't compiled file \x1b[0m".format(asm1))
            else:
                print("asm1 \x1b[1;32;40m {} compiled file \x1b[0m".format(asm1))
        if asm2:
            if not champ_data[2]:
                print("asm2 \x1b[1;31;40m {} doesn't compiled file \x1b[0m".format(asm2))
            else:
                print("asm2 \x1b[1;32;40m {} compiled file \x1b[0m".format(asm2))
        if asm1 and asm2:
            if champ_data[1] == champ_data[2]:
                print("\x1b[1;32;40m Result is identical \x1b[0m")
            else:
                print("\x1b[1;31;40m Result differs! \x1b[0m")

run_and_print_champs_in_dir(ASM1, ASM2, INVALID_CHAMPS_DIR)
run_and_print_champs_in_dir(ASM1, ASM2, VALID_CHAMPS_DIR)
