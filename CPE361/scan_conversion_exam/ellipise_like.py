import turtle
import math

# Configuration
GRID_SIZE = 10
MIN_POINT = (-20, -20)
MAX_POINT = (40, 40)
BOARD_SIZE = (MAX_POINT[0] - MIN_POINT[0], MAX_POINT[1] - MIN_POINT[1])

h = 15
k = 15
A = 20
R = 20

# Turtle setup
wn=turtle.Screen()
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

def translate(points, to):
  result = [] + points
  for i in range(len(points)):
    result[i] = (points[i][0] + to[0], points[i][1] + to[1])  
  return result

def flip45(points):
  result = [] + points
  for i in range(len(points)):
    result[i] = (points[i][1], points[i][0])
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

# Algorithm
def mid_point_alogirthm(x1, y1, x2, y2):
    points = []
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
      points.append((x, y))
      if d > 0:
        d = d + dU
        x+=1
        y+=1
      else:
        d = d + dD
        x+=1
    return points

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


def draw_line(x1, y1, x2, y2):
  result = mid_point_alogirthm(x1, y1, x2, y2)
  return result

def draw_circle_in_first_quadrant(radius):
  first = circle_alogoirthm(radius)
  result = [] + first + flip45([] + first)
  return result

def draw_ellipse_like(h, k, A, R, color):
  result = []
  line = draw_line(0, int(R/2), int(A/2), int(R/2))
  
  # Draw circle in first quadrant and then translate to connect straight line
  circle = draw_circle_in_first_quadrant(int(R/2))
  circle = translate(circle, (A/2, 0))

  # Combine line and circle
  first_quadrant = [] + line + circle

  # mirror and flip
  result = first_quadrant + mirror(first_quadrant)
  result = result + flip(result)

  # Translate back to actually point
  result = translate(result, (h, k))

  return (result, color)


# Render grid and point
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


elipse_like = draw_ellipse_like(h, k, A, R, "Green")

pointList = []
pointList.append(elipse_like)
pointList.append(([(h, k)], "Red"))

# Print point
print("[", end = "")
for i in range(len(elipse_like[0])):
  x = int(elipse_like[0][i][0])
  y = int(elipse_like[0][i][1])
  if (i == len(elipse_like[0]) - 1):
    print("(" + str(x) + ", " + str(y)  + ")", end = "]")
  else:
    print("(" + str(x) + ", " + str(y)  + ")", end = ", ")

render(pointList)
input()