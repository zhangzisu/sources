const _ = require('lodash')

const n = 100000
const m = 100000

console.log(n)

let p = []
for (let i = 1; i <= n; i++)
    p.push(_.random(0, i - 1))

console.log(p.join(' '))

let vis = {}

console.log(m)

for (let i = 1; i <= m; i++) {
    let t = []
    let x = _.random(0, 1)
    let u = _.random(0, n)
    let v = _.random(0, n - 1)
    if (u == v)
        v++;
    if (x == 0 && !vis[u]) {
        t.push(1)
        t.push(u)
        vis[u] = 1
    } else {
        t.push(2)
        t.push(u)
        t.push(v)
        t.push(_.random(1, n))
        t.push(_.random(0, i - 1))
    }
    console.log(t.join(' '))
}
