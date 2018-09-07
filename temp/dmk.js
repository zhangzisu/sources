const _ = require("lodash")

const n = 100000
const m = 10
console.log(`${n} ${m}`)

for (let i = 0; i < n; i++)console.log(`${1}`)

for (let i = 1; i < n; i++)console.log(`${i} ${i + 1}`)

for (let i = 0; i < m; i++) {
    console.log(`${3} ${_.random(1, n)} ${_.random(1, n)}`)
}