import socket
def client(host = 'localhost', port=8082):
    
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    server_address = (host, port)
    print ("Conectando %s porta %s" % server_address)
    sock.connect(server_address)
    
    try:
        message = input("Digite a mensagem a ser enviada: ")
        print ("Enviando %s" % message)
        sock.sendall(message.encode('utf-8'))
        data = sock.recv(2048)
    except socket.error as e:
        print ("Socket error: %s" %str(e))
    except Exception as e:
        print ("Other exception: %s" %str(e))
    finally:
        print ("Closing connection to the server")
        sock.close()

client()