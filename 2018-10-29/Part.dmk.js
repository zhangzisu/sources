const n = 1000
console.log(n)
console.log(
    [...Array(n).keys()].map(i =>
        [...Array(n).keys()].map(j => (i + j) & 1).join(' ')
    ).join('\n')
)