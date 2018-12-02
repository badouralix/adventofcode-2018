/**
 * @param {string} s puzzle input in string format
 * @returns {string} solution flag
 */
const run = s => {
  // Your code goes here
  const [twos, threes] = s
    .split("\n")
    .map(line =>
      line.split("").reduce((letters, letter) => {
        letters[letter] = 1 + (letters[letter] || 0);
        return letters;
      }, {})
    )
    .reduce(
      (acc, line) => {
        let findTwo = false;
        let findThree = false;
        Object.values(line).forEach(count => {
          if (count === 2) {
            findTwo = true;
          }
          if (count === 3) {
            findThree = true;
          }
        });
        if (findThree) {
          acc[1] += 1;
        }
        if (findTwo) {
          acc[0] += 1;
        }
        return acc;
      },
      [0, 0]
    );
  return twos * threes;
};

console.log(run(process.argv[2]));
