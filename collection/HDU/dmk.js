const _ = require('lodash')

const n = 100000
const m = 100000
console.log(`${n} ${m}`)

console.log([...Array(n).keys()].map(() => _.random(0, 1)).join(' '))

console.log(
    [...Array(m).keys()].map(() => {
        let u = _.random(1, n)
        let v = _.random(1, n)
        while (u == v) {
            u = _.random(1, n)
            v = _.random(1, n)
        }
        let w = _.random(1, 2 ** 31 - 1)
        return `${u} ${v} ${w}`;
    }).join('\n')
)

const q = 100000
console.log(q)

console.log(
    [...Array(q).keys()].map(() => {
        if (_.random(0, 1)) {
            return `Asksum ${_.random(0, 1)} ${_.random(0, 1)}`
        } else {
            return `Change ${_.random(1, n)}`
        }
    }).join('\n')
)