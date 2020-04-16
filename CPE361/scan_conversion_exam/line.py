import turtle
import math

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

# x0 = input("x0: ")
# y0 = input("y0: ")
# x1 = input("x1: ")
# y1 = input("y1: ")
# m = (y1 - y0) / (x1 - x0)

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

def translate(points, trans):
  result = [] + points
  for i in range(len(points)):
    result[i] = (points[i][0] + trans[0], points[i][1] + trans[1])
  return result

def mirror(points):
  result = [] + points
  for i in range(len(points)):
    result[i] = (-points[i][0], points[i][1])
  return result
    
def flip(points):
  result = [] + points
  for i in range(len(points)):
    result[i] = (points[i][0], -points[i][1])
  return result

def flip45(points):
  result = [] + points
  for i in range(len(points)):
    result[i] = (points[i][1], points[i][0])
  return result

def rotate_45(points, degree):
  result = [] + points
  for i in range(len(points)):
    x = points[i][0]
    y = points[i][1]
    cos = math.cos(math.radians(degree))
    sin = math.sin(math.radians(degree))
    result[i] = (y, x)
  return result
  
def mid_point_alogirthm(x1, y1, x2, y2, points):
    x1 = int(x1)
    y1 = int(y1)
    x2 = int(x2)
    y2 = int(y2)

    dx = x2 - x1
    dy = y2 - y1
    d = 2 * dy - dx
    dU = 2 * (dy - dx)
    dD = 2 * dy
    x = x1
    y = y1
    while x <= x2:
      plot_pixel(points, x, y, d)
      if d > 0:
        d = d + dU
        x+=1
        y+=1
      else:
        d = d + dD
        x+=1


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