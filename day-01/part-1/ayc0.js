const run = s => Function("return 0" + s)();

console.log(run(process.argv[2]));
