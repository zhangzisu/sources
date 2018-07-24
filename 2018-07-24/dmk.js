const _ = require('lodash')

const n = 1000000
const m = 1000000
const q = 1000000

console.log(`${n} ${m} ${q}`);

let d = []
for (let x = 0; x < n; x++)
    d.push(_.random(1, m))

console.log(d.join(' '))

for(let x = 0;x < q;x++)
    console.log(`${_.random(1, m)} ${_.random(1, m)}`);

