for /L %i in (1, 1, 20) do cmd /c "node dmk.js >data\more_%i.in"
for /L %i in (1, 1, 20) do cmd /c "cbal <data\more_%i.in >data\more_%i.out"
