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
 *
 * @param {string} string
 * @returns {string}
 */
const buildPolymer = string => {
  const pile = [];
  for (let char of string) {
    pile.push(char);
    while (remove(pile)) {}
  }
  return pile.join("");
};

/**
 * @param {string} string
 * @param {string} ignoreChar
 * @returns {string} solution flag
 */
const shortestPolymer = (string, ignoreChar) => {
  // Your code goes here
  const pile = [];
  for (let char of string) {
    if (char.toLowerCase() !== ignoreChar) {
      pile.push(char);
      while (remove(pile)) {}
    }
  }
  return pile.length;
};

/**
 * @param {string} s puzzle input in string format
 * @returns {string} solution flag
 */
const run = s => {
  // Your code goes here
  const string = buildPolymer(s);
  const set = new Set(string.toLowerCase());
  const sizes = [];
  for (const char of set) {
    sizes.push(shortestPolymer(string, char));
  }
  return Math.min(...sizes);
};

let start = Date.now();
let answer = run(process.argv[2]);

console.log("_duration:" + (Date.now() - start).toString());
console.log(answer);
