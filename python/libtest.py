from mylib.calculator import Calculator
from mylib.circularbuffer import CircularBuffer


def calculator_check():
    # initialise calculator
    calc = Calculator()

    # addition
    val = calc.add(1, 1)
    print(f"1 + 1 = {val}")
    val = calc.add(2, 3)
    print(f"2 + 3 = {val}")

    # check ops num
    val = calc.cnt_ops_done()
    print(f"ops done {val}")

    # subtraction
    val = calc.sub(4, 3)
    print(f"4 - 3 = {val}")
    val = calc.sub(1, 4)
    print(f"1 - 4 = {val}")

    # check ops num
    val = calc.cnt_ops_done()
    print(f"ops done {val}")

    # reset
    val = calc.reset_counter()
    print(f"counter resetted! last count {val}")

    # check ops num
    val = calc.cnt_ops_done()
    print(f"ops done {val}")

    # 1 addition
    val = calc.add(100, 120)
    print(f"100 + 120 = {val}")

    # check ops num
    val = calc.cnt_ops_done()
    print(f"ops done {val}")



def circbuff_check():
    # initialise circbuff
    buf = CircularBuffer(10)

    # insert 3
    length = buf.put(b"abcd", 3)
    print(f"put {length} filled {buf.get_length()}")

    # insert 5
    length = buf.put(b"12345")
    print(f"put {length} filled {buf.get_length()}")

    # get 4
    data = buf.get(4)
    print(f"get {len(data)} filled {buf.get_length()} data {data}")

    # insert 5
    length = buf.put(b"abcde")
    print(f"put {length} filled {buf.get_length()}")

    # insert 3
    try:
        length = buf.put(b"123")
        print(f"put {length} filled {buf.get_length()}")
    except OverflowError as e:
        print(f"Exception! ({e})")

    # clean
    length = buf.clean()
    print(f"cleaned {length}! filled {buf.get_length()}")


if __name__ == "__main__":
    print("--- calculator check ---")
    calculator_check()
    print()

    print("--- circbuff check ---")
    circbuff_check()
    print()
