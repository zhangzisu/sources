const _ = require("lodash")
const n = 2000
const m = 2000
console.log(n, m, 10 ** 18)
console.log([...Array(n)].map(() => _.random(1, Number.MAX_SAFE_INTEGER)).join(' '))
for (let i = 0; i < m; i++) {
    console.log(2, 1, n)
}