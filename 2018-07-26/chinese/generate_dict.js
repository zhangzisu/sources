const _ = require('lodash');
const fs = require('fs');
let dict = fs.readFileSync('default.txt').toString().split('\r\n');
let result = new Set();
dict.forEach(x => result.add(x));

let output = [];
result.forEach(x => output.push(x));
fs.writeFileSync('dict', output.join('\r\n'));