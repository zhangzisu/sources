echo off
:loop
cls
dmk %random% >in.txt
baidu <in.txt >out.txt
echo FUCK!
fucker <in.txt >std.txt
echo FUCK!
fc out.txt std.txt
if not errorlevel 1 goto loop
pause