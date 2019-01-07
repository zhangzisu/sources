const _ = require("lodash")

const n = 10000
const m = 10000
console.log(n, m)
for (let i = 0; i < m; i++) {
    const op = _.random(1, 4)
    let l = _.random(1, n)
    let r = _.random(1, n)
    if (l > r) {
        let t = l
        l = r
        r = t
    }
    let a = _.random(1, 10000)
    let b = _.random(1, 10000)
    switch (op) {
        case 1:
        case 2:
            console.log(op, l, r, a, b)
            break;
        case 3:
            console.log(op, l, r)
            break;
        case 4:
            console.log(op, l)
            break;
    }
}