import re
import sys
from os.path import expanduser
home = expanduser("~")

file = open(sys.argv[1])
ofile = open(home+"/test.txt",'w')
ipfile = open(home+"/ip.txt",'w')
statusfile = open(home+"/status.txt",'w')
datefile = open(home+"/date.txt",'w')
uagent= open(home+"/uagent.txt",'w')
count = 0
pattern = r'([\d\.]+) - - \[(.*?)\] "(\w+) (.*?) (HTTP/1.[01])" (\d+) (\d+|-) "(.*?)" "(.*?)"'
#group 1 - IP Address
#group 2 - day and date
#group 3 - Request method (GET/POST)
#group 4 - Requested URL
#group 5 - HTTP Version
#group 6 - HTTP status (Response status)
#group 7 - Response size (in bytes)
#group 8 - Referer
#group 9 - User-agent
ofile.write("IP"+","+"Date"+","+"Method"+","+"URL"+","+"Version"+","+"Status"+","+"Size"+","+"Referer"","+"Agent"+"\n")
user_agents = ["BrowseX","Chrome","Exabot","Firefox","Googlebot","Mozilla","MSIE","Opera","Safari","Yahoo"]
status = [0,0,0,0,0]
for line in file:
    #print "Count #",count
    match = re.search(pattern,line)
    if match :
        ofile.write(match.group(1)+",")
	ipfile.write(match.group(1)+"\n")
	rdate = re.search(r'(.*?):',match.group(2))
	ofile.write(rdate.group(1)+",")
	datefile.write(rdate.group(1)+"\n")
	if int(match.group(6)) < 200:
		status[0]+=1
	elif int(match.group(6)) < 300:
		status[1]+=1
	elif int(match.group(6)) < 400:
		status[2]+=1
	elif int(match.group(6)) < 500:
		status[3]+=1
	else:
		status[4]+=1
	ofile.write(match.group(3)+","+match.group(4)+","+match.group(5)+","+match.group(6)+","+match.group(7)+","+match.group(8))
	for agent in user_agents:
            if agent in match.group(9):
                ofile.write(","+agent+"\n")
		uagent.write(agent+"\n")
		break
    count+=1
statusfile.write("A\t"+str(status[0]))
statusfile.write("\n")
statusfile.write("B\t"+str(status[1]))
statusfile.write("\n")	
statusfile.write("C\t"+str(status[2]))
statusfile.write("\n")	
statusfile.write("D\t"+str(status[3]))
statusfile.write("\n")	
statusfile.write("E\t"+str(status[4]))
statusfile.write("\n")
file.close()
ofile.close()
statusfile.close()
ipfile.close()
datefile.close()
uagent.close()
