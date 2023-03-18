import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;

import static java.lang.Character.isLetter;

public class FileIO {
    static private HashSet<String> word_map;
    static private ArrayList<String> words;
    static private int words_cnt = 0;

    static private void read_file(String filepath) {
        try (BufferedReader br = new BufferedReader(new FileReader(filepath))) {
            String line;
            while ((line = br.readLine()) != null) {
                parse_words(line);
            }
        } catch (IOException e) {
            System.err.println("Failed to read file: " + e.getMessage());
        }
    }

    static private void parse_words(String context) {   /* 解析单词的函数 */
        int size = context.length();
        int i = 0;
        String word = "";
        StringBuilder sb = new StringBuilder();
        while (i < size) {
            if (isLetter(context.charAt(i))) {
                sb.append(context.charAt(i));
            } else if (sb.length() != 0) {
                store_word(sb.toString());
                sb.setLength(0);
            }
            i++;
        }
        if (sb.length() != 0) {
            store_word(sb.toString());
        }
    }

    static private void store_word(String word) {     /* 储存单词的函数 */
        word = word.toLowerCase();
        if (!word_map.contains(word)) {    //添加单词操作
            words.add(word);
            word_map.add(word);
        }
    }

    static public String[] get_words() {
        String[] new_words = new String[words.size()];
        new_words = words.toArray(new_words);
        return new_words;
    }
}
