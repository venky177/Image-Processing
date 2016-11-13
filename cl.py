import socket
import os
ip="192.168.5.206"
filen="/tmp/out.jpeg"
c=socket.socket()

c.connect(("192.168.5.206",8002))
ch=raw_input("Enter choice: 1.Write 2.Read\n")
c.send(ch)
if ch=='1':
	print 'Writing to file..'
	msg=raw_input("-->")
	c.send(msg)
else:
	print 'Current contents...'
	f=open('out.jpeg','wb')
#	msg=c.recv(1024)
   	print "\n\nPicture captured!"
yolo1="sshpass -p 'pictsctr' scp root@"+ip+":"+filen + " /home/exam10/Music"
os.system(yolo1)
os.system("chmod 777 /home/exam10/Music/out.jpeg" )
f.close()	    
c.close()
