const generate = require("randomstring").generate;
const n = 50
const m = 50
console.log(`${n} ${m}`)
const d = [...Array(n).keys()].map(_ => generate({ length: m, charset: "01" }));
console.log(d.join('\n'))