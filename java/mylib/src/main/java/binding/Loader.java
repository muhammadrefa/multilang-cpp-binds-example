package binding;

public final class Loader {

    private static boolean loaded = false;

    private Loader() {
    }

    public static synchronized void load() {
        if (!loaded) {
            System.loadLibrary("mylibrary_jni");
            loaded = true;
        }
    }
}
