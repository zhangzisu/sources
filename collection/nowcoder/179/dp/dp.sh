while true; do
    node C.dmk.js >C.in
    time ./cur <C.in >C.out
    time ./std <C.in >C.ans
    if diff C.out C.ans; then
        printf "Accepted\n"
    else
        printf "Wrong Answer\n"
        exit 0
    fi
done