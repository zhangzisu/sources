@echo off
:loop
node t2_dmk.js >in
problem <in >out
problem_bak <in >std
fc out std
if not errorlevel 1 goto loop