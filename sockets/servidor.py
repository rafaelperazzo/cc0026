import socket

def server(host = 'localhost', port=8082):
    data_payload = 2048 
    
    sock = socket.socket(socket.AF_INET,  socket.SOCK_STREAM)
    
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    server_address = (host, port)
    print ("Iniciando servidor na porta %s %s" % server_address)
    sock.bind(server_address)
    
    sock.listen(5)
    i = 0
    while True:
        print ("Esperando mensagem do cliente")
        client, address = sock.accept()
        data = client.recv(data_payload)
        '''
        o que fazer com a mensagem recebida ?
        '''
        if data:
            print ("Dados: %s" %data.decode())
            client.send(data)
            client.close()
server()