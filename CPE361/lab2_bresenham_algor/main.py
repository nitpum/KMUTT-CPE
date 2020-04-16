import turtle
GRID_SIZE = 10
MIN_POINT = (-20, -5)
MAX_POINT = (13, 20)
BOARD_SIZE = (MAX_POINT[0] - MIN_POINT[0], MAX_POINT[1] - MIN_POINT[1])

wn=turtle.Screen()
# wn.bgcolor("Black")
t=turtle.Turtle()
t.speed(0)
t.pensize(1)
t.hideturtle()
wn.tracer(0,0)

pointList = []

def draw_square():
  for i in range(4):
    t.forward(GRID_SIZE)
    t.right(90)

def in_points(points, x, y):
  for i in range(len(points)):
    if points[i][0] == x and points[i][1] == y:
      return True
  return False

def plot_pixel(points, x, y, d):
  points.append((x, y))
  print('(' + str(x) + ', ' + str(y) + ') ' + str(d))

# def mid_point_line(x1, y1, x2, y2, color):
#     x1 = int(x1)
#     y1 = int(y1)
#     x2 = int(x2)
#     y2 = int(y2)
#     points = []

#     dx = x2 - x1
#     dy = y2 - y1
#     d = 2 * dy - dx
#     dU = 2 * dy
#     dD = 2 * (dy - dx)
#     x = x1
#     y = y1
#     print('DX: ' + str(dx))
#     print('DY: ' + str(dy))
#     print('D: ' + str(d))
#     print('dU: ' + str(dU))
#     print('dD: ' + str(dD))
#     # if dx > dy:
#     while x <= x2:
#       plot_pixel(points, x, y, d)
#       if d > 0:
#         d = d + dD
#         x+=1
#       else:
#         d = d + dU
#         x+=1
#         y+=1
    # elif dx < dy: 
    #   d = 2 * dx - dy
    #   dU = 2 * dx
    #   dD = 2 * (dx - dy)
    #   while y <= y2:
    #     plot_pixel(points, x, y, d)
    #     if d < 0:
    #       d = d + dU
    #       y+=1
    #     else:
    #       d = d + dD
    #       x+=1
    #       y+=1
    # else:
    #   while x <= x2:
    #     plot_pixel(points, x, y, d)
    #     x+=1
    #     y+=1

def plot_pixel(points, x, y, d):
  points.append((x, y))
  # print('(' + str(x) + ', ' + str(y) + ') ' + str(d))

def mid_point_alogirthm(x1, y1, x2, y2, points):
    x1 = int(x1)
    y1 = int(y1)
    x2 = int(x2)
    y2 = int(y2)

    dx = x2 - x1
    dy = y2 - y1
    d = 2 * dy - dx
    dU = 2 * dy
    dD = 2 * (dy - dx)
    x = x1
    y = y1
    while x <= x2:
      plot_pixel(points, x, y, d)
      if d > 0:
        d = d + dD
        x+=1
      else:
        d = d + dU
        x+=1
        y+=1


def mirror(points):
  for i in range(len(points)):
    points[i] = (-points[i][0], points[i][1])
    
def flip(points):
  for i in range(len(points)):
    points[i] = (points[i][0], -points[i][1])

def transpose(points, x, y):
  for i in range(len(points)):
    points[i] = [points[i][0] + x, points[i][1] + y]

def draw_line(x1, y1, x2, y2, color):
  mirrored = False
  flipped = False
  points = []
  offset = (1 - x1 ,1 - y1)
  x2 = x2 + offset[0]
  y2 = y2 + offset[1]
  if x2 < 0:
    x2 = -x2 + offset[0]
    mirrored = True
  if y2 < 0:
    y2 = -y2 + offset[1]
    flipped = True
  print(offset, color)
  print(x1, y1, x2, y2, color)
  mid_point_alogirthm(1, 1, x2, y2, points)

  # if flipped == True:
  #   flip(points)
  if mirrored == True:
    mirror(points)
  # transpose(points, -offset[0], -offset[1])
  pointList.append((points, color))


draw_line(1, 1, 13, 7, "Green")
# # 2 -13
draw_line(2, 2, 13, 7, "Red")
draw_line(1, 1, 7, 13, "Red")
draw_line(1, 1, 7, 13, "Orange")
draw_line(-1, 1, -13, 7, "Blue")


for y in range(MIN_POINT[1], MAX_POINT[1] + 1):   
    t.setpos(-(BOARD_SIZE[0] / 2) * GRID_SIZE - (GRID_SIZE /2), (-(BOARD_SIZE[1] / 2) * GRID_SIZE) + (y - MIN_POINT[1]) * GRID_SIZE)
    for x in range(MIN_POINT[0], MAX_POINT[0] + 1):
      t.begin_fill()
      draw_square()
      t.color("White")
      if (x == 0 or y == 0):
        t.color("Gray")
      for points in pointList:
        if in_points(points[0], x, y) == True:
          t.color(points[1])
      t.end_fill()
      t.color("Black")
      t.forward(GRID_SIZE)

wn.update()
input()


# x = list(map(lambda x: x[0], points))
# y = list(map(lambda x: x[1], points))

# for i in range(0, len(points) - 1):
#   plt.plot([points[i][0], points[i + 1][0]], [points[i][1], points[i + 1][1]], '-ro')

# plt.scatter(x, y)
# plt.grid(True)