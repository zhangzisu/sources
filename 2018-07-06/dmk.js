let _ = require('lodash');
let fs = require('fs')
let path = require('path')

const n = 200000;
const m = 200000;
const k = 40;

let data = [];

data.push(`${n} ${m} ${k}`);

for (let i = 0; i < m; i++) {
    if (_.random(0, 1) == 1) {
        data.push(`1 ${_.random(1, n)}`);
    } else {
        data.push(`0 ${_.random(1, n)} ${_.random(1, 100)}`);
    }
}

fs.writeFileSync(path.resolve('in.txt'), data.join('\n'));