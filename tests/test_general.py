import os
import subprocess
from subprocess import check_output, STDOUT
from shutil import copyfile

def return_file_path_if_ext(file, dir_, check_ext):
    root, ext = os.path.splitext(file)
    if (ext == check_ext):
        return os.path.join(dir_, file)

def iter_file(start_dir, iter_func, *args):
    res = []
    for dir_, dirs, files in os.walk(start_dir):
        for file in files:
            res.append(iter_func(file, dir_, *args))
    return res

def get_all_file_names(start_dir, ext):
    res = iter_file(start_dir, return_file_path_if_ext, ext)
    return list(filter(lambda x: x, res))

def copy_file_if_ext(file, src_dir, cpy_dir, file_ext):
    root, ext = os.path.splitext(file)
    if ext == file_ext:
        copyfile(os.path.join(src_dir, file), os.path.join(cpy_dir, file))

def compile_champ(champ_file, src_dir, asm):
    subprocess.call("{} {}".format(asm, os.path.join(src_dir, champ_file)), shell=True)

def copy_all_files_with_ext_to_dir(start_dir, cpy_dir, file_ext):
    iter_file(start_dir, copy_file_if_ext, cpy_dir, file_ext)

def compile_all_champs(asm, champ_dir):
    iter_file(champ_dir, compile_champ, asm)
