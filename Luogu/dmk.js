const _ = require("lodash")
const n = 100000
const m = 100000
console.log(n, m, 20)
console.log([...Array(n + 1)].map(() => _.random(1, 1000000000)).join(' '))
console.log([...Array(m + 1)].map(() => _.random(1, 1000000000)).join(' '))