const _ = require('lodash')
const n = 200000
const q = 30
const m = 100

console.log(`${n} ${q}`)

for (let _n = 0; _n < n; _n++)
    console.log(_.random(-1000000000, 1000000000))

for (let _q = 0; _q < q; _q++)
    console.log(_.random(80, 100))