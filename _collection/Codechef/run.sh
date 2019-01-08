cp ../PHOTOCOM.cpp .
g++ PHOTOCOM.cpp -o PHOTOCOM -Wall -O2 -std=c++14
g++ baoli.cpp -o baoli -O2 -std=c++14
while true; do
    node dck.js >PHOTOCOM.in
    ./PHOTOCOM <PHOTOCOM.in >PHOTOCOM.out
    ./baoli <PHOTOCOM.in >PHOTOCOM.ans
    if diff PHOTOCOM.out PHOTOCOM.ans; then
        printf "Accepted\n"
    else
        printf "Wrong Answer\n"
        exit 0
    fi
done