const fs = require("fs-extra")

let template = fs.readFileSync("Lcm.template.cpp").toString()

let lineTemplate = `if (n == :key) return puts(":value"), 0;`;
let inject = [];

fs.readFileSync("Lcm.data")
    .toString()
    .split('\n')
    .map(x => x.trim())
    .forEach((v, i) => inject.push(lineTemplate.replace(":key", i).replace(":value", v)));

template = template.replace("/* inject */", inject.join('\n'));

fs.writeFileSync("Lcm.cpp", template);