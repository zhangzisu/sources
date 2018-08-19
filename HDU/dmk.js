const _ = require('lodash')

const n = 100000
const m = 100000
console.log(1)
console.log(`${n} ${m}`)

let d = []
for (let i = 0; i < n; i++)d.push(_.random(1, n))

for (let i = 0; i < m; i++) {
    let l = _.random(1, n)
    let r = _.random(1, n)
    if (l > r) {
        let t = l
        l = r
        r = t
    }
    if (_.random(0, 1)) {
        console.log(`1 ${l} ${r} ${_.random(1, n)} ${_.random(1, n)}`)
    } else {
        console.log(`2 ${l} ${r} ${_.random(1, r - l + 1)}`)
    }
}