const _ = require("lodash")
const n = 1000
const m = 12
console.log(n)
for (let i = 2; i <= n; i++) {
    console.log(_.random(1, i - 1), i)
}
console.log(m)
for (let i = 2; i <= m; i++) {
    console.log(_.random(1, i - 1), i)
}