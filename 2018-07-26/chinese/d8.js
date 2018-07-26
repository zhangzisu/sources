const _ = require('lodash');
const fs = require('fs');
const dict = fs.readFileSync('dict').toString().split('\r\n');
const MAX_WORD_SIZE = _.max(dict.map(x => x.length));
const FILE_NAME = 'gbxf8.in';

let content = fs.readFileSync(FILE_NAME).toString();

let result = content.split('\n').map(x => {
    return x.substring(0, 3) + ' ' + x.substring(3, x.length - 4) + ' ' + x.substring(x.length - 4, x.length - 1) + ' ' + '。';
});

fs.writeFileSync('gbxf8.out', result.join('\n'));