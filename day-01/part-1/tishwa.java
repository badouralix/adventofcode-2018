class Solution {
    // BEWARE: your main class MUST be named Solution

    private static String solve(String input) {
        /**
		 * gives the sum of each line
		 * @param a list of int written as Strings, with their sign as first char
		 * for instance: {"+12", "-300"}
		 * @return the sum of each line
		 * for instance: 300 - 12 = 288
		 */
		int sum = 0;
		for (String line : input.split("\n")) {
			sum += Integer.parseInt(line);
		}
		return Integer.toString(sum);
    };

    public static void main(String[] args) {
        String input = args[0];
        long startTime = System.currentTimeMillis();
        String result = solve(input);
        System.out.println("_duration: " + (System.currentTimeMillis() - startTime) + "\n" + result);
    }
}
