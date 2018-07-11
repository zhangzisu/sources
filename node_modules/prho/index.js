const factor = (n) => {
  n = Number(n)
  let o = []
  let d = prho(n)
  if (!d) return [n]

  while (true) {
    o.push(d)
    n = n / d
    d = prho(n)
    if (!d) {
      o.push(n)
      break
    }
  }

  return o
}

const prho = (n) => {
  if (n % 2 === 0) return n === 2 ? false: 2
  if (isPrime(n)) return false
  const g = (x) => {
    return x ** 2 + 1
  }
  let x = 2
  let y = 2
  let d = 1

  while (d === 1) {
    x = g(x)
    y = g(g(y))
    d = gcd(Math.abs(x - y), n)
  }

  return d === n ? false : d
}

const gcd = (m, n) => {
  if (m < n) {
    let r = m
    m = n
    n = r
  }

  while (m % n !== 0) {
    let r = m % n
    m = n
    n = r
  }

  return n
}

const isPrime = (n) => {
  const primes = [2, 3, 5, 7, 11]
  for (let j = 0; primes[j] <= Math.sqrt(n); j += 1) {
    if (n % primes[j] === 0) return false
  }
  return true
}

module.exports = factor
