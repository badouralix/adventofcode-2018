/**
 * @param {string} s puzzle input in string format
 * @returns {string} solution flag
 */
const run = s => {
  // Your code goes here
  const area = new Map([]);
  const overlap = [];
  s.split("\n")
    .map(line => line.match(/#([0-9]+) @ ([0-9]+),([0-9]+): ([0-9]+)x([0-9]+)/))
    .map(match => ({
      id: parseInt(match[1], 10),
      offsetLeft: parseInt(match[2], 10) + 1,
      offsetTop: parseInt(match[3], 10) + 1,
      width: parseInt(match[4], 10),
      height: parseInt(match[5], 10)
    }))
    .forEach(claim => {
      for (let i = claim.offsetLeft; i < claim.offsetLeft + claim.width; i++) {
        for (let j = claim.offsetTop; j < claim.offsetTop + claim.height; j++) {
          const key = `${i},${j}`;
          if (!area.has(key)) {
            area.set(key, 0);
          }
          const value = area.get(key);
          if (value === 1) {
            overlap.push(key);
          }
          area.set(key, value + 1);
        }
      }
    });
  return overlap.length;
};

console.log(run(process.argv[2]));
