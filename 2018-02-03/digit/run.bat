@echo off
:loop
cls
dmk
std
digit
fc digit.out digit.ans
if not errorlevel 1 goto loop