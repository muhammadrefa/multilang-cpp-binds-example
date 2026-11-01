import mylib.Calculator;
import mylib.CircularBuffer;
import mylib.animal.Animal;
import mylib.animal.Dog;
import mylib.animal.Cat;
import mylib.animal.Tiger;
import mylib.numberprocessor.NumberProcessor;
import mylib.numberprocessor.ProcessAdd2;

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
    
    static void animal_check()
    {
        // create animal1
        Animal animal1 = new Animal();
        animal1.setName("specimen1");
        animal1.speak();

        // create animal2
        Animal animal2 = new Animal("specimen2");
        animal2.speak(3);

        // adopt a dog
        Dog dog = new Dog("Pluto");
        dog.speak();
        for (int i=0; i<7; ++i)
        {
            if (dog.fetch())
                System.out.println(dog.getName() + " fetched the stick!");
            else
                System.out.println(dog.getName() + " did not fetch the stick!");
        }
        System.out.println(dog.getName() + " energy: " + dog.getEnergy());
        dog.sleep();
        if (dog.fetch())
            System.out.println(dog.getName() + " fetched the stick!");
        else
            System.out.println(dog.getName() + " did not fetch the stick!");
    
        // adopt a cat
        Cat cat = new Cat("Pretty");
        cat.speak(2);
        cat.fight(false);
        cat.fight(true);
        cat.fight(true);
        cat.fight(false);
        if (cat.stillAlive())
            System.out.println(cat.getName() + " still alive");
        else
            System.out.println(cat.getName() + " died");
        for (int i=0; i<9; ++i)
            cat.fight(true);
        if (cat.stillAlive())
            System.out.println(cat.getName() + " still alive");
        else
            System.out.println(cat.getName() + " died");

        // adopt a tiger (?)
        Tiger tiger = new Tiger("Tigris");
        tiger.speak(3);
        tiger.fight(false);
        tiger.fight(true);
        tiger.fight(true);
        tiger.fight(false);
        if (tiger.stillAlive())
            System.out.println(tiger.getName() + " still alive");
        else
            System.out.println(tiger.getName() + " died");
        System.out.println(tiger.getName() + " hunger level: " + tiger.getHunger());
        tiger.hunt();
        tiger.hunt();
        System.out.println(tiger.getName() + " hunger level: " + tiger.getHunger());
        tiger.sleep();
        System.out.println(tiger.getName() + " hunger level: " + tiger.getHunger());


        // kill them :(
        animal1.close();
        animal2.close();
        dog.close();
        cat.close();
        tiger.close();
    }

    static void number_processor_check()
    {
        ProcessAdd2 add2 = new ProcessAdd2();
        add2.setNumber(10);
        add2.printNumber();
        add2.process();
        add2.printNumber();

        JProcessAdd7 add7 = new JProcessAdd7();
        add7.setNumber(10);
        add7.printNumber();
        add7.process();
        add7.printNumber();

        // try upcast and downcast
        System.out.println("-- upcast test");
        NumberProcessor add7_up = add7;
        add7_up.printNumber();
        System.out.println("-- downcast test");
        JProcessAdd7 add7_dn = JProcessAdd7.fromNumberProcessor(add7_up, JProcessAdd7.class);
        add7_dn.hello();
        add7_dn.printNumber();

        add7_dn.close();
        add7_up.close();
        add7.close();
        add2.close();
    }

    public static void main(String[] args) {
        System.out.println("--- calculator check ---");
        calculator_check();
        System.out.println();

        System.out.println("--- circbuff check ---");
        circbuff_check();
        System.out.println();

        System.out.println("--- animal check ---");
        animal_check();
        System.out.println();

        System.out.println("--- number processor check ---");
        number_processor_check();
        System.out.println();
    }
}
