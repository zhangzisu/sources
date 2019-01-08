@echo off
:loop
node 3730.js >in
3730.exe <in >out
3730_std <in >ans
fc out ans
if not errorlevel 1 goto loop