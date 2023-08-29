import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
server_address = ('localhost', 20001)
print ("Conectando %s porta %s" % server_address)
#Conectando ao servidor
sock.connect(server_address)

message = input("Digite a mensagem a ser enviada: ")
print ("Enviando %s" % message)
#Enviando mensagem ao servidor
sock.sendall(message.encode('utf-8'))
#Recebendo mensagem do servidor
data = sock.recv(2048)
#Imprimino a mensagem recebida
print(data.decode())

#Fechando o socket
sock.close()