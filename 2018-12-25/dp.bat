@echo off
:loop
node gen >in
leaves <in >out
std <in >ans
fc out ans
if not errorlevel 1 goto loop
