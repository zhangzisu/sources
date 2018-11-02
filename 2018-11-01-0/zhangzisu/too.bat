@echo off
:loop
too.dmk %random% >too.in
too.baoli
cp too.out too.ans
too
type too.out
fc too.out too.ans
if not errorlevel 1 goto loop
type too.out
type too.ans
pause