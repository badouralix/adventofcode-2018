import java.util.Dictionary;
import java.util.Hashtable;

class Solution {

    private static String solve(String input) {
		/**
		 * get the checksum of a list of codes
		 * @param a list of codes which are random strings like "efmghuxckqldtwjzvitbparnno"
		 * @return the number of codes which have the same char exactly twice
		 * times the number of codes which have the same char exactly thrice
		 */
		int two = 0;
		int three = 0;
		Dictionary<Character, Integer> occurences;
		for (String word : input.split("\n")) {
			occurences = new Hashtable<Character, Integer>();
			int thisTwo = 0;
			int thisThree = 0;
			for (int i = 0; i < word.length(); i++) {
				char letter = word.charAt(i);
				int occurence = occurences.get(letter) != null ? occurences.get(letter) + 1 : 1;
				occurences.put(letter, occurence);
				if (occurence == 2) {thisTwo++;}
				if (occurence == 3) {thisTwo--; thisThree++;}
				if (occurence == 4) {thisThree--;}
			}
			if (thisTwo > 0) two++;
			if (thisThree > 0) three++;
		}
		return Integer.toString(two * three);
    };

    public static void main(String[] args) {
        String input = args[0];
        long startTime = System.currentTimeMillis();
        String result = solve(input);
        System.out.println("_duration: " + (System.currentTimeMillis() - startTime) + "\n" + result);
    }
}
