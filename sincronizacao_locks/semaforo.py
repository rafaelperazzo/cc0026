import threading
import time
import random

semaforo = threading.Semaphore(2)

def mostrar():
    semaforo.acquire()
    print(threading.currentThread().getName())
    time.sleep(random.randint(2,7))
    semaforo.release()

if __name__=="__main__":
    t1 = threading.Thread(target=mostrar)
    t2 = threading.Thread(target=mostrar)
    t3 = threading.Thread(target=mostrar)
    t4 = threading.Thread(target=mostrar)
    t5 = threading.Thread(target=mostrar)
    t1.start()
    t2.start()
    t3.start()
    t4.start()
    t5.start()
    t1.join()
    t2.join()
    t3.join()
    t4.join()
    t5.join()
