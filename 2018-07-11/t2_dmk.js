let fs = require('fs')
let _ = require('lodash')

const n = 1000000
const m = 1000000
const k = 2 ** 31 - 1

let p = Array.apply(null, Array(n)).map((key, value) => { return value })

let find = (x) => {
    return x == p[x] ? x : p[x] = find(p[x])
}

console.log(`${n} ${m}`)

for (let x = 1; x < n; x++) {
    let u = _.random(n - 1)
    let v = _.random(n - 1)
    while (find(u) == find(v)) {
        u = _.random(n - 1)
        v = _.random(n - 1)
    }
    p[find(u)] = v
    console.log(`${u + 1} ${v + 1} ${_.random(1, k)}`);
}

for (let x = 0; x < m; x++) {
    let u = _.random(n - 1)
    let v = _.random(n - 1)
    while (u == v) {
        u = _.random(n - 1)
        v = _.random(n - 1)
    }
    console.log(`${u + 1} ${v + 1} ${_.random(1, k)} ${_.random(1, k)} ${_.random(1, k)}`)
}