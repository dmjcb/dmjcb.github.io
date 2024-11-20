from time import sleep
from multiprocessing import Process

g_value = 100

def test_1():
    global g_value

    for i in range(5):
        print("test_1: %d" % (g_value))
        g_value += 1

        sleep(0.5)

def test_2():
    global g_value

    for i in range(5):
        print("test_2: %d" % (g_value))
        g_value += 1

        sleep(0.5)

if __name__ == "__main__":
    process_1 = Process(target=test_1)
    process_2 = Process(target=test_2)

    process_1.start()
    process_2.start()

    print("g_value = %d" % (g_value))
