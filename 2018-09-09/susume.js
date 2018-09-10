const _ = require("lodash")
const n = 50
const d = 30000

console.log(`${n} ${d}`)
for (let i = 0; i < n; i++) {
    let l = _.random(0, 30000)
    let r = _.random(l, 30000)
    console.log(`${l} ${r}`)
}