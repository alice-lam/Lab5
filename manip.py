file = "";

with open("data.txt") as f:
    content = f.readlines()
	
x = 0
for line in content:
	if(x == 0):
		x = 1
		continue;
	string = line.rstrip();
	file = file + string[9:-2];
	
file = file[:-2]
	
words = [file[i:i+8] for i in range(0,len(file), 8)]

bytes = [];

for w in words:
	bytes.append(''.join([w[i-1:i+1:1] for i in range(len(w)-1, 0, -2)]))

f = open('result.txt','w')
for line in bytes:
	f.write(line+"\n");

f.close()



