#!/usr/local/bin/python3

import os
import subprocess
from subprocess import check_output, STDOUT
from shutil import copyfile
from test_general import *

TIMEOUT = 0.5
COREWAR1 = "./ocorewar"
COREWAR2 = "../corewar"
VALID_CHAMPS_DIR = "compiled_champs/valid_champs"
INVALID_CHAMPS_DIR = "compiled_champs/invalid_champs"

def run_champ(champ_file, src_dir, corewar):
    res = []
    com = "{} {}".format(corewar, os.path.join(src_dir, champ_file))
    try:
        res.append(check_output(com, stderr=STDOUT, shell=True, timeout=TIMEOUT))
    except subprocess.CalledProcessError as e:
        res.append(e.output)
    except subprocess.TimeoutExpired:
        res.append("VM stopped after timeout")
    return res

def run_champs(champ_file, src_dir, corewar1, corewar2):
    res = [champ_file]
    if corewar1 != None:
        res.append(run_champ(champ_file, src_dir, corewar1))
    if corewar2 != None:
        res.append(run_champ(champ_file, src_dir, corewar2))
    return res

def run_and_print_champs_in_dir(corewar1, corewar2, champ_dir):
    res = iter_file(champ_dir, run_champs, corewar1, corewar2)
    for i, champ_data in enumerate(res):
        print("---------------------CHAMPION: '{}'----------------".format(champ_data[0]))
        if corewar1:
            print("corewar1 {} response:\n{}".format(corewar1, champ_data[1][0]))
        if corewar2:
            print("corewar2 {} response:\n{}".format(corewar2, champ_data[2 - (1 if not corewar1 else 0)]))

run_and_print_champs_in_dir(COREWAR1, COREWAR2, VALID_CHAMPS_DIR)
run_and_print_champs_in_dir(COREWAR1, COREWAR2, INVALID_CHAMPS_DIR)
