from random import*

n=100
m=100
ff=open('tmp.in','w')
print(n,file=ff)
for i in range(n-1):
    print(i+2,randint(1,i+1),randint(1,2),file=ff)
print(m,file=ff)
for i in range(m):
    print(randint(1,n),randint(1,n),randint(2,100),file=ff)
ff.close()
