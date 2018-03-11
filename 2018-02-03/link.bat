@echo off
cls
del "digit.cpp"
del "fire.cpp"
del "integers.cpp"
del "sandwich.cpp"
mklink /H "digit.cpp"    "digit/digit.cpp"
mklink /H "fire.cpp"     "fire/fire.cpp"
mklink /H "integers.cpp" "integers/integers.cpp"
mklink /H "sandwich.cpp" "sandwich/sandwich.cpp"
del info.txt
echo Informations: >info.txt
g++ "digit.cpp"    -o "digit"    -Wall >>info.txt
g++ "fire.cpp"     -o "fire"     -Wall >>info.txt
g++ "integers.cpp" -o "integers" -Wall >>info.txt
g++ "sandwich.cpp" -o "sandwich" -Wall >>info.txt
#del "digit.exe"
#del "fire.exe"
#del "integers.exe"
#del "sandwich.exe"
cls
more info.txt
pause