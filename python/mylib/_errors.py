from ._enums import Status


def check_pointer(result, func, args):
    if not result:
        raise MemoryError(
            f"{func.__name__} returned NULL"
        )

    return result


def check_status(result, func, args):
    if result == Status.OK:
        return result
    if result == Status.INVALID_HANDLE:
        raise ReferenceError(f"{func.__name__} failed: {Status(result).name}")
    if result == Status.INVALID_ARGUMENT:
        raise ValueError(f"{func.__name__} failed: {Status(result).name}")
    if result == Status.OVERFLOW_ERROR:
        raise OverflowError(f"{func.__name__} failed: {Status(result).name}")
    if result == Status.RANGE_ERROR:
        raise IndexError(f"{func.__name__} failed: {Status(result).name}")
    
    raise RuntimeError(f"{func.__name__} failed: {result}")
