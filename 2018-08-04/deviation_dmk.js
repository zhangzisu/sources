const _ = require('lodash')

const t = 6
const n = 100000
const maxv = 1000000000

console.log(t)
for (let _t = t; _t; _t--) {
    console.log(n)
    let data = []
    for (let _n = 0; _n < n; _n++)data.push(_.random(1, maxv))
    console.log(data.join(' '))
    let m = _.random(1, n)
    console.log(m)
    let start = _.random(0, n - m)
    data = data.slice(start, start + m)
    console.log(data.join(' '))
    console.log()
}