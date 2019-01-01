const randFill = (thead, offsetX, offsetY, width, height, color) => {
    const vis = [...Array(width)].map(() => [...Array(height)].map(() => false))
    const intervals = [...Array(thead)].map(() => {
        const socket = io()
        return setInterval(() => {
            let x = Math.floor(Math.random() * width)
            let y = Math.floor(Math.random() * height)
            while (vis[x][y]) {
                x = Math.floor(Math.random() * width)
                y = Math.floor(Math.random() * height)
            }
            vis[x][y] = 1
            socket.emit("draw", {
                x: offsetX + x,
                y: offsetY + y,
                color
            })
        }, 1000)
    })
    return () => intervals.forEach(id => clearInterval(id))
}

const linerFill = (thead, offsetX, offsetY, width, height, color) => {
    const queue = []
    for (let i = 0; i < width; i++) {
        for (let j = 0; j < height; j++) {
            queue.push([offsetX + i, offsetY + j])
        }
    }
    for (let i = 0; i < thead; i++) {
        const socket = io()
        const interval = setInterval(() => {
            if (!queue.length) {
                clearInterval(interval)
                return
            }
            const data = queue.shift()
            socket.emit("draw", {
                x: data[0],
                y: data[1],
                color
            })
        }, 1000)
    }
}

const linerFillEx = (thead, offsetX, offsetY, width, height) => {
    const queue = []
    for (let i = 0; i < width; i++) {
        for (let j = 0; j < height; j++) {
            queue.push([offsetX + i, offsetY + j])
        }
    }
    for (let i = 0; i < thead; i++) {
        const socket = io()
        const interval = setInterval(() => {
            if (!queue.length) {
                clearInterval(interval)
                return
            }
            const data = queue.shift()
            socket.emit("draw", {
                x: data[0],
                y: data[1],
                color: (data[0] + data[1]) % 32
            })
        }, 1000)
    }
}

const linerFillExEx = (thead, offsetX, offsetY, width, height) => {
    const queue = []
    for (let i = 0; i < width; i++) {
        for (let j = 0; j < height; j++) {
            queue.push([offsetX + i, offsetY + j])
        }
    }
    for (let i = 0; i < thead; i++) {
        const socket = io()
        const interval = setInterval(() => {
            if (!queue.length) {
                clearInterval(interval)
                return
            }
            const data = queue.shift()
            socket.emit("draw", {
                x: 800 - data[0],
                y: 600 - data[1],
                color: Math.floor(Math.random() * 32)
            })
        }, 1000)
    }
}

const randFill = (thead, offsetX, offsetY, width, height, color) => {
    const vis = [...Array(width)].map(() => [...Array(height)].map(() => false))
    const intervals = [...Array(thead)].map(() => {
        const socket = io()
        return setInterval(() => {
            let x = Math.floor(Math.random() * width)
            let y = Math.floor(Math.random() * height)
            vis[x][y] = 1
            socket.emit("draw", {
                x: 800 - (offsetX + x),
                y: 600 - (offsetY + y),
                color: 28
            })
        }, 1000)
    })
    return () => intervals.forEach(id => clearInterval(id))
}