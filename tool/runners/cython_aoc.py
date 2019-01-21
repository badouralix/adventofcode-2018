import os
import subprocess
import shutil
import importlib

from tool.utils import BColor, resolve_path
from tool.runners.python import SubmissionPy
from tool.runners.exceptions import RuntimeError


class SubmissionPyx(SubmissionPy):

    def __init__(self, file):
        SubmissionPy.__init__(self)
        self.module = None

        setup_path = resolve_path("tool", "runners", "cython_aoc-setup.py")
        script_name = os.path.basename(file)
        script_name_escaped = script_name.replace(".", "_").replace("_pyx", ".pyx")
        build_dir_relative = os.path.join(os.path.dirname(file), script_name.replace(".", "_") + "_build")
        build_dir = resolve_path(build_dir_relative)
        self.build_dir = build_dir

        if not os.path.exists(build_dir):
            os.makedirs(build_dir)
        shutil.copyfile(resolve_path(file), resolve_path(build_dir, script_name_escaped))

        try:
            cmd = "cd %s && python %s build_ext --inplace %s %s" % (build_dir, setup_path, script_name_escaped, build_dir)
            subprocess.check_output(cmd, shell=True).decode()
        except Exception:
            print(BColor.RED + "Could not compile cython %s" % script_name + BColor.ENDC)
            return

        rel_script_path = os.path.join(build_dir_relative, script_name_escaped)
        module_name = ".".join(os.path.normpath(os.path.splitext(rel_script_path)[0]).split(os.sep))
        self.module = importlib.import_module(module_name)

    def language(self):
        return 'pyx'

    def run(self, input):
        if self.module is None:
            return "-"
        try:
            return self.module.run(input)
        except Exception as e:
            print(BColor.RED + "Could not run cython %s" % e + BColor.ENDC)
            raise RuntimeError(e)

    def cleanup(self):
        try:
            shutil.rmtree(self.build_dir)
        except Exception as e:
            print("Could not remove cython build directory:", e)
