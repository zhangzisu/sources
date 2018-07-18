const _ = require('lodash')

const N = 200000
const M = 400000
const Q = 0
let max = 0

console.log(1)

console.log(`${N} ${M}`)

for (let i = 0; i < M; i++) {
    let u = _.random(N)
    let v = _.random(N)
    while (u == v) v = _.random(N)
    console.log(`${u} ${v} ${_.random(10000)} ${i}`)
}

console.log(Q)

for(let i = 0;i < Q;i++){
    let u = _.random(N);
    let v = _.random()
}