#!/usr/bin/python3.6

import sys
file_name=sys.argv[1]
hist_size = 200

file_content=open(file_name,"r")
first_time = True
hist = [0] * hist_size
for line in file_content:
    curr=int(line)
    if first_time:
        first_time=False;		
        prev=int(line);
        continue;
    else:
        abs_diff = abs(curr - prev)
        if abs_diff < hist_size:
            hist[abs_diff] += 1
            prev=curr
print(hist)
	
