const _ = require("lodash")

let T = 1
console.log(T)
while (T--) {
    let n = 100000
    console.log(n)
    /*let vis = new Set()
    while (n--) {
        let x = _.random(1, 5)
        let y = _.random(1, 5)
        while (vis.has(`${x}-${y}`)) {
            x = _.random(1, 5)
            y = _.random(1, 5)
        }
        vis.add(`${x}-${y}`)
        console.log(x, y)
    }*/
    for (let i = 1; i <= n; i++) {
        console.log(i, i)
    }
}