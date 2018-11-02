@echo off
:loop
easy.dmk %random% >easy.in
easy.baoli
cp easy.out easy.ans
easy
type easy.out
fc easy.out easy.ans
if not errorlevel 1 goto loop
type easy.out
type easy.ans
pause