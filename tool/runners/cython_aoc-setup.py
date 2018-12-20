import sys
from socket import gethostname

from distutils.core import setup
from Cython.Build import cythonize

build_dir = sys.argv.pop()
script_name = sys.argv.pop()

quiet = gethostname() not in ['Aymeric-MBP.local']

setup(ext_modules=cythonize(script_name,
                            build_dir=build_dir,
                            quiet=quiet,
                            compiler_directives={'language_level': 3}))

# annotate=True enables generation of the html annotation file
