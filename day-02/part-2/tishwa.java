class Solution {

    private static String solve(String input) {
		/**
		 * Find the first two words with exactly one letter different
		 * @input a list of words
		 * @return the letters the two matching words have in common
		 */
		String wordA, wordB, same;
        String[] words = input.split("\n");
		int diff;
		for (int i = 0; i < words.length - 1; i++) {
			for (int j = i + 1; j < words.length; j++) {
				wordA = words[i];
				wordB = words[j];
				same = "";
				diff = 0;
				for (int l = 0; l < wordA.length(); l++) {
					if (wordA.charAt(l) != wordB.charAt(l)) {diff++;}
					else {same += wordA.charAt(l);}
					if (diff > 1) {break;}
				}
				if (diff == 1) {return same;}
			}
		}
		return "not found";
    };

    public static void main(String[] args) {
        String input = args[0];
        long startTime = System.currentTimeMillis();
        String result = solve(input);
        System.out.println("_duration: " + (System.currentTimeMillis() - startTime) + "\n" + result);
    }
}
