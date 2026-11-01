import mylib.numberprocessor.NumberProcessorProxy;

public class JProcessAdd7 extends NumberProcessorProxy {
    public void process() {
        int number = getNumber();
        number += 7;
        setNumber(number);
    }

    @Override
    public void printNumber() {
        System.out.print("Java print number -> ");
        super.printNumber();
    }

    public void hello() {
        System.out.println("Hello from Java!");
    }
}
