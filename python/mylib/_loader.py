# Library loader
# Load CDLL once, use everywhere


from ctypes import CDLL
from pathlib import Path


_lib = None

def load_library():
    """
    Load the CDLL library once
    :return:
    :rtype:
    """
    global _lib

    if _lib is not None:
        return _lib
    
    lib_dir = Path(__file__).resolve().parent / "native"
    
    _lib = CDLL(str(lib_dir / "libmylibraryc.so"))
    return _lib
