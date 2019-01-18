import matplotlib.pyplot as plt
from sys import argv

if __name__ == "__main__":
    data = argv[1]
    with open("paint" + data + ".in", "r") as input:
        n = 2 * int(input.readline())
        X = []
        Y = []
        for i in range(n):
            x, y = list(map(int, input.readline().split()))
            X.append(x)
            Y.append(y)
        plt.plot(X, Y, 'ro')
    if len(argv) > 2:
        with open("paint" + data + ".out", "r") as output:
            for i in range(n):
                j = int(output.readline()) - 1
                if(j > i):
                    plt.plot([X[i], X[j]], [Y[i], Y[j]], color='b')
    plt.show()
