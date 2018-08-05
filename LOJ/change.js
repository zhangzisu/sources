let fs = require('fs')

let buffer = fs.readFileSync('lalala.cpp')

let lines = buffer.toString().split('\r\n').filter((str) => { return str.length && !str.startsWith('# ') }).join('\n');

fs.writeFileSync('lalalalala.cpp', lines);