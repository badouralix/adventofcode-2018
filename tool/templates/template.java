import java.util.Dictionary;
import java.util.Hashtable;
import java.util.List;

class Solution {
    // !!! You have to change the classname
    private static String solve(String input) {
        // Your code goes here
        return "Nothing";
    };

    public static void main(String[] args) {
        String input = args[0];
        long startTime = System.currentTimeMillis();
        String result = solve(input);
        System.out.println("_duration:%f\n" + (startTime - System.currentTimeMillis()));
        System.out.println(result);
    }
}