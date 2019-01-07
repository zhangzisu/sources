const _ = require('lodash')
const n = 1000000
const k = 2000
console.log(`${n} ${k}`)

let d = []
for (let i = 0; i < n; i++) {
    let x = _.random(1, 10)
    d.push(x)
}

console.log(d.join(' '))