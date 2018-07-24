@echo off
:loop
node t3_dmk.js >t3.in
message <t3.in >t3.out
ddd <t3.in >t3.ans
fc t3.out t3.ans
if not errorlevel 1 goto loop