const _ = require("lodash")
const n = 100
const m = 100
console.log(`${n} ${m}`)
console.log([...Array(m).keys()].map(() => `${_.random(1, n)} ${_.random(1, n)}`).join('\n'))
const q = 1000
console.log(q)
console.log([...Array(q).keys()].map(() => `${_.random(1, 10 ** 9)} ${_.random(1, n)} ${_.random(1, n)}`).join('\n'))