const _ = require("lodash")
const randomstring = require("randomstring")
const charset = 'QWERTYUIOPLKJHGFDSAZXCVBNM';
const generate = (length) => (randomstring.generate({ length, charset }));
console.log(10)
for (let d = 0; d < 10; d++) {
    console.log(1000001);
    let s = generate(500000);
    s = s + s;
    const p = _.random(0, 1000000)
    s = s.substring(0, p) + generate(1) + s.substring(p, s.length)
    console.log(s)
}