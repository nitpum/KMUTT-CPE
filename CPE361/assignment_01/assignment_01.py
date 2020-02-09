# pMin = [0, 0]
# pMax = [10, 10]


# a = [-1, 6]
# b = [5, 12]

# a = [5, -2]
# b = [15, 15] 

# pMin = [0, 0]
# pMax = [10, 10]

# a = [5, -2]
# b = [8, 12]

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

def find_x(y, m, p):
  x = (y - p)/m
  return x

def find_y(x, m, p):
  y  = m * x + p
  return y

def find_p(x, y, m):
  return y - m * x 

def find_m(start, end):
  return (end[1] - start[1]) / (end[0] - start[0])

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
  m = find_m(start, end)
  start_p = find_p(start[0], start[1], m)
  end_p = find_p(end[0], end[1], m)
  start_cohen = bit_code(start, w_min, w_max)
  end_cohen = bit_code(end, w_min, w_max)
  cohen = cohen_combine(start_cohen, end_cohen)
  clipping_type = get_clipping_type(start_cohen, end_cohen)
  print("M: " + str(m))
  print("P_start: " + str(start_p))
  print("P_end: " + str(end_p))
  print("Cohen_start: " + str(start_cohen))
  print("Cohen_end: " + str(end_cohen))
  print("Cohen: " + str(cohen))
  print("Clipping Type: " + str(clipping_type))


  print("\n====== RESULT ======")
  if clipping_type != 'clipping':
    print("Invisible no clipping point")
    return

  crossed_point_on_line_x_min = [w_min[0], find_y(w_min[0], m, start_p)]
  crossed_point_on_line_x_max = [w_max[0], find_y(w_max[0], m, start_p)]
  crossed_point_on_line_y_min = [find_x(w_min[1], m, end_p) , w_min[1]]
  crossed_point_on_line_y_max = [find_x(w_max[1], m, end_p) , w_max[1]]

  is_cross_on_line_y_max = True if start_cohen[0] != end_cohen[0] else False
  is_cross_on_line_y_min = True if start_cohen[1] != end_cohen[1] else False
  is_cross_on_line_x_max = True if start_cohen[2] != end_cohen[2] else False
  is_cross_on_line_x_min = True if start_cohen[3] != end_cohen[3] else False

  print("Points: ")
  print(str(crossed_point_on_line_x_min) + ": " + str(is_cross_on_line_x_min))
  print(str(crossed_point_on_line_x_max) + ": " + str(is_cross_on_line_x_max))
  print(str(crossed_point_on_line_y_min) + ": " + str(is_cross_on_line_y_min))
  print(str(crossed_point_on_line_y_max) + ": " + str(is_cross_on_line_y_max))


  return 0

find_clipping_point(a, b, w_min, w_max)