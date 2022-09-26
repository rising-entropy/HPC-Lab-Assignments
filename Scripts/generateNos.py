import random

print("Enter Numbers to Generate - ", end='')
n = int(input())

f = open("data.txt", "w")
for i in range(n):
    f.write(str(int(random.random() * 10000)))
    f.write("\n")

f.close()