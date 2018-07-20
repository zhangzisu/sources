function exgcd(a, b) {
    if (b) {
        let [r, y, x] = exgcd(b, a % b);
        y -= a / b * x;
        return [r, x, y];
    } else {
        x = 1n;
        y = 0n;
        return [a, x, y];
    }
}

module.exports = exgcd;