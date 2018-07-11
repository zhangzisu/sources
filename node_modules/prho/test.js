const prho = require('./')
const cases = {
  4: [2, 2],
  13: [13],
  360: [2, 2, 2, 3, 3, 5]
}

Object.keys(cases).forEach((n) => {
  const a = JSON.stringify(cases[n])
  const b = JSON.stringify(prho(n))
  if (a !== b) throw new Error(n)
})
