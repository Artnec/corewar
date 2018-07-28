#!/usr/local/bin/python3

import os
import subprocess
from subprocess import check_output, STDOUT, PIPE, Popen
from shutil import copyfile
from test_general import *
import random
import sys

def run_valgrind_test(champ_file, src_dir, prog):
    comm = "valgrind --leak-check=full {} {}".format(prog, os.path.join(src_dir, champ_file))
    print(comm)
    try:
        p = check_output(comm, stderr=STDOUT, shell=True, timeout=5)
        print(str(p).split("\\n")[-2])
    except subprocess.TimeoutExpired:
        print("Timeout")
    except Exception as e:
        out = str(e.output)
        print(out.split("\\n")[-2])

if (len(sys.argv) < 2):
    iter_file(".", run_valgrind_test, "../corewar")
elif (sys.argv[1] == '-v'):
    iter_file(".", run_valgrind_test, "../corewar")
elif (sys.argv[1] == '-a'):
    iter_file(".", run_valgrind_test, "../asm")

