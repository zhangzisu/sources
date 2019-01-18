const _ = require("lodash")
const n = 100000
const m = 100000
console.log(n, m)
console.log([...Array(n)].map(() => _.random(n, n)).join(' '))
console.log([...Array(m)].map(() => {
    let op = _.random(1, 2), l = _.random(1, n), r = _.random(1, n)
    if (l > r) {
        let t = l
        l = r
        r = t
    }
    let x = op == 1 ? n / 2 : n / 2 + 1
    return [op, l, r, x].join(' ')
}).join('\n'))