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
        stderr = stdout
        stdout = ""
    else:
        os.remove(corpath)

    return (stdout, stderr)

def run_champs(champ_file, src_dir, asm1, asm2):
    res = [champ_file]
    if asm1 != None:
        asm_out = run_champ(champ_file, src_dir, asm1)
        if asm_out:
            res.append(asm_out)
        else:
            return None
    if asm2 != None:
        asm_out = run_champ(champ_file, src_dir, asm2)
        if asm_out:
            res.append(asm_out)
        else:
            return None
    return res

def run_and_print_champs_in_dir(asm1, asm2, champ_dir):
    res = iter_file(champ_dir, run_champs, asm1, asm2)
    res = filter(lambda x: x, res)
    for i, champ_data in enumerate(res):
        print("\x1b[1;33;40m---------------------CHAMPION: '{}'----------------\x1b[0m".format(champ_data[0]))
        if asm1:
            data = champ_data[1]
            if (len(data[0]) > 0):
                print("asm1 {} \x1b[1;32;40mcompiled\x1b[0m and responsed:\n{}".format(asm1, data[0]))
            else:
                print("asm1 {} \x1b[1;31;40mgot error\x1b[0m and said:\n{}".format(asm2, data[1]))

        if asm2:
            data = champ_data[2 - (1 if not asm1 else 0)]
            if (len(data[0]) > 0):
                print("asm2 {} \x1b[1;32;40mcompiled\x1b[0m and responsed:\n{}".format(asm1, data[0]))
            else:
                print("asm2 {} \x1b[1;31;40mgot error\x1b[0m and said:\n{}".format(asm2, data[1]))

run_and_print_champs_in_dir(ASM1, ASM2, INVALID_CHAMPS_DIR)
run_and_print_champs_in_dir(ASM1, ASM2, VALID_CHAMPS_DIR)
