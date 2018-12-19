class Solution {
    // BEWARE: your main class MUST be named Solution

    private static String solve(String input) {
        // Your code goes here
        return "Nothing";
    };

    public static void main(String[] args) {
        String input = args[0];
        long startTime = System.currentTimeMillis();
        String result = solve(input);
        System.out.println("_duration: " + (System.currentTimeMillis() - startTime) + "\n" + result);
    }
}
