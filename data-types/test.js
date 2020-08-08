const mod = require("./build/Release/data_types_addon");

console.log(mod);
console.log("incNumber:", mod.incNumber(42.5));

console.log("incInteger:", mod.incInteger(42));
console.log("incInteger:", mod.incInteger(42.5));

console.log("negateBool:", mod.negateBool(true));

console.log("reverseString:", mod.reverseString("Tiago"));
console.log("reverseString:", mod.reverseString(42));
console.log("reverseString:", mod.reverseString({ x: 5 }));

console.log("modifyObject:", mod.modifyObject({}));
console.log("modifyObject:", mod.modifyObject({ y: 20 }));

console.log("mathOps:", mod.mathOpsObject({ x: 10, y: 20 }));
console.log("mathOps:", mod.mathOpsObject({ x: 30 }));
