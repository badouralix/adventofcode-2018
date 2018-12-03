/**
 * @param {string} s puzzle input in string format
 * @returns {string} solution flag
 */
const run = s => {
  // Your code goes here
  const area = new Map([]);
  const ids = {};
  s.split("\n")
    .map(line => line.match(/#([0-9]+) @ ([0-9]+),([0-9]+): ([0-9]+)x([0-9]+)/))
    .map(match => {
      const id = parseInt(match[1], 10);
      ids[id] = true;
      return {
        id,
        offsetLeft: parseInt(match[2], 10) + 1,
        offsetTop: parseInt(match[3], 10) + 1,
        width: parseInt(match[4], 10),
        height: parseInt(match[5], 10)
      };
    })
    .forEach(claim => {
      for (let i = claim.offsetLeft; i < claim.offsetLeft + claim.width; i++) {
        for (let j = claim.offsetTop; j < claim.offsetTop + claim.height; j++) {
          const key = `${i},${j}`;
          if (!area.has(key)) {
            area.set(key, claim.id);
          } else {
            const id = area.get(key);
            ids[id] = false;
            ids[claim.id] = false;
          }
        }
      }
    });
  for (let id in ids) {
    if (ids[id]) {
      return id;
    }
  }
};

console.log(run(process.argv[2]));
