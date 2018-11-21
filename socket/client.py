import socket               

s = socket.socket()        
host = '127.0.1.1' 
port = 1234              

s.connect((host, port))
print ('Received:',str(s.recv(1024)))
s.close()                    