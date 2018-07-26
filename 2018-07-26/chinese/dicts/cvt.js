const fs = require('fs')

let data = fs.readFileSync('extra1.txt').toString().split('\r\n')

data = data.sort();
data = data.join('\r\n');

fs.writeFileSync('extra1.txt', data);