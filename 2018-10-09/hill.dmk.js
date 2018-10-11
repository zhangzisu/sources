const _ = require("lodash")
const n = 20
const m = 300
console.log(`${n} ${m}`)
for (let i = 0; i < m; i++) {
    let l = _.random(1, n - 1)
    let r = l + 1
    console.log(`${l} ${r} ${_.random(0, 50)}`)
}