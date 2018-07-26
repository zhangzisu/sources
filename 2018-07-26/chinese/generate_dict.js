const _ = require('lodash');
const fs = require('fs');
const dict = fs.readFileSync('dict_source').toString().split('\r\n');
let result = new Set();
dict.forEach((x) => {
    result.add(x);
    result.add(x + '了');
    result.add(x + '的');
    result.add(x + '个');
    result.add(x + '吧');
});

result.forEach((x) => {
    if (!x.startsWith('不')) {
        result.add('不' + x);
    }
});

let output = [];
result.forEach(x => output.push(x));
fs.writeFileSync('dict', output.join('\r\n'));