const _ = require("lodash")
const n = 200000
const m = 200000
const q = 200000
console.log(`${n} ${m}`)
for (let i = 1; i < n; i++)console.log(`${i} ${i + 1}`);
for (let i = 1; i <= m; i++)console.log(`${_.random(1, n)} ${_.random(1, n)}`)
console.log(`${q}`)
for (let i = 1; i <= q; i++) {
    const v = _.random(1, n)
    const k = _.random(1, m)
    console.log(`${v} ${k}`)
}