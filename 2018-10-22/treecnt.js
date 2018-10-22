const _ = require("lodash")
const n = 100000
console.log(n)
for (let i = 2; i <= n; i++) {
    console.log(`${i} ${_.random(1, i - 1)}`)
}