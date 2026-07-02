package exceptions;

public class MyLibException
    extends RuntimeException {

    public MyLibException(String message) {
        super(message);
    }
}
