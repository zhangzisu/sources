const _ = require("lodash")
const n = 100000
const r = _.random(1, n)
const l = _.random(0, r)
const R = _.random(1, n)
const L = 0

console.log(`${l} ${r} ${L} ${R}`)