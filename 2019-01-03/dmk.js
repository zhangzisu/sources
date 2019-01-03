const _ = require("lodash")
const n = 200000
const m = 200000

console.log(n, m)
console.log([...Array(n)].map(() => {
    let l = _.random(1, 10 ** 9)
    let r = _.random(1, 10 ** 9)
    return l < r ? `${l} ${r}` : `${r} ${l}`
}).join('\n'))
console.log([...Array(m)].map(() => {
    let l = _.random(1, 10 ** 9)
    let r = _.random(1, 10 ** 9)
    return (l < r ? `${l} ${r}` : `${r} ${l}`) + ' ' + _.random(1, 10 ** 9)
}).join('\n'))