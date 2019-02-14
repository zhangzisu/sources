const _ = require("lodash")

let T = 5
console.log(T)

while (T--) {
    let n = 100
    console.log(n)
    while (n--) {
        let x = _.random(true)
        let y = _.random(true)
        let h = _.random(true)
        console.log(x, y, h)
    }
}