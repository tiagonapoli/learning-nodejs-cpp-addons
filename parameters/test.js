const test = require("./build/Release/parameters_addon");

console.log(test);
console.log("Add: ", test.add(1, 2));
console.log("Missing argument: ", test.add(2));
console.log("Wrong argument types: ", test.add(2, "wololo"));
console.log("Null and undefined: ", test.add(null, undefined));

const cb = () => {
  console.log("Called callback");
};

const cb2 = (str) => {
  console.log(`Called callback: ${str}`);
};

test.callCb(cb);
test.callCbWithArgs(cb2, "This is a string");
