const n = 100000
const _ = require("lodash")
console.log(n)
console.log(
    [
        ...Array(n).keys()
    ].map(() => {
        return `92400 92400 92400`;
    }).join("\n")
)