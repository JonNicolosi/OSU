#Jon Nicolosi
#CS 344
#Project 5
from random import randint

#Initial Write
for a in range(0,3):
	f = open('File {0}.txt'.format(a), 'wt')
	for index in range(0,10):
		f.write(unichr(randint(97, 122)))
		
	f.write('\n')
	f.close()	
		
#Read file contents back to user
for b in range(0,3):
	f = open('File {0}.txt'.format(b), 'r')
	str = f.read(10)
	print str
	f.close()

#Create two random integers
randominteger1 = randint(1, 42)
randominteger2 = randint(1, 42)

#Print two random integers and their product
print randominteger1
print randominteger2
print randominteger1*randominteger2