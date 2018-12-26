const _ = require("lodash")
const n = 1000

console.log(n, 1)
const fa = [...Array(n - 1).keys()].map(x => _.random(1, x + 1))
const leaves = [...Array(n).keys()].map(x => x + 1).filter(x => !fa.includes(x))
for (let i = 2; i <= n; i++) {
    console.log(i, fa[i - 2])
}
const k = _.random(1, leaves.length)
console.log(1, k, ..._.shuffle(leaves))
