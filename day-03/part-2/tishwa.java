import java.util.Map;
import java.util.HashMap;

class Solution {

	private static int[] parseLine(String line) {
		/**
		 * parse a line of the input into usable data
		 * @param a String of the form "#{code} @ {left},{top}: {width}x{height}"
		 * @return an array of int of the form {code, left, top, width, height}
		 */
		String[] parsed = line.split("[ #@,x:]+");
		int code = Integer.parseInt(parsed[1]);
		int left = Integer.parseInt(parsed[2]);
		int top = Integer.parseInt(parsed[3]);
		int width = Integer.parseInt(parsed[4]);
		int height = Integer.parseInt(parsed[5]);
		return new int[] {code, left, top, width, height};
	}

    private static String solve(String input) {
		/**
		 * we have a fabric which is a large matrix (of more than 1000 inches each side)
		 * and a list of claims to use a portion of this fabriq. This method returns the
		 * first claim that does not collide with any other
         * 
		 * @param a list of claims of the form "#{code} @ {left},{top}: {width}x{height}"
		 * @return the code of the first claim that does not collide with any other
		 */
		Map<String, Integer> fabric = new HashMap<String, Integer>();
		Map<Integer, Boolean> codes = new HashMap<Integer, Boolean>();
		for (String line: input.split("\n")) {
			int[] parsed = parseLine(line);
			int code = parsed[0], left = parsed[1], top = parsed[2], width = parsed[3],
					height = parsed[4];
            boolean valid = true;
			for (int i = left; i < left + width; i++) {
				for (int j = top; j < top + height; j++) {
					if (fabric.get(i + "," + j) == null) {
                        // for each inch, specify by which code it has been claimed
						fabric.put(i + "," + j, code);
					} else {
                        // if an inch has already been claimed, then this code can't be the answer
						// and neither can the code that had previously claimed it
						valid = false;
						int otherCode = fabric.get(i + "," + j);
						codes.put(otherCode, false);
					}
				}
			}
			codes.put(code,  valid);
		}
		for (int code: codes.keySet()) {
			// go back through all the codes to get the one that is valid
			if (codes.get(code)) return Integer.toString(code);
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
