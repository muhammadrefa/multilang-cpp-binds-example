using MyLib;

void calculator_check()
{
    var val = 0;

    // initialise calculator
    using var calc = new Calculator();

    // addition
    val = calc.Add(1, 1);
    Console.WriteLine($"1 + 1 = {val}");

    // check ops num
    val = calc.CntOpsDone();
    Console.WriteLine($"ops done {val}");

    // subtraction
    val = calc.Sub(4, 3);
    Console.WriteLine($"4 - 3 = {val}");
    val = calc.Sub(1, 4);
    Console.WriteLine($"1 - 4 = {val}");

    // check ops num
    val = calc.CntOpsDone();
    Console.WriteLine($"ops done {val}");

    // reset
    val = calc.ResetCounter();
    Console.WriteLine($"counter resetted! last count {val}");

    // check ops num
    val = calc.CntOpsDone();
    Console.WriteLine($"ops done {val}");

    // 1 addition
    val = calc.Add(100, 120);
    Console.WriteLine($"100 + 120 = {val}");

    // check ops num
    val = calc.CntOpsDone();
    Console.WriteLine($"ops done {val}");
}

void circbuff_check()
{
    var length = 0;

    // initialise circbuff
    using var buf = new CircularBuffer(10);

    // insert 3
    byte[] data1 = {(byte)'a', (byte)'b', (byte)'c', (byte)'d'};
    length = buf.Put(data1, 3);
    Console.WriteLine($"put {length} filled {buf.GetLength()}");

    // insert 5
    byte[] data2 = {(byte)'1', (byte)'2', (byte)'3', (byte)'4', (byte)'5'};
    length = buf.Put(data2);
    Console.WriteLine($"put {length} filled {buf.GetLength()}");

    // get 4
    byte[] data = buf.Get(4);
    Console.WriteLine($"get {data.Length} filled {buf.GetLength()} data {BitConverter.ToString(data)}");

    // insert 5
    byte[] data3 = {(byte)'a', (byte)'b', (byte)'c', (byte)'d', (byte)'e'};
    length = buf.Put(data3);
    Console.WriteLine($"put {length} filled {buf.GetLength()}");

    // insert 3
    try
    {
        length = buf.Put(data2, 3);
        Console.WriteLine($"put {length} filled {buf.GetLength()}");
    }
    catch (OverflowException)
    {
        Console.WriteLine($"Overflow Exception!");
    }

    // clean
    length = buf.Clean();
    Console.WriteLine($"cleaned {length}! filled {buf.GetLength()}");
}

void animal_check()
{
    // create animal1
    using var animal1 = new Animal();
    animal1.Name = "specimen1";
    animal1.Speak();

    // create animal2
    using var animal2 = new Animal("specimen2");
    animal2.Speak(3);

    // adopt a dog
    using var dog = new Dog("Pluto");
    dog.Speak();;
    for (int i=0; i<7; ++i)
    {
        if (dog.Fetch())
            Console.WriteLine($"{dog.Name} fetched the stick!");
        else
            Console.WriteLine($"{dog.Name} did not fetch the stick!");
    }
    Console.WriteLine($"{dog.Name} energy: {dog.GetEnergy()}");
    dog.Sleep();
    if (dog.Fetch())
        Console.WriteLine($"{dog.Name} fetched the stick!");
    else
        Console.WriteLine($"{dog.Name} did not fetch the stick!");
    
    // adopt a cat
    using var cat = new Cat("Pretty");
    cat.Speak(2);
    cat.Fight(false);
    cat.Fight(true);
    cat.Fight(true);
    cat.Fight(false);
    if (cat.StillAlive())
        Console.WriteLine($"{cat.Name} still alive");
    else
        Console.WriteLine($"{cat.Name} died");
    for (int i=0; i<9; ++i)
        cat.Fight(true);
    if (cat.StillAlive())
        Console.WriteLine($"{cat.Name} still alive");
    else
        Console.WriteLine($"{cat.Name} died");

    // adopt a tiger (?)
    using var tiger = new Tiger("Tigris");
    tiger.Speak(3);
    tiger.Fight(false);
    tiger.Fight(true);
    tiger.Fight(true);
    tiger.Fight(false);
    if (tiger.StillAlive())
        Console.WriteLine($"{tiger.Name} still alive");
    else
        Console.WriteLine($"{tiger.Name} died");
    Console.WriteLine($"{tiger.Name} hunger level: {tiger.GetHunger()}");
    tiger.Hunt();
    tiger.Hunt();
    Console.WriteLine($"{tiger.Name} hunger level: {tiger.GetHunger()}");
    tiger.Sleep();
    Console.WriteLine($"{tiger.Name} hunger level: {tiger.GetHunger()}");

    // kill them (silently) :(
    // they should have been died when this function returned
}

Console.WriteLine("--- calculator check ---");
calculator_check();
Console.WriteLine();

Console.WriteLine("--- circbuff check ---");
circbuff_check();
Console.WriteLine();

Console.WriteLine("--- animal check ---");
animal_check();
Console.WriteLine();
