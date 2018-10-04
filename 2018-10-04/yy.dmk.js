const _ = require("lodash")
const [n, m] = [300, 300]
console.log(`${n} ${m}`)
console.log(
    [...Array(n).keys()].map(() =>
        [...Array(m).keys()].map(() =>
            _.random(1, 10000)
        ).join(' ')
    ).join('\n')
)
const q = 1000000
console.log(`${q}`)
console.log([...Array(q).keys()].map(() => {
    let x0 = _.random(1, n)
    let x1 = _.random(1, n)
    if(x0 > x1){
        let t = x0
        x0 = x1
        x1 = t
    }
    let y0 = _.random(1, m)
    let y1 = _.random(1, m)
    if(y0 > y1){
        let t = y0
        y0 = y1
        y1 = t
    }
    return [x0, y0, x1, y1].join(' ')
}).join('\n'))