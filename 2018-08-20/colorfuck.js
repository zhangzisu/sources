const _ = require('lodash')

const n = 500
const m = 1000
const v = 500
const q = 100

console.log(`${n} ${m}`)
for (let i = 1; i < n; i++)console.log(`${i} ${i + 1} ${_.random(1, v)}`)
for (let i = n; i <= m; i++) {
    let l = _.random(1, n - 1)
    let r = l + 1
    console.log(`${l} ${r} ${_.random(1, v)}`)
}
console.log(`${q}`)
for (let i = 1; i <= q; i++)console.log(`${_.random(1, n)} ${_.random(1, n)}`)