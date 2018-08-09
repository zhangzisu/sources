const _ = require('lodash')

const n = 1000
const q = 10000
const maxv = 10000000

console.log(`${n} ${n - 1} ${q}`)

let val = []
for (let _n = 0; _n < n; _n++)val.push(_.random(1, maxv))
console.log(val.join(' '))

for (let _n = 1; _n < n; _n++) {
    console.log(`${_n} ${_n + 1}`);
}

for (let _q = 0; _q < q; _q++) {
    let x = _.random(1, n)
    let y = _.random(1, n)
    console.log(`${_.random(1, 2)} ${x} ${y}`);
}