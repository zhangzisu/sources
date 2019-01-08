const _ = require("lodash")
const t = 10000
console.log(`${t}`)
for (let i = 0; i < t; i++) {
    const n1 = 1
    const m1 = 1000000
    console.log(`${n1} ${m1}`)
    const d1 = []
    for (let i = 0; i < n1 * m1; i++)d1.push(_.random(1, 1))
    console.log(d1.join(''))
    const n2 = 1000000
    const m2 = 1
    console.log(`${n2} ${m2}`)
    const d2 = []
    for (let i = 0; i < n2 * m2; i++)d2.push(_.random(1, 1))
    console.log(d2.join(''))
}