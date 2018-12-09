@echo off
:loop
d > in
s <in > ans
a <in > out
fc ans out
if not errorlevel 1 goto loop