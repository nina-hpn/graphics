import math
import matplotlib.pyplot as plt
class Circle:
    # A circle take in its radius
    def __init__(self, r, x = 0, y = 0):
        # Create a circle with centroid O and radius r
        self.r = r
        self.x = x
        self.y = y
    
    def get(self):
        return self.r

    def set(self, x, y):
        self.x = x
        self.y = y

    def drawMidPoint(self):

        def draw8Points(x, y, sx, sy):
            plt.plot(x + sx, y + sy, 'ro')

            plt.plot(-x + sx , y + sy, 'ro')
            plt.plot(x + sx, -y + sy, 'ro')
            plt.plot(-x + sx, -y + sy, 'ro')

            plt.plot(y + sx, x + sy, 'ro')
            
            plt.plot(-y + sx, x + sy, 'ro')
            plt.plot(y + sx, -x + sy, 'ro')
            plt.plot(-y + sx, -x + sy, 'ro')


        x1 = 0
        y1 = self.r
        f1 = 1 - self.r

        plt.plot(x1 + self.x, y1 + self.y, 'ro')
        while x1 < (self.r / math.sqrt(2)):
            if f1 < 0:
                f1 += 2 * x1 + 3
                x1 += 1
                draw8Points(x1, y1, self.x, self.y)

            else:
                f1 += 2*x1 - 2*y1 + 5
                x1 += 1
                y1 -= 1
                draw8Points(x1, y1, self.x, self.y)

        plt.show()




        
