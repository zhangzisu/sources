echo off
:loop
node buy_dmk.js >buy.in
buy <buy.in >buy.out
buy_bl <buy.in >buy.ans
fc buy.out buy.ans
if not errorlevel 1 goto loop