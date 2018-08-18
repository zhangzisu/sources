const _ = require('lodash')
const n = 500000
const m = n - 1
const k = n
console.log(`${n} ${m} ${k}`)

for (let i = 0; i < m; i++) {
    console.log(`${i % n + 1} ${(i + 1) % n + 1}`)
}

for (let i = 0; i < k; i++) {
    console.log(`${i % n + 1} ${(i + 1) % n + 1} ${1000000000}`)
}