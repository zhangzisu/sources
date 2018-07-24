const _ = require('lodash')

const T = 5
const N = 20

console.log(T)
for (let t = 0; t < T; t++) {
    console.log(N * 2)
    let x = []
    for (let i = 0; i < N * 2; i++)
        x.push(_.random(1, 40))
    console.log(x.join(' '))
}