import math

def line_length(x1, y1, x2, y2):
  return math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)

def subdivision_times(length):
  return math.ceil(math.log(length, 2))

def midpoint(x1, y1, x2, y2):
  return [(x1 + x2)/2, (y1 + y2)/2] 

print("Please enter A(x, y): ")
aX = float(input("x: "))
aY = float(input("y: "))
print("Please enter B(x, y): ")
bX = float(input("x: "))
bY = float(input("y: "))

length = line_length(aX, aY, bX, bY)
subdivision_times = 2 * subdivision_times(length)

print("\n====== RESULT ======")
print("Line length: " + str(length))
print("Subdivisons: " + str(subdivision_times))