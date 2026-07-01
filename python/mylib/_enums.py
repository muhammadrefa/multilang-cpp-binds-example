from enum import IntEnum


class Status(IntEnum):
    OK = 0

    UNKNOWN_ERROR = -1
    INVALID_HANDLE = -2
    INVALID_ARGUMENT = -3

    LOGIC_ERROR = -11
    OVERFLOW_ERROR = -12
    RANGE_ERROR = -13

    BUFFER_TOO_SMALL = -51
