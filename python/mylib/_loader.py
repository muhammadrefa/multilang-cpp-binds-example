# Library loader
# Load CDLL once, use everywhere


import os
import sys

from ctypes import CDLL
from pathlib import Path


_lib: CDLL = None
_dll_dir_handle = None


def _library_path() -> Path:
    lib_dir = Path(__file__).resolve().parent / "native"

    if sys.platform == "win32":
        return lib_dir / "mylibraryc.dll"

    if sys.platform.startswith("linux"):
        return lib_dir / "libmylibraryc.so"

    raise RuntimeError(f"Unsupported platform: {sys.platform}")


def load_library() -> CDLL:
    """
    Load the CDLL library once
    :return:
    :rtype:
    """
    global _lib, _dll_dir_handle

    if _lib is not None:
        return _lib
    
    lib_path = _library_path()
    
    if sys.platform == "win32":
        # Required so Windows can find mine.dll and other dependent DLLs
        _dll_dir_handle = os.add_dll_directory(str(lib_path.parent))
    
    # On Linux, it should be compiled with -Wl,-rpath,'$ORIGIN'
    try:
        _lib = CDLL(str(lib_path))
    except OSError as e:
        print(type(e))
        print(e)
        print(repr(e))
    return _lib
