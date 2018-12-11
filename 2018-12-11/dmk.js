const { generate } = require("randomstring")

const g = (length) => {
    return generate({ length, charset: 'abcde' })
}

console.log(g(20))
console.log(g(20))
console.log(20)
for (let i = 0; i < 20; i++) {
    console.log(g(1) + '->' + g(2))
}