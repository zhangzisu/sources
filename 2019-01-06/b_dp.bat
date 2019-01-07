@echo off
:loop
node b.dmk > b.in
b
move b.out b.tmp
b_bl
move b.out b.ans
fc b.tmp b.ans
if not errorlevel 1 goto loop
