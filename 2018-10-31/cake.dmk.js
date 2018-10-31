const n = 18
const d = "WXYZ"
const _ = require("lodash")

console.log(n)
for (let i = 0; i < 3; i++) {
    console.log(`${_.random(1, 10)} W X`)
    console.log(`${_.random(1, 10)} W Y`)
    console.log(`${_.random(1, 10)} W Z`)
    console.log(`${_.random(1, 10)} X Y`)
    console.log(`${_.random(1, 10)} X Z`)
    console.log(`${_.random(1, 10)} Y Z`)
}