cp ../172B.cpp .
g++ 172B.cpp -o 172B -Wall -O2 -std=c++14
g++ 172B_std.cpp -o 172B_std -O2 -std=c++14
while true; do
    node 172B.js >172B.in
    ./172B <172B.in >172B.out
    ./172B_std <172B.in >172B.ans
    if diff 172B.out 172B.ans; then
        printf "Accepted\n"
    else
        printf "Wrong Answer\n"
        exit 0
    fi
done