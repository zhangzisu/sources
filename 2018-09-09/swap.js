const _ = require("lodash")
const n = 3
const a = []
for (let i = 0; i < n; i++)a.push(_.random(1, 100))
console.log(`${n}`)
console.log(a.join(' '))