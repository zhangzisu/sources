const _ = require('lodash')

const t = 1
const n = 10
const m = 1

console.log(`${t}`)
console.log(`${n} ${m}`)

for (let i = 0; i < n; i++)console.log(_.random(1, 2 ** 5))

console.log(`${1} ${n}`)