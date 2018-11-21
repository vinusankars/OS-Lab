import socket               

s = socket.socket()         
host = socket.gethostname() 
port = 1235  
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  
s.bind((host, port))   
s.listen(1)                 

c, addr = s.accept()   
c.send(b'Hello text from server.')
print('Sent: Hello text from server.')
c.close()    
s.close()         