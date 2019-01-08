const _ = require('lodash')

const n = 100000
const m = 100000

console.log(`${n} ${m}`)

let d = []
for (let x = 0; x < n; x++)d.push(_.random(1, 1000))
console.log(d.join(' '))

for (let x = 1; x < n; x++)
    console.log(`${x} ${x + 1}`);

for (let x = 0; x < m; x++) {
    console.log(`${_.random(0, 1)} ${_.random(1, n)} ${_.random(1, 1000)}`)
}