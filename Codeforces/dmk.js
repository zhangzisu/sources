const _ = require('lodash')
const n = 1
const m = 100000
const k = 100000
console.log(`${n} ${m} ${k}`)

for (let i = 0; i < n; i++) {
    console.log(`1 1 1`);
}

for (let i = 0; i < m; i++) {
    let x = _.random(1, 100000)
}

for (let i = 0; i < k; i++) {
    console.log(`${i % n + 1} ${(i + 1) % n + 1}`)
}
