import java.util.List;
import java.util.ArrayList;

class Solution {

    private static String solve(String input) {
		/**
		 * find out the length of the polymer once it has reacted
		 * @input a string of random letters with random capitalization
		 * @return length of the corresponding polymer once reacted
		 */
        Polymer polymer = new Polymer(input);
        polymer.reactAll();
        return Integer.toString(polymer.units.size());
    };

    public static void main(String[] args) {
        String input = args[0];
        long startTime = System.currentTimeMillis();
        String result = solve(input);
        System.out.println("_duration: " + (System.currentTimeMillis() - startTime) + "\n" + result);
    }
}

class Polymer {
    List<Character> units = new ArrayList<Character>();

    public Polymer(String units) {
        for (String unit : units.split("")) {
            this.units.add(unit.charAt(0));
        }
    }

    public void reactAll() {
        int i = 0;
        while (i < units.size() - 1) {
            char currentUnit = units.get(i);
            char nextUnit = units.get(i + 1);
            if (shouldReact(currentUnit, nextUnit)) {
                // if there is a reaction, remove the corresponding units
                // and go back once (to check if there are new reactions)
                units.remove(i + 1);
                units.remove(i);
                if (i > 0) {i--;}
            } else {
                // otherwise, go on
                i++;
            }
        }
    }

    private boolean shouldReact(char unitA, char unitB) {
        // check if two units should react
        if (Character.isUpperCase(unitA) != Character.isUpperCase(unitB)) {
            if (Character.toUpperCase(unitA) == Character.toUpperCase(unitB)) {
                return true;
            }
        }
        return false;
    }
}