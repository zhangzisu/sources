const n = 100000
const m = 50000
const _ = require("lodash")

console.log(`${n} ${m}`)
const data = [...Array(n).keys()].map(() => _.random(1, 1000000000))
console.log(data.join(' '))