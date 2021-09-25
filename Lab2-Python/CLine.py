import matplotlib.pyplot as plt
import math


class CLine:
    def __init__(self, a, b):
        self.a = a.get()
        self.b = b.get()
    

    def LineBresenham(self, color = 'blue'):
        # Determin if it is slower or faster
        x1, y1 = self.a
        x2, y2 = self.b

        if x1 == x2 and y1 == y2: # The two point is conincide
            plt.plot(x1,y1, 'ro')
            
            return

        def _LineBresenhamY(x1, y1, x2, y2):   
            Dx = abs(x2 - x1)
            Dy = y2 - y1

            yStep = (1 if Dy >= 0 else -1)  
            Dy = abs(Dy)

            const1 = Dy * 2
            const2 = (Dy - Dx) * 2
            p = const1 - Dx
            
            plt.plot(x1, y1, 'bo')

            for i in range(0, Dx, 1):
                if p < 0:
                    p += const1

                else:
                    p += const2
                    y1 += yStep

                x1 += 1
                plt.plot(x1, y1, 'bo')

            
            return

        def _LineBresenhamX(x1, y1, x2, y2):
            Dx = x2 - x1
            Dy = abs(y2 - y1)

            xStep = (1 if Dx >= 0 else -1)
            Dx = abs(Dx)

            const1 = Dx * 2
            const2 = (Dx - Dy) * 2

            p = const1 - Dy

            plt.plot(x1, y1, 'bo')

            for i in range(0, Dy, 1):
                if p < 0:
                    p += const1
                else:
                    p += const2
                    x1 += xStep
                    
                y1 += 1
                plt.plot(x1, y1, 'bo')

            
            return

        
        if abs(x1 - x2) > abs(y1 - y2): #It is slower
            # Determine if the point is at it correct placement
            if x1 <= x2: #It is correct
                _LineBresenhamY(x1, y1, x2, y2)
            else:
                _LineBresenhamY(x2, y2, x1, y1)
        else: # It is faster
            if y1 <= y2:
                _LineBresenhamX(x1, y1, x2, y2)
            else:
                _LineBresenhamX(x2, y2, x1, y1)




    def LineDDA(self, color = 'red'):

        def Round(x):
            return int(x + 0.5)

        def _LineDDAX(x1, y1, x2, y2):

            plt.plot(x1, y1, 'ro')
            a = (y2 - y1) / (x2 - x1)
            y = y1

            while x1 < x2:
                x1 += 1
                y += a
                plt.plot(x1, Round(y), 'ro')

            
            return


        def _LineDDAY(x1, y1, x2, y2):

            plt.plot(x1, y1, 'ro')
            a = (x2 - x1) / (y2 - y1)
            x = x1

            while y1 < y2:
                y1 += 1
                x += a
                plt.plot(Round(x), y1, 'ro')

            
            return()

        
        x1, y1 = self.a
        x2, y2 = self.b

        if x1 == x2 and y1 == y2:
            plt.plot(x1, y1, 'ro')
            
            return

        if abs(x1 - x2) > abs(y1 - y2):
            if x1 < x2:
                _LineDDAX(x1, y1, x2, y2)
            else:
                _LineDDAY(x2, y2, x1, y1)

        else:
            if y1 < y2:
                _LineDDAY(x1, y1, x2, y2)
            else:
                _LineDDAY(x2, y2, x1, y1)




