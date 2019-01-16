const _ = require("lodash")
const g = () => (_.random(0, 998244352))

const n = 25000
console.log(n)
console.log([...Array(n)].map(() => [g(), g(), g()].join(' ')).join('\n'))
console.log(0)
