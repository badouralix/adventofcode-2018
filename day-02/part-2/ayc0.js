/**
 * @param {string} stringA
 * @param {string} stringB
 * @returns {[number, number[]]} solution flag
 */
const diff = (stringA, stringB) => {
  if (stringA.length !== stringB.length) {
    return [NaN, [-1]];
  }
  let nbDiff = 0;
  const posDiff = [];
  for (let index = 0; index < stringA.length; index++) {
    const charA = stringA[index];
    const charB = stringB[index];
    if (charA !== charB) {
      nbDiff += 1;
      posDiff.push(index);
    }
  }
  return [nbDiff, posDiff];
};

/**
 * @param {string} s puzzle input in string format
 * @returns {string} solution flag
 */
const run = s => {
  const lines = s.split("\n");
  for (let i = 0; i < lines.length; i++) {
    for (let j = i; j < lines.length; j++) {
      const [nbDiff, posDiff] = diff(lines[i], lines[j]);
      if (nbDiff === 1) {
        return lines[i].substring(0, posDiff[0]) + lines[i].substring(posDiff[0] + 1, lines[i].length);
      }
    }
  }
};

console.log(run(process.argv[2]));
