const fs = require('fs')

let data = fs.readFileSync('dict.txt').toString().split('\r\n')

data = data.map(x => x.substring(0, x.indexOf(' ')).trim()).filter(x => x.length).join('\r\n');

fs.writeFileSync('dict.txt', data);