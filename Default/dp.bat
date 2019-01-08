@echo off
:loop
node dmk > in
9 <in >out
10 <in >ans
fc out ans
if not errorlevel 1 goto loop
