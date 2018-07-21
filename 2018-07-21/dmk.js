const _ = require('lodash')

const n = 100
const m = 100

console.log(`${n} ${m}`)

let d = []
for(let x = 1;x <= n;x++)
    d.push(_.random(2, 10))

console.log(d.join(' '))

for(let x = 1;x <= m;x++){
    let op = _.random(1, 2)
    if(op == 1){
        let l = _.random(1, n)
        let r = _.random(1, n)
        if(l > r){
            let t = l
            l = r
            r = t
        }
        console.log(`${op} ${l} ${r} ${_.random(2, 10)}`);
    }else{
        let l = _.random(1, n)
        let r = _.random(1, n)
        if(l > r){
            let t = l
            l = r
            r = t
        }
        console.log(`${op} ${l} ${r}`);
    }
}