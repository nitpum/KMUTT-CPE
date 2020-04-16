import turtle
import math

# Configuration
GRID_SIZE = 10
MIN_POINT = (-20, -20)
MAX_POINT = (20, 20)
BOARD_SIZE = (MAX_POINT[0] - MIN_POINT[0], MAX_POINT[1] - MIN_POINT[1])

# Turtle setup
wn=turtle.Screen()
# wn.bgcolor("Black")
t=turtle.Turtle()
t.speed(0)
t.pensize(1)
t.hideturtle()
wn.tracer(0,0)

# Render function
def draw_square():
  for i in range(4):
    t.forward(GRID_SIZE)
    t.right(90)

def in_points(points, x, y):
  for i in range(len(points)):
    if points[i][0] == x and points[i][1] == y:
      return True
  return False

def rotate_45(points, degree):
  result = [] + points
  for i in range(len(points)):
    x = points[i][0]
    y = points[i][1]
    cos = math.cos(math.radians(degree))
    sin = math.sin(math.radians(degree))
    result[i] = (y, x)
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

# Render
def render(pointList):
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

def circle_alogoirthm(radius):
  points = []
  h = 1 - radius
  x = 0
  y = radius
  points.append((x, y))
  while y > x:
    if h < 0:
      dU = 2*x + 3
      h = h + dU
      x = x + 1
    else:
      dD = 2 * (x-y) + 5
      h = h + dD
      x = x + 1
      y = y - 1
    points.append((x, y))
  return points

def draw_circle(radius, color):
  first = circle_alogoirthm(radius)
  result = [] + first + rotate_45([] + first, -45) 
  result = result + mirror(result)
  result = result + flip(result)
  return (result, color) 

pointList = []
pointList.append(draw_circle(5,"Green"))

render(pointList)
input()