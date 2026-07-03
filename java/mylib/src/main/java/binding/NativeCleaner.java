// Java 8 does not supports Cleaner

package binding;

import java.lang.ref.Cleaner;

public final class NativeCleaner {

    public static final Cleaner INSTANCE = Cleaner.create();

    private NativeCleaner() {
    }
}
