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

calculator_check();
circbuff_check();
