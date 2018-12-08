/**
 * @param {string} s puzzle input in string format
 * @returns {string} solution flag
 */
const run = s => {
  let currentGuardId = null;
  let maxSleepGuardId = null;
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
          guards[currentGuardId] = { total: 0, sleeps: [] };
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
        currentGuard.total += sleepTime;

        if (currentGuard.total > maxSleep) {
          maxSleep = currentGuard.total;
          maxSleepGuardId = currentGuardId;
        }

        currentGuard.sleeps.push([lastAsleep.getMinutes(), sleepTime]);

        lastAsleep = null;
        return;
      }
    });

  let maxSlept = 0;
  let minute = 0;

  const minutes = new Array(60).fill(0);
  guards[maxSleepGuardId].sleeps.forEach(([asleep, length]) => {
    for (let index = 0; index < length; index++) {
      const min = (index + asleep) % 60;
      const nbSlept = (minutes[min] += 1);

      if (nbSlept > maxSlept) {
        maxSlept = nbSlept;
        minute = min;
      }
    }
  });

  return minute * Number(maxSleepGuardId);
};

let start = Date.now();
let answer = run(process.argv[2]);

console.log("_duration:" + (Date.now() - start).toString());
console.log(answer);
