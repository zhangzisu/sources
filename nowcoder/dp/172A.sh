cp ../172A.cpp .
g++ 172A.cpp -o 172A -Wall -O2 -std=c++14
g++ 172A_std.cpp -o 172A_std -O2 -std=c++14
while true; do
    node 172A.js >172A.in
    ./172A <172A.in >172A.out
    ./172A_std <172A.in >172A.ans
    if diff 172A.out 172A.ans; then
        printf "Accepted\n"
    else
        printf "Wrong Answer\n"
        exit 0
    fi
done