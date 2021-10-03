from graphics import *
from Ellipse import Ellipse

def main():
    win = GraphWin('Ellipse', 1000, 1000)
    win.setCoords(-1000,-1000,1000,1000)
    win.setBackground("white")


    color = "red"
    e = Ellipse(200,500, x = 100, y = 200)
    e.draw(win, color)
    #e.boundaryFill(win, "black", 100, 200)

    win.getMouse()
    win.close()

main()