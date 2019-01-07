const _ = require('lodash')
const rs = require('randomstring')

const T = 100;
const n = 1000;
const q = 1000;
console.log(T);
for (let x = 0; x < T; x++) {
    console.log(rs.generate({ length: n, charset: 'qwertyuiopasdfghjklzxcvbnm' }));
    console.log(`${q}`);
    for (let y = 0; y < q; y++) {
        let l = _.random(1, n), r = _.random(1, n);
        if (l > r) {
            let t = l;
            l = r;
            r = t;
        }
        console.log(`${l} ${r} ${_.random(2)}`);
    }
}