const _ = require("lodash")
let m = 100000
console.log(`${m} ${0}`)
for (let i = 0; i < m; i++) {
    let u = _.random(0, 8)
    let v = _.random(0, 8)
    let p = _.random(1, 2000)
    let w = _.random(1, 1000000000)
    console.log(`${p} ${u} ${v} ${w}`)
}
const q = 5
console.log(`${q}`)
for (let i = 0; i < q; i++) {
    const u = _.random(0, 8)
    const v = _.random(0, 8)
    const k = 2000
    const d = [u, v, k]
    for (let j = 0; j < k; j++) {
        d.push(j + 1)
        d.push(j + 1)
    }
    console.log(d.join(' '))
}