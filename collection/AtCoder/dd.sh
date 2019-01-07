while true; do  
    ./dmk >dd.txt
    ./arc095_d <dd.txt >gg.txt
    ./std      <dd.txt >bb.txt
    if diff gg.txt bb.txt; then
        printf AC
    else  
        echo WA
        exit 0  
    fi
done