import socket
import threading

def conexao_cliente(client,address):
    data = client.recv(2048)
    print(address)
    '''
    PROTOCOLO
    '''
    client.sendall(data)
    #Fechando o socket
    client.close()

sock = socket.socket(socket.AF_INET,  socket.SOCK_STREAM)
    
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

server_address = ('localhost', 20001)
print ("Iniciando servidor na porta %s %s" % server_address)
#Reservando porta
sock.bind(server_address)
#Escutando na porta reservada
sock.listen(1)

#Iniciando protocolo

while True:
    print ("Esperando mensagem do cliente")
    client, address = sock.accept()
    conexao = threading.Thread(target=conexao_cliente,args=(client,address,))
    conexao.start()

