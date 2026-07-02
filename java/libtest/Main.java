import binding.CalculatorNative;
import binding.refs.IntRef;

public final class Main {

    public static void main(String[] args) {
        long handle = CalculatorNative.create();
        System.out.println("Handle: " + handle);

        IntRef result = new IntRef();
        int status = CalculatorNative.add(handle, 1, 3, result);
        System.out.println("Status: " + status);
        System.out.println("Result: " + result.value);

        status = CalculatorNative.destroy(handle);
        System.out.println("Status: " + status);
    }
}
