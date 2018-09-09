const _ = require("lodash")
const n = 100000
const k = _.random(1, n)
console.log(`${n} ${k}`)
const d = []
for (let i = 0; i < n; i++)d.push(_.random(1, n))
console.log(d.join(' '))