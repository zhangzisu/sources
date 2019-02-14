const _ = require("lodash")

console.log(100)

for (let i = 0; i < 90; i++) {
    let n = 300
    console.log(n)
    while (n--) {
        console.log(_.random(true), _.random(true))
    }
}

for (let i = 0; i < 10; i++) {
    let n = 1000
    console.log(n)
    while (n--) {
        console.log(_.random(true), _.random(true))
    }
}