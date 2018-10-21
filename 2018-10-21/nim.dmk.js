const T = 100
const n = 1000
console.log(T)
for (let i = 0; i < T; i++) {
    console.log([...Array(n).keys()].map(() => 9).join(''))
}