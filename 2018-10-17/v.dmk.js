const generate = require("randomstring").generate;

const n = 30
const k = 30
console.log(`${n} ${k}`)
console.log(generate({ length: n, charset: "WB" }));