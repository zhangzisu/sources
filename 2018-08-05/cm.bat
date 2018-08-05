@echo off
:loop
node chairman.js >chairman.in
chairmantree.exe <chairman.in >chairman.out
chairmantree.bak.exe <chairman.in >chairman.ans
fc chairman.out chairman.ans
if not errorlevel 1 goto loop
