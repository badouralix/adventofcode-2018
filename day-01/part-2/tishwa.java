import java.util.Dictionary;
import java.util.Hashtable;

class Solution {
    // BEWARE: your main class MUST be named Solution

    private static String solve(String input) {
		/**
		 * @param a list of int written as Strings, with their sign as first char
		 * for instance: {"+12", "-300"}
		 * @return the first time a sum is reached twice when adding the values of each line
		 * in an infinite loop
		 */
		Dictionary<Integer, Integer> frequencies = new Hashtable<Integer, Integer>();
		boolean found = false;
		int i = 0;
		int freq = 0;
        String[] inputList = input.split("\n");
		String line;
		while (!found) {
			line = inputList[i % inputList.length];
			freq += Integer.parseInt(line);
			if (frequencies.get(freq) != null) {
				frequencies.put(freq,  2);
				found = true;
			} else {
				frequencies.put(freq,  1);
			}
			i++;
		}
		return Integer.toString(freq);
    };

    public static void main(String[] args) {
        String input = args[0];
        long startTime = System.currentTimeMillis();
        String result = solve(input);
        System.out.println("_duration: " + (System.currentTimeMillis() - startTime) + "\n" + result);
    }
}
