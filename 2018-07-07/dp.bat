:loop
dmk >in
std <in >out.std
tokyo <in >out.tokyo
fc out.std out.tokyo
if not errorlevel 1 goto loop