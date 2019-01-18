const _ = require("lodash")
const n = 1000000
const m = 1000000
console.log(n, m)
console.log([...Array(n)].map(() => _.random(1, 1000000)).join(' '))
console.log([...Array(m)].map(() => _.random(1, 1000000)).join(' '))