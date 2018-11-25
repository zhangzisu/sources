const _ = require("lodash")
const { generate } = require("randomstring")

const n = 10
console.log(n)
console.log(...[...Array(n - 1).keys()].map((i) => _.random(1, i + 1)))
console.log(...[...Array(n).keys()].map(() => _.random(1, 100)))
let m = 10
console.log(m)
for (; m; m--) {
    const all = _.shuffle([...Array(n).keys()].map(i => i + 1));
    if (_.random(0, 1)) {
        console.log('P', all[0], all[1]);
    } else {
        console.log('V', all[0], _.random(1, 100));
    }
}