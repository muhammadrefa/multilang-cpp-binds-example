// Cleaner requires Java 9+

package binding;

import java.lang.ref.Cleaner;

public final class NativeCleaner {

    public static final Cleaner INSTANCE = Cleaner.create();

    private NativeCleaner() {
    }
}
