const n = 100000
const m = 100000
const _ = require("lodash")

console.log(n)
console.log([...Array(n - 1).keys()].map(i => `${i + 1} ${i + 2} ${_.random(1, 2)}`).join("\n"))

console.log(m)
console.log([...Array(m).keys()].map(() => `${_.random(1, n)} ${_.random(1, n)} ${_.random(300, 400)}`).join("\n"))
