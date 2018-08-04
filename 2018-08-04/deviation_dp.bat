@echo off
:loop
node deviation_dmk.js                >deviation.in
deviation             <deviation.in  >deviation.out
deviation_bl          <deviation.in  >deviation.ans
fc                     deviation.out  deviation.ans
if not errorlevel 1 goto loop