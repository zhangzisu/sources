const _ = require('lodash')

const n = 200000
const m = 200000
const k = 200000
const t = 0

console.log(`${n} ${m} ${k} ${t}`)

for(let x = 0;x < m;x++){
    console.log(`${_.random(1, n)} ${_.random(1, n)}`)
}

for(let x = 0;x < k;x++){
    let l = _.random(1, m)
    let r = _.random(1, m)
    if(l > r){
        let t = l
        l = r
        r = t
    }
    console.log(`${l} ${r}`)
}