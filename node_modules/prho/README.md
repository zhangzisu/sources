# prho
Pollard's rho algorithm in Node.js

## Refs
https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm

## Install
```console
$ npm install prho
```

## Usage
```js
const prho = require('prho')
const factor = prho(360)
// => [2, 2, 2, 3, 3, 5]
```
