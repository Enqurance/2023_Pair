import java.io.File;

public class CoreAPI {
    static {
        System.load(System.getProperty("user.dir") + File.separator + ".." + File.separator + "bin" + File.separator + "core.dll"); // 加载 DLL 文件
    }

    public static native int genChainsAll(String[] words, int len, String[][] result);
    public static native int genChainWord(String[] words, int len, String[] result, char head, char tail, char reject, boolean enable_loop);
    public static native int genChainChar(String[] words, int len, String[] result, char head, char tail, char reject, boolean enable_loop);
}
