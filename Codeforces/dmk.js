const _ = require('lodash')
const n = 100000
const m = 300000
console.log(`${n}`)
let d = []
d.push(999999999)
for (let _n = 1; _n < n; _n++)d.push(1000000000 - _n)
console.log(d.join(' '))
console.log(`${m}`)
for (let _m = 0; _m < m; _m++) {
    let l = _.random(1, n - 1)
    let r = _.random(l + 1, n)
    console.log(`${l} ${r}`)
}