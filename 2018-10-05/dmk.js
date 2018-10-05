const _ = require("lodash")
const n = 1000000000
console.log(`${n} ${n} 1 2 3 4 20000`)
const getRange = () => {
    let l = _.random(1, n)
    let r = _.random(1, n)
    if (l > r) {
        let t = l
        l = r
        r = t
    }
    return [l, r]
}
for (let i = 0; i < 10000; i++) {
    const x = _.random(1, 10 ** 9)
    const y = _.random(1, 10 ** 9)
    console.log(`1 ${x} ${y} ${_.random(1, 1 ** 9)}`)
}
for (let i = 0; i < 10000; i++) {
    const x = getRange()
    const y = getRange()
    console.log(`2 ${x[0]} ${y[0]} ${x[1]} ${y[1]}`)
}
