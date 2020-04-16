import math

print("Please enter Window min(x, y)")
wXMin = float(input("x: "))
wYMin = float(input("y: "))
print("Please enter Window max(x, y)")
wXMax = float(input("x: "))
wYMax = float(input("y: "))
print("Please enter A(x, y): ")
aX = float(input("x: "))
aY = float(input("y: "))
print("Please enter B(x, y): ")
bX = float(input("x: "))
bY = float(input("y: "))

w_min = [wXMin, wYMin]
w_max = [wXMax, wYMax]
a = [aX, aY]
b = [bX, bY]

def line_length(x1, y1, x2, y2):
  return math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)

def subdivision_times(length):
  return math.ceil(math.log(length, 2))

def midpoint(x1, y1, x2, y2):
  return [(x1 + x2)/2, (y1 + y2)/2] 

def bisection(minX,  minY, maxX, maxY, line_Xmin, line_Ymin, line_Xmax, line_Ymax, loop, left = True):
  if round(minX) == line_Xmin
  middile_point = midpoint(minX, minY, maxX, maxY)
  if left:
    return bisection(minX, minY, middile_point[0], middile_point[1], line_Xmin, line_Ymin, line_Xmax, line_Ymax, loop, left)
  else:
    return bisection(middile_point[0], middile_point[1], maxX, maxY, line_Xmin, line_Ymin, line_Xmax, line_Ymax, loop, left)
  
def cohen_combine(a, b):
  return [
    1 if a[0] == b[0] and a[0] == 1 else 0,
    1 if a[1] == b[1] and a[1] == 1 else 0,
    1 if a[2] == b[2] and a[2] == 1 else 0,
    1 if a[3] == b[3] and a[3] == 1 else 0
  ]

def get_clipping_type(a, b):
  combine = cohen_combine(a, b)
  if a == b and a == [0,0,0,0]:
    return 'visible'
  if combine == [0,0,0,0]:
    return 'clipping'
  return 'invisible'

def bit_code(point, w_min, w_max):
  cohen = [0, 0, 0, 0]
  cohen[0] = 1 if point[1] > w_max[1] else 0
  cohen[1] = 1 if point[1] < w_min[1] else 0
  cohen[2] = 1 if point[0] > w_max[0] else 0
  cohen[3] = 1 if point[0] < w_min[0] else 0
  return cohen

def find_clipping_point(start, end, w_min, w_max):
  start_cohen = bit_code(start, w_min, w_max)
  end_cohen = bit_code(end, w_min, w_max)
  cohen = cohen_combine(start_cohen, end_cohen)
  clipping_type = get_clipping_type(start_cohen, end_cohen)

  distance = line_length(start[0], start[1], end[0], end[1])
  loop_times = subdivision_times(distance)

  middile_point = midpoint(start[0], start[1], end[0], end[1])

  
  is_cross_on_line_y_max = True if start_cohen[0] != end_cohen[0] else False
  is_cross_on_line_y_min = True if start_cohen[1] != end_cohen[1] else False
  is_cross_on_line_x_max = True if start_cohen[2] != end_cohen[2] else False
  is_cross_on_line_x_min = True if start_cohen[3] != end_cohen[3] else False



  print("Cohen_start: " + str(start_cohen))
  print("Cohen_end: " + str(end_cohen))
  print("Cohen: " + str(cohen))
  print("Line length: " + str(distance))
  print("Loop times: " + str(loop_times))
  print("Clipping Type: " + str(clipping_type))

  print("\n====== RESULT ======")
  if clipping_type != 'clipping':
    print("Invisible no clipping point")
    return


  return 0

find_clipping_point(a, b, w_min, w_max)