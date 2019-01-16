const n = 5
/**
 * @param {number} len
 * @param {number} vmin
 * @returns {number[]}
 */
function build(len, vmin) {
    if (len == 1) return [vmin]
    let ret = build(len - 1, vmin + 1)
    ret.splice((len + 1) / 2 - 1, 0, vmin)
    return ret
}
console.log(n)
console.log(build(n, 1).join(' '))
