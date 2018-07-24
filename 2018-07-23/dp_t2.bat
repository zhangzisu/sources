@echo off
:loop
node t2_dmk.js >in
split <in >out
split_bl <in >ans
fc out ans
if not errorlevel 1 goto loop
