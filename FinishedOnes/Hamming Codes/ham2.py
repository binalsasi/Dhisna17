Rx = raw_input("Enter Received CodeWord In Binary : ");

n = 0;
T2 = int(Rx,2);
while(T2 >> n != 1): n+=1;
if(Rx[0] == '0'): n+=1;
r = 0;

while(n > 2**r): r+=1;

bt = 1 << (n-1);
ps2 = [];
pc = 0;
i = 0;

while(pc < r):
 i = 2**pc - 1;
 if(((T2& bt)>>i)!=0): ps2.insert(pc,1);
 else: ps2.insert(pc,0);
 pc+=1;

ps = [];
pc = 0;
while(pc<r):
 ps.insert(pc,0);
 pc+=1;
i = 2; pc = 2;

while(i<n):
 j = 0;
 u = 0;
 if(((T2&bt)>>i)!= 0): u = 1;
 if(i+1 != 2**pc):
  while(j<r):
   if(((i+1) & 1<<j)!=0):
     ps[j] = ps[j] ^ u;
   j +=1;
 else: pc+=1;
 i+=1;

c = 0;
i = 0;
while(i<r):
 if(ps2[i] & ps[i]):
  c += 2**i;
 i+=1;

if(c == 0):
 print "No Error Was Detected; Received Code Word = ", Rx;
else:
 print "Error Occured at position",c, "of Received Code Word = ", Rx;
 T2 = T2 ^ (bt >> c-1);
 R = list(Rx);

 if(R[c-1] == '0'): R[c-1] = '1';
 else: R[c-1] = '0';
 print "The Corrected Code Word =", "".join(R);
