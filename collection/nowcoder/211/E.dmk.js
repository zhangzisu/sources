const _ = require("lodash")
const n = 200000
console.log(`${n} ${n}`)
console.log([...Array(n).keys()].map(() => _.random(0, 2 ** 20 - 1)).join(' '))
for (let i = 0; i < n; i++) {
    let l = _.random(1, n)
    let r = _.random(1, n)
    if (l > r) {
        let t = l
        l = r
        r = t
    }
    let v = _.random(0, 20)
    console.log(`${_.random(1, 5)} ${l} ${r} ${v}`)
}