const _ = require("lodash")
const n = 500000
console.log(n)
console.log([...Array(n).keys()].map(() => _.random(1, 1)).join(' '))