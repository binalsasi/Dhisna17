Rx = raw_input("Enter Message Code In Binary : ");

m = 0;
M = int(Rx, 2);
while(M>>m != 1): m+=1;

r = 0;
while(m+r+1 > 2**r): r+=1;

T = 0;
i = 2;
bt = 1 << (m+r-1);
bm = 1 << m-1;
pc = 2;
mc = 0;

while(i<m+r):
 if((i+1) != 2**pc):
  if((M & bm)!=0):   T = T | (bt>>i);
  bm>>1;
 else: pc+=1;
 i +=1;

ps = [];
pc = 0;

while(pc<r): 
 ps.insert(pc,0);
 pc+=1;

i = 2;
while(i<m+r):
 j = 0;
 u = 0;
 if(((T&bt) >> i)!= 0): u = 1;
 
 while(j<r):
  if(((i+1) & 1<<j)!=0): 
    ps[j] = ps[j] ^ u;
  j+=1;
 i+=1;

pc = 0;
while(pc < r):
 i = 2**pc -1;
 if(ps[pc]):  T = T | (bt>>i);
 pc+=1;

Tx = list(bin(T));
del Tx[0], Tx[0];
print "Hamming Code Produced : ", "".join(Tx);
