let fs = require('fs')

let content = fs.readFileSync('dist.male.first.dic').toString()

content = content.split('\n').map(x => x.substring(0, x.indexOf(' '))).filter(x => x.length).join('\n')

fs.writeFileSync('male.dic.txt', content);
