const _ = require('lodash');
const fs = require('fs');

let dicts = fs.readdirSync('dicts');
let result = new Set();

for (let filename of dicts) {
    if (filename.endsWith('.txt')) {
        let dict = fs.readFileSync(`dicts/${filename}`).toString().split('\r\n');
        dict = dict.map(x => x.trim()).filter(x => (x.length && x.indexOf(' ') === -1));
        dict.forEach(
            x => {
                if (!result.has(x))
                    result.add(x)
            }
        );
    }
}

result.forEach((x) => {
    if (!x.endsWith('了')) {
        result.add(x + '了');
    }
});

result.forEach((x) => {
    if (!x.startsWith('不')) {
        result.add('不' + x);
    }
});

result.forEach((x) => {
    if (x.startsWith('不') && x.length == 2) {
        let str = x[1] + x[0] + x[1];
        if (!result.has(str))
            result.add(str);
    }
});

let output = [];
result.forEach(x => output.push(x));
fs.writeFileSync('dict', output.join('\r\n'));
