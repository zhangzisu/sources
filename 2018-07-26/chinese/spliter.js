const _ = require('lodash');
const fs = require('fs');
const dict = fs.readFileSync('dict').toString().split('\r\n');
const MAX_WORD_SIZE = _.max(dict.map(x => x.length));
const FILE_NAME = 'gbxf2.in';

let content = fs.readFileSync(FILE_NAME).toString();

let numbers = '0123456789１２３４５６７８９０'.split('');
let english = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'.split('');
let operations = ',./;/*-+()&^%$#@!。，；<>‘“’”【】（）{}《》！？￥…— '.split('');

function getTypeByWord(str) {
    if (numbers.includes(str)) return 'number';
    if (english.includes(str)) return 'english';
    if (operations.includes(str)) return 'operation';
    return 'chinese';
}

let parsers = {
    number: x => x,
    english: x => x,
    operation: x => x,
    chinese: x => {
        let result = [];
        while (x.length) {
            for (let len = _.min([MAX_WORD_SIZE, x.length]); len >= 1; len--) {
                let word = x.substr(0, len);
                if (dict.includes(word) || len == 1) {
                    x = x.substring(len, x.length);
                    result.push(word);
                    break;
                }
            }
        }
        return result.join(' ');
    }
};

let result = [];

// Tokenlization
let lines = content.split('\n');
for (let line of lines) {
    let tokens = [];
    for (let i = 0; i < line.length; i++) {
        let type = getTypeByWord(line[i]);
        if (!tokens.length || type !== tokens[tokens.length - 1].type) {
            tokens.push({ str: line[i], type: type });
        } else {
            tokens[tokens.length - 1].str = tokens[tokens.length - 1].str + line[i];
        }
    }
    tokens.forEach((x) => {
        x.str = parsers[x.type](x.str);
    });
    tokens = tokens.map(x => x.str);
    result.push(tokens.join(' '));
}

fs.writeFileSync('gbxf2.out', result.join('\n'));