while true; do  
# python3 ./gen.py
./travel <tmp.in >tmp.out
./d <tmp.in >tmp2.out
if diff tmp.out tmp2.out; then
printf AC
else  
echo WA
exit 0  
fi
done