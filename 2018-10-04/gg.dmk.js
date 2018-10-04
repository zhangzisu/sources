const _ = require("lodash")
const n = 500000
const l = _.random(500000 - 100, 500000)
const x0 = _.random(0, 10 ** 9)
const a = _.random(0, 10 ** 9)
const b = _.random(0, 10 ** 9)
console.log(`${n} ${l} ${x0} ${a} ${b}`)