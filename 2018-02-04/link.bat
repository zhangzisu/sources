@echo off
cls
del "ab.cpp"
del "color.cpp"
del "interval.cpp"

mklink /H "ab.cpp"       "ab/ab.cpp"
mklink /H "color.cpp"    "color/color.cpp"
mklink /H "interval.cpp" "interval/interval.cpp"

del info.txt
echo Informations: >info.txt
g++ "ab.cpp"       -o "ab"       -Wall >>info.txt
g++ "color.cpp"    -o "color"    -Wall >>info.txt
g++ "interval.cpp" -o "interval" -Wall >>info.txt

cls
more info.txt
pause