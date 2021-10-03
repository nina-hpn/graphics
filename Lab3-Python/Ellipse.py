from graphics import *

class Ellipse:
    def __init__(self, a, b, x=0, y=0):
        self.a = a
        self.b = b
        self.x = x
        self.y = y

    def draw(self, win, color):

        a = self.a
        b = self.b
        xc = self.x
        yc = self.y
        
        def draw4Points(win, x, y, color, sx, sy):
            win.plot(sx + x, sy + y, color)
            win.plot(sx + x, sy + -y, color)
            win.plot(sx + -x, sy + y, color)
            win.plot(sx + -x, sy + -y, color)

        x = 0
        y = b
    
        f = ((b**2) - (a**2 * b) + (0.25 * a**2))
        M = 2 * b**2 * x
        N = 2 * a**2 * y
    
        while (M < N):
    
            draw4Points(win, x, y, color, xc, yc)
    
            if (f < 0):
                M = M + (2 * b**2)
                f = f + M + (b**2)

                x += 1

            else:
                M = M + (2 * b**2)
                N = N - (2 * a**2)
                f = f + M - N + (b**2)

                x += 1
                y -= 1
    
        f = (b**2 * (x + 0.5)**2 + (a**2 * (y - 1)**2) - (a**2 * b**2))
    
        while (y >= 0):
    
            draw4Points(win, x, y, color, xc, yc)
    
            if (f > 0):
                N = N - (2 * a**2)
                f = f + (a**2) - N

                y -= 1

            else:
                M = M + (2 * b**2)
                N = N - (2 * a**2)
                f = f + M - N + (a**2)

                y -= 1
                x += 1

    def boundaryFill(self, win, color, x, y):
        
        currColor = win.getPixel(x, y)
        if currColor != "white" and currColor != color:
            win.plot(x, y, color)

            self.boundaryFill(win, color, x - 1, y)
            self.boundaryFill(win, color, x, y + 1)
            self.boundaryFill(win, color, x + 1, y)
            self.boundaryFill(win, color, x, y- 1)

            



            