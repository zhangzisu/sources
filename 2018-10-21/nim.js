const gao = (n) => {
    let res = 0
    for (let i = 1; i <= n; i++)res ^= i
    return res
}

const suan = (n) => {
    let nim = gao(n), ans = 0
    for (let i = 1; i <= n; i++) {
        for (let j = 1; j <= i; j++) {
            if (!(nim ^ i ^ (i - j))) ans++
        }
    }
    return ans
}

for (let i = 1; i <= 1000; i += 4) {
    console.log(`${suan(i)}\t${suan(i + 1)}\t${suan(i + 2)}\t${suan(i + 3)}`)
}