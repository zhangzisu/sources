const _ = require("lodash")
const n = 100000
console.log(`${n}`)
const f = []
for (let i = 1; i < n; i++)f.push(i + 1)
console.log(f.join(' '))
const v = []
for (let i = 0; i < n; i++)v.push(100000)
console.log(v.join(' '))