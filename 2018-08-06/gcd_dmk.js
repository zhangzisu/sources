const _ = require('lodash')

const n = 100000
const m = 100000

console.log(`${n} ${m}`)
let d = []
for (let _n = 0; _n < n; _n++)
    d.push(_.random(2, 100000))
console.log(d.join(' '))

for(let _m=0;_m<m;_m++){
    let l = _.random(1, n)
    let r = _.random(1, n)
    let g = _.random(2, 100000)
    if(l > r){
        let x = l
        l = r
        r = x
    }
    console.log(`${g} ${l} ${r}`)
}