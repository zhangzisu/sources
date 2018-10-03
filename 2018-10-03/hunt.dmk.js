const n = 100000
const m = 100000
const _ = require("lodash")

console.log(`${n} ${m} 1`)
console.log([...Array(m).keys()].map(() => [_.random(1, n), _.random(1, n)].join(' ')).join('\n'))
console.log(`${_.random(1, n)}`)