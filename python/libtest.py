from mylib.calculator import Calculator
from mylib.circularbuffer import CircularBuffer
from mylib.animal import Animal, Dog, Cat, Tiger


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


def animal_check():
    # create animal1
    animal1 = Animal()
    animal1.name = "specimen1"
    animal1.speak()

    # create animal2
    animal2 = Animal("specimen2")
    animal2.speak(3)

    # adopt a dog
    dog = Dog("Pluto")
    dog.speak()
    for i in range(7):
        if dog.fetch():
            print(f"{dog.name} fetched the stick!")
        else:
            print(f"{dog.name} did not fetch the stick!")
    print(f"{dog.name} energy: {dog.get_energy()}")
    dog.sleep()
    if dog.fetch():
        print(f"{dog.name} fetched the stick!")
    else:
        print(f"{dog.name} did not fetch the stick!")
    
    # adopt a cat
    cat = Cat("Pretty")
    cat.speak(2)
    cat.fight(False)
    cat.fight(True)
    cat.fight(True)
    cat.fight(False)
    if cat.still_alive():
        print(f"{cat.name} still alive")
    else:
        print(f"{cat.name} died")
    for i in range(9):
        cat.fight(True)
    if cat.still_alive():
        print(f"{cat.name} still alive")
    else:
        print(f"{cat.name} died")

    # adopt a tiger (?)
    tiger = Tiger("Tigris")
    tiger.speak(3)
    tiger.fight(False)
    tiger.fight(True)
    tiger.fight(True)
    tiger.fight(False)
    if tiger.still_alive():
        print(f"{tiger.name} still alive")
    else:
        print(f"{tiger.name} died")
    print(f"{tiger.name} hunger level: {tiger.get_hunger()}")
    tiger.hunt()
    tiger.hunt()
    print(f"{tiger.name} hunger level: {tiger.get_hunger()}")
    tiger.sleep()
    print(f"{tiger.name} hunger level: {tiger.get_hunger()}")
    
    # kill them (silently) :(
    # they should have been died when this function returned



if __name__ == "__main__":
    print("--- calculator check ---")
    calculator_check()
    print()

    print("--- circbuff check ---")
    circbuff_check()
    print()

    print("--- animal check ---")
    animal_check()
    print()
