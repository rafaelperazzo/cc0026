import threading
import time
import random

dados = []

def inserir(valor):
    global dados
    dados.append(valor)
    print("Inserido valor %d" % valor)

def ler():
    global dados
    retirado = dados.pop()
    print("Retirado: %d" % retirado)

if __name__=="__main__":
    print("Iniciando thread principal...")
    valor = random.randint(0,100)
    t1 = threading.Thread(target=inserir,args=(valor,))
    t1.start()
    t2 = threading.Thread(target=ler)
    t2.start()
    t1.join()
    t2.join()