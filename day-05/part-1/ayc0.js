/**
 *
 * @param {string[]} list
 * @returns {boolean}
 */
const remove = list => {
  const length = list.length;
  if (length < 2) {
    return false;
  }
  const char = list[length - 2];
  const nextChar = list[length - 1];
  if (char !== nextChar && char.toLowerCase() === nextChar.toLowerCase()) {
    list.pop();
    list.pop();
    return true;
  }
  return false;
};

/**
 * @param {string} s puzzle input in string format
 * @returns {string} solution flag
 */
const run = s => {
  // Your code goes here
  const pile = [];
  for (let char of s) {
    pile.push(char);
    while (remove(pile)) {}
  }
  return pile.length;
};

let start = Date.now();
let answer = run(process.argv[2]);

console.log("_duration:" + (Date.now() - start).toString());
console.log(answer);
