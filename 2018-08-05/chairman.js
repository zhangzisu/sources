const _ = require('lodash')

const n = 10
const k = 3
const l = 3
console.log(`${n} ${k} ${l}`);
let d = []
for (let _n = 0; _n < n; _n++)d.push(_.random(1, n))
console.log(d.join(' '))
