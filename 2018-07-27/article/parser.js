let _ = require('lodash');
let fs = require('fs');

let males_dict = new Set();
let female_dict = new Set();

let male_dic = fs.readdirSync('dict/male');
male_dic.filter(x => x.endsWith('.txt')).forEach(x => {
    fs.readFileSync('dict/male/' + x)
        .toString()
        .split('\n')
        .map(x => x.trim())
        .filter(x => x.length)
        .forEach(x => males_dict.add(x));
});
let female_dic = fs.readdirSync('dict/female');
female_dic.filter(x => x.endsWith('.txt')).forEach(x => {
    fs.readFileSync('dict/female/' + x)
        .toString()
        .split('\n')
        .map(x => x.trim())
        .filter(x => x.length)
        .forEach(x => female_dict.add(x));
});
console.log(`Loaded ${males_dict.size} male names`);
console.log(`Loaded ${female_dict.size} female names`);

let males = new Set();
let females = new Set();
let names = new Set();

let article = fs.readFileSync('middle.txt').toString();


pas = article.split('\n\n').filter(x => x.length).map(x => x.split('\n').join(' '));

let operators = ',<.>/?;:\'"[{]}\\|-_=+)(*&^%$#@!`~‘’“”';
let numbers = '1234567890';

/**
 * getType
 * @param {String} str 
 * @returns {String} type of str
 */
function getType(str) {
    if (operators.indexOf(str) !== -1) return 'operator';
    if (numbers.indexOf(str) !== -1) return 'number';
    if (str === ' ' || str === '\t') return 'whitespace';
    return 'word';
}

/**
 * isName
 * @param {any} token The token
 * @returns {Boolean} whether the string is a name
 */
function isName(token) {
    if (!token) return false;
    if (token.type !== 'word') return false;
    if (token.str.length < 3) return false;
    let str = token.str;
    return str === _.upperFirst(str) && str !== _.upperCase(str);
}

let chapters = [];

for (let pa of pas) {
    let tokens = [];
    for (let i = 0; i < pa.length; i++) {
        let type = getType(pa[i]);
        if (!tokens.length || tokens[tokens.length - 1].type !== type) {
            tokens.push(
                {
                    str: pa[i],
                    type: type
                }
            );
        } else {
            tokens[tokens.length - 1].str = tokens[tokens.length - 1].str + pa[i];
        }
    }
    chapters.push(tokens);
    for (let i = 0; i < tokens.length; i++) {
        let token = tokens[i];
        if (i > 1 && tokens[i - 1].type === 'whitespace' && tokens[i - 2].type === 'word' && token.type === 'word' && isName(token)) {
            names.add(token.str);
        }
    }
}

for (let chapter of chapters) {
    for (let i = 0; i < chapter.length; i++) {
        let token = chapter[i];
        if (token.str === 'Mr') {
            let token_first_name = chapter[i + 3];
            let token_last_name = chapter[i + 5];
            if (isName(token_first_name)) males.add(token_first_name.str);
            if (isName(token_last_name)) males.add(token_last_name.str);
        }
        if (_.lowerCase(token.str) === 'his') {
            let token_name = chapter[i + 2];
            let token_is = chapter[i + 4];
            if (token_name && token_name.str === 'name' && token_is && (token_is.str === 'is' || token_is.str === 'was')) {
                let token_first_name = chapter[i + 6];
                let token_last_name = chapter[i + 8];
                if (isName(token_first_name)) males.add(token_first_name.str);
                if (isName(token_last_name)) males.add(token_last_name.str);
            }
        }
        if (token.str === 'Mrs') {
            let token_first_name = chapter[i + 3];
            let token_last_name = chapter[i + 5];
            if (isName(token_first_name)) females.add(token_first_name.str);
            if (isName(token_last_name)) females.add(token_last_name.str);
        }
        if (_.lowerCase(token.str) === 'her') {
            let token_name = chapter[i + 2];
            let token_is = chapter[i + 4];
            if (token_name && token_name.str === 'name' && token_is && (token_is.str === 'is' || token_is.str === 'was')) {
                let token_first_name = chapter[i + 6];
                let token_last_name = chapter[i + 8];
                if (isName(token_first_name)) females.add(token_first_name.str);
                if (isName(token_last_name)) females.add(token_last_name.str);
            }
        }
    }
}

let succeed = 0, probly = 0, failed = 0, fail = [];
names.forEach(x => {
    if (males.has(x) ^ females.has(x)) {
        succeed++;
    } else {
        males.delete(x);
        females.delete(x);
        if (males_dict.has(x) ^ female_dict.has(x)) {
            if (males_dict.has(x)) males.add(x);
            else females.add(x);
            // console.log(`Name ${x} : no match using dictionary => ${males_dict.has(x) ? 'MALE' : 'FEMALE'}`);
            probly++;
        } else {
            // console.log(`Name ${x} match failed.`);
            fail.push({
                name: x,
                reason: males_dict.has(x) ? 'Mutiple' : 'Empty'
            });
            failed++;
        }
    }
});

console.log(`Successfully matched ${succeed} names.`);
console.log(`${probly} names is fuzzy-matched.`);
console.log(`${failed} names failed.`);

fs.writeFileSync('failed.json', JSON.stringify(fail, null, '\t'));

/**
 * Output
 */




let array_males = [];
males.forEach(x => array_males.push(x));
let array_females = [];
females.forEach(x => array_females.push(x));

let output_cpp_prefix = `#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
int n;
std::set<std::string> m, f;
std::string str;
std::string getName(std::string name) {
if (m.count(name)) return "Male";
if (f.count(name)) return "Female";
return rand() & 1 ? "Male" : "Female";
}
int main() {
`;
let output_cpp_suffix = `
srand(19260817);
std::ios::sync_with_stdio(false);
std::cin >> n;
while (n--) {
std::cin >> str;
std::cout << getName(str) << std::endl;
}
return 0;
}
`;
let output_cpp =
    output_cpp_prefix
    + array_males.map(x => `m.insert("${x}");`).join('\n')
    + array_females.map(x => `f.insert("${x}");`).join('\n')
    + output_cpp_suffix;


fs.writeFileSync(`${+new Date()}gender.cpp`, output_cpp);