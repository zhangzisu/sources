while true; do  
./dmk>tmp.in 
./B<tmp.in>tmp.out
./bl<tmp.in>tmp2.out
if diff tmp.out tmp2.out; then
printf AC
else  
echo WA
exit 0  
fi
done