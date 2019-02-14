@echo off
:loop
node I_dmk >in
I <in >out
I_bl <in >ans
fc out ans
if not errorlevel 1 goto loop
