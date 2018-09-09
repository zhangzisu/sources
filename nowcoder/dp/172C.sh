cp ../172C.cpp .
g++ 172C.cpp -o 172C -Wall -O2 -std=c++14
g++ 172C_std.cpp -o 172C_std -O2 -std=c++14
while true; do
    node 172C.js >172C.in
    time ./172C <172C.in >172C.out
    time ./172C_std <172C.in >172C.ans
    if diff 172C.out 172C.ans; then
        printf Accepted
    else
        printf WrongAnswer
        exit 0
    fi
done