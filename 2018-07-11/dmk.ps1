for($i = 0;$i -lt 10;$i = $i + 1) {
    node --stack-size=1024000000 t2_dmk.js >data/ex_$i.in
    Get-Content data/ex_$i.in |  ./problem >data/ex_$i.out
}