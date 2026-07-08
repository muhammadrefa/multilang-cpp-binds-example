import mylib.Calculator;
import mylib.CircularBuffer;

import java.nio.BufferOverflowException;
import java.util.Arrays;

public final class Main {

    static void calculator_check() {
        int val = 0;

        // initialise calculator
        Calculator calc = new Calculator();

        // addition
        val = calc.add(1, 1);
        System.out.println("1 + 1 = " + val);

        // check ops num
        val = calc.cntOpsDone();
        System.out.println("ops done " + val);

        // subtraction
        val = calc.sub(4, 3);
        System.out.println("4 - 3 = " + val);
        val = calc.sub(1, 4);
        System.out.println("1 - 4 = " + val);

        // check ops num
        val = calc.cntOpsDone();
        System.out.println("ops done " + val);

        // reset
        val = calc.resetCounter();
        System.out.println("counter resetted! last count " + val);

        // check ops num
        val = calc.cntOpsDone();
        System.out.println("ops done " + val);

        // 1 addition
        val = calc.add(100, 120);
        System.out.println("100 + 120 = " + val);

        // check ops num
        val = calc.cntOpsDone();
        System.out.println("ops done " + val);

        // close calculator
        calc.close();
    }
    
    static void circbuff_check()
    {
        int length = 0;

        // initialise circbuff
        CircularBuffer buf = new CircularBuffer(10);

        // insert 3
        byte[] data1 = {'a', 'b', 'c', 'd'};
        length = buf.put(data1, 3);
        System.out.println("put " + length + " filled " + buf.getLength());

        // insert 5
        byte[] data2 = {'1', '2', '3', '4', '5'};
        length = buf.put(data2);
        System.out.println("put " + length + " filled " + buf.getLength());

        // get 4
        byte[] data = buf.get(4);
        System.out.println("get " + data.length + " filled " + buf.getLength() + " data " + Arrays.toString(data));

        // insert 5
        byte[] data3 = {'a', 'b', 'c', 'd', 'e'};
        length = buf.put(data3);
        System.out.println("put " + length + " filled " + buf.getLength());

        // insert 3
        try
        {
            length = buf.put(data2, 3);
            System.out.println("put " + length + " filled " + buf.getLength());
        }
        catch (BufferOverflowException ex)
        {
            System.out.println("Overflow Exception! " + ex.getMessage());
        }

        // clean
        length = buf.clean();
        System.out.println("cleaned " + length + "! filled " + buf.getLength());

        // close circular buffer
        buf.close();
    }

    public static void main(String[] args) {
        System.out.println("--- calculator check ---");
        calculator_check();
        System.out.println();

        System.out.println("--- circbuff check ---");
        circbuff_check();
        System.out.println();
    }
}
