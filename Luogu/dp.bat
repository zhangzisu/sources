@echo off
:loop
node dmk > in
4245 <in >out
std <in >ans
fc out ans
if not errorlevel 1 goto loop
