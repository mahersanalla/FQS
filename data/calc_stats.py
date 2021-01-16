#!/usr/bin/python3.6
import sys
file_name=sys.argv[1]
output_file=sys.argv[2]
content=open(file_name,"r")
out_file=open(output_file,"w")
x=content.read();
x=x.replace(",","")
z=x[1:len(x)-3]
y = [int(i) for i in z.split()]
#print(y)

print('The size of hist is: ' + str(len(y)))
samples_sum = sum(y)
print('The total sum of samples is: '+str(samples_sum))
newList = [w / samples_sum for w in y]
newList = [round(w * 100,3) for w in newList]
print(newList)
sys.stdout=out_file;
for percentage in newList:
	print(percentage)
