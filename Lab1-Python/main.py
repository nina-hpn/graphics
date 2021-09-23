from CLine import CLine
from CPoint import CPoint

pointA = CPoint(100,700)
pointB = CPoint(300,800)
line = CLine(pointB, pointA)

# Test Line DDA
line.LineDDA()
# Test Line Bresenham
line.LineBresenham()
