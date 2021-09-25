import math
import matplotlib.pyplot as plt
class Circle:
    # A circle take in its radius
    def __init__(self, r):
        # Create a circle with centroid O and radius r
        self.r = r
        self.x = 0
        self.y = 0
    
    def get(self):
        return self.r

    def set(self, x, y):
        self.x = x
        self.y = y

    def drawMidPoint(self):

        def draw8Points(x, y):
            plt.plot(x, y, 'ro')

            plt.plot(-x , y, 'ro')
            plt.plot(x, -y, 'ro')
            plt.plot(-x, -y, 'ro')

            plt.plot(y, x, 'ro')
            
            plt.plot(-y, x, 'ro')
            plt.plot(y, -x, 'ro')
            plt.plot(-y, -x, 'ro')


        x1 = 0
        y1 = self.r
        f1 = 1 - self.r

        plt.plot(x1, y1, 'ro')
        while x1 < (self.r / math.sqrt(2)):
            if f1 < 0:
                f1 += 2 * x1 + 3
                x1 += 1
                draw8Points(x1, y1)

            else:
                f1 += 2*x1 - 2*y1 + 5
                x1 += 1
                y1 -= 1
                draw8Points(x1, y1)

        plt.show()




        
