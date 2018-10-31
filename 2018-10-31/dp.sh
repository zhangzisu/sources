while true; do  
node cake.dmk >tmp.in
./cake <tmp.in >tmp.out
./cake.fake <tmp.in >tmp2.out
if diff tmp.out tmp2.out; then
printf AC
else  
echo WA
exit 0  
fi
done