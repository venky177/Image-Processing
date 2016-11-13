import socket
import threading
import os 
class sc(threading.Thread):
	def __init__(self):	
		threading.Thread.__init__(self)
	def run(self):
		threadlock.acquire()
		ch=client.recv(1111)
		if ch=='1':
			f=open('outfile.jpeg','a+')
			r=client.recv(4096)
			f.write(r+'\n')
			f.close()
		else:
			os.system("streamer -c /dev/video0 -o outpu.jpeg")
			f=open('outpu.jpeg','r')
			f2=open('ott.jpeg','w')
			msg=f.read(1024)	
			while(msg):
				client.send(msg)
				print "sent"
				f2.write(msg)
				msg=f.read(1024)		
			f.close()
			f2.close()
			print "sending complete"
		threadlock.release()
threadlock=threading.Lock()
s = socket.socket()
s.bind(("192.168.6.22",6000))
s.listen(5)
for i in range(0,5):
	client,client_addr=s.accept()
	s1=sc()
	s1.start()
	s1.join()
client.close()
s.close()
