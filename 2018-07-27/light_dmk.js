const _ = require('lodash')

const n = 100000
const m = 100000

console.log(`${n} ${m}`)
let d = []
for (let i = 1; i < n; i++)
    d.push(524288)
d.push(99999)

console.log(d.join(' '))

for (let i = 0; i < m; i++) {
    let l = 1
    let r = n
    if (_.random(0, 1)) {
        console.log(`1 ${l} ${r} ${2}`);
    } else {
        console.log(`2 ${l} ${r}`);
    }
}