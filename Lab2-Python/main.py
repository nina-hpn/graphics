from Circle import Circle
from CLine import CLine
from CPoint import CPoint


Ox1 = CPoint(-700, 0)
Ox2 = CPoint(700, 0)
Ox = CLine(Ox1, Ox2)
Ox.LineBresenham()

Oy1 = CPoint(0,-700)
Oy2 = CPoint(0, 700)
Oy = CLine(Oy1, Oy2)
Oy.LineBresenham()

x = Circle(500)
x.drawMidPoint()