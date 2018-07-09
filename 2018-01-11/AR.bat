@echo off
:loop
AD >A.txt
A <A.txt >A.out.txt
echo OK!!!
goto loop