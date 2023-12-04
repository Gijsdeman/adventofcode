import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class day6 {
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("2022/day6.input");
        Scanner scanner = new Scanner(file);
        String input = scanner.next();

        int result = 0;
        int startMarkerSize = 14;
        for (int i = 0; i < input.length() - startMarkerSize; i++) {
            String subString = input.substring(i, i + startMarkerSize);
            if (subString.chars().distinct().count() == startMarkerSize) {
                result = i + startMarkerSize;
                break;
            }
        }
        System.out.println(result);
    }
}