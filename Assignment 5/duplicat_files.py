import hashlib
import fnmatch
import os
import time

def GenerateHash(filename,blockSize = 65536): # to create hash value for each file
    try:
        f = open(filename,'rb')
        h = hashlib.md5()
        while True:
            data = f.read(blockSize)
            if not data:
                break
            h.update(data)
        return h.hexdigest()
    except IOError,e:
        print e
   
start_time = time.time()
A = set()
dups = []
rootPath = '/home/archbloom/remove/' # path to check the if any files are duplicate
pattern = '*' # check all types of files
 
for root, dirs, files in os.walk(rootPath):
    for filename in fnmatch.filter(files, pattern):
        temp = len(A)
        A.add(GenerateHash((os.path.join(root, filename))))
        if temp == len(A):		# add duplicate files to a list- dups 
            dups.append(os.path.join(root, filename)) 
for i in range(len(dups)):
    print dups[i]  
print "Total duplicate files found = "+str(len(dups))
print "Time required in seconds = " +str(time.time() - start_time) # execution time of the program
print "Deleting all the duplicate files: "
response = raw_input("Y/N:")   # ask user if willing to remove the duplicate files or not 
if response ==  "Y" or response == "y":
	for i in range(len(dups)):
		os.remove(dups[i])
	print "All duplicate files are removed."
else:
	print "Duplicate files are not removed."

