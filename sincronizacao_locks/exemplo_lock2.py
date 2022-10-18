from threading import Thread
import time
import random

g = 0

def incrementa():
    global g
    tmp = g     # le valor
    time.sleep(random.randint(0,10))
    tmp += 1    # incrementa
    g = tmp     # escreve

if __name__=="__main__":
    thread1 = Thread(target=incrementa)
    thread1.start()

    thread2 = Thread(target=incrementa)
    thread2.start()

    thread1.join()
    thread2.join()

    print(g)