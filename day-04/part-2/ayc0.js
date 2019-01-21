/**
 * @param {string} s puzzle input in string format
 * @returns {string} solution flag
 */
const run = s => {
  let currentGuardId = null;
  let maxSleep = 0;
  let guards = {};
  s.split("\n")
    .map(line => {
      const date = new Date(line.substring(1, 17));
      const command = line.substring(19);
      return [date, command];
    })
    .sort((dateA, dateB) => dateA[0] - dateB[0])
    .forEach(([date, command]) => {
      if (command[0] === "G") {
        currentGuardId = command.substring(7).replace(" begins shift", "");
        if (guards[currentGuardId] === undefined) {
          guards[currentGuardId] = { minutes: new Array(60).fill(0), maxSlept: 0, minute: 0, id: currentGuardId };
        }
        // Init
        return;
      }
      if (command[0] === "f") {
        lastAsleep = date;
        return;
      }
      if (command[0] === "w") {
        const sleepTime = parseInt((date - lastAsleep) / 60000, 10);
        const currentGuard = guards[currentGuardId];

        const asleep = lastAsleep.getMinutes();
        for (let index = 0; index < sleepTime; index++) {
          const min = (index + asleep) % 60;
          const nbSlept = (currentGuard.minutes[min] += 1);

          if (nbSlept > currentGuard.maxSlept) {
            currentGuard.maxSlept = nbSlept;
            currentGuard.minute = min;
          }
        }

        lastAsleep = null;
        return;
      }
    });

  const guard = Object.values(guards).reduce((acc, cur) => (cur.maxSlept > acc.maxSlept ? cur : acc));
  return guard.minute * Number(guard.id);
};

let start = Date.now();
let answer = run(process.argv[2]);

console.log("_duration:" + (Date.now() - start).toString());
console.log(answer);
