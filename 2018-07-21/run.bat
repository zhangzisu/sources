@echo off
:loop
node dmk.js >in
bucket <in >out
bl <in >ans
fc out ans
if not errorlevel 1 goto loop