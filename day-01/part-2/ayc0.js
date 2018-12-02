/**
 * @param {string} s puzzle input in string format
 * @returns {string} solution flag
 */
const run = s => {
  const list = s.split("\n").map(Number);
  let prev = 0;
  const sums = {};
  let solution = null;
  while (solution === null) {
    prev = list.reduce((acc, current) => {
      const s = acc + current;
      if (s in sums) {
        sums[s] += 1;
      } else {
        sums[s] = 1;
      }
      if (sums[s] === 2 && solution === null) {
        solution = s;
      }
      return s;
    }, prev);
  }
  return solution;
};

console.log(run(process.argv[2]));
