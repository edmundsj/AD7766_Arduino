import time
startTime = time.perf_counter()

for i in range(1000000):
    a = 1
    b = 2
    c = a+b
    print("hello")

endTime = time.perf_counter()
timeElapsed = endTime - startTime

print(timeElapsed)
