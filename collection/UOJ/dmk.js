console.log(2, 25000)
console.log(...[...Array(25000).keys()].map(_ => _ + 1))
