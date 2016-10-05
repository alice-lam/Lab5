#int getSine(int rad){
#int deg = rad*57.32;
#	int sign = -1;
#	if(deg<0 || deg > 180)
		#sign = 1;
	#deg+=180;
	#deg %= 180;
	#int num = 4*deg*(180-deg);
	#num*=1000*sign;
	#int den = 40500 - deg*(180-deg);
	#return num/den;
#}

#int Song_EnvelopeScale(int currentMill, int totalMill){ //returns scale*1000
#	if(currentMill < totalMill/5){
		#int scale = totalMill/8;
#		int arg = scale * (currentMill +90);
#		return getSine(arg);
#	}
#	else{
#		int fourFifths = totalMill*4/5;
#		int oneFifth = totalMill - fourFifths;
#		double c = fourFifths/1.897;
#		double x = (oneFifth-currentMill)/c;
#		double value = exp(x);
#		int ret = value*1000;
#		return ret;
#	}
#}

from math import exp
from math import sin
bpm = 150;
tick =  (60000000000/(bpm*24))/20;
qn = (12*tick -10000)/440

f = open('result.txt','w')
	
def scale(currentMill, totalMill): #//returns scale*1000
	if(currentMill < totalMill/5):
		scale = 8.0/totalMill;
		arg = scale * (currentMill -90);
		return (.4+sin(arg))*100;
	else:
		fourFifths = totalMill*4/5;
		oneFifth = totalMill - fourFifths;
		c = fourFifths/1.897;
		x = (oneFifth-currentMill)/c;
		value = exp(x);
		return value*100;
		
for i in range(qn):
	f.write(str(i)+"	"+str(scale(i,qn))+"\n");

f.close()