const _ = require("lodash")

const n = 100000
console.log(n)
console.log([...Array(n).keys()].map(() => _.random(1, 30000)).join(' '))
