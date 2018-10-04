const _ = require("lodash")
const n = 1000000
const m = _.random(1, n)
console.log(n, m)
console.log([...Array(n).keys()].map(x => (x & 1) ? 1 : 1000000).join(' '))