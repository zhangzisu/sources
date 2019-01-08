const _ = require("lodash")

const n = 5

console.log(n)
console.log(..._.shuffle([...Array(n)].map(() => _.random(1, Math.round(n / 2)))))
