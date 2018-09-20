const _ = require("lodash")
const fs = require("fs")
const output = []

const n = 100000
const q = 100000

output.push(n)
const a = []
for (let i = 0; i < n; i++)a.push(_.random(1, 1000000000))
output.push(a.join(' '))
for (let i = 0; i < n; i++) {
    const l = _.random(1, n)
    const r = _.random(l, n)
    output.push(`${l} ${r}`)
}
output.push(q)
for (let i = 0; i < n; i++) {
    const op = _.random(1, 2)
    const l = _.random(1, n)
    if (op == 1) {
        const v = _.random(1, 1000000000)
        output.push(`${op} ${l} ${v}`)
    } else {
        const r = _.random(l, n)
        output.push(`${op} ${l} ${r}`)
    }
}
output.push('')

fs.writeFileSync("sum.in", output.join('\n'))