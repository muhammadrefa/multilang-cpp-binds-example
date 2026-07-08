package mylib.binding.refs;

public final class CharRef {

    public final byte[] value;

    public CharRef(int size) {
        this(new byte[size]);
    }

    public CharRef(byte[] value) {
        this.value = value;
    }
}
