# -*- coding: utf-8 -*-
# import pyqtgraph.examples
# pyqtgraph.examples.run()
from pyqtgraph.Qt import QtGui, QtCore
import numpy as np
import pyqtgraph as pg
from pyqtgraph.ptime import time


pg.setConfigOption('background', 'w')
pg.setConfigOption('foreground', 'k')
pg.setConfigOption('antialias', True)

app = QtGui.QApplication([])
mainWindow = QtGui.QMainWindow()
mainWindow.setWindowTitle('pyqtgraph example: PlotWidget')
mainWindow.resize(400,300)
centerWidget = QtGui.QWidget()
mainWindow.setCentralWidget(centerWidget)
# layout = QtGui.QVBoxLayout()
layout = QtGui.QHBoxLayout()
centerWidget.setLayout(layout)

pw1 = pg.PlotWidget(name='Plot1')
layout.addWidget(pw1)
pw2 = pg.PlotWidget(name='Plot2')
layout.addWidget(pw2)
mainWindow.show()

pw1.setWindowTitle('Example1')
pw1.setRange(xRange=[0,100],yRange=[-2,4]) 
# pw1.setLabel('bottom', 'Index', units='B')
pw1.showGrid(y=True,alpha=0.2) #显示网格
pw1.enableAutoRange(0,x=1.0,y=2.0)
curve11 = pg.PlotCurveItem(pen=(0,2*1.3))
curve11.setPen(pg.mkPen(width=4.5,color='b')) #曲线颜色
pw1.addItem(curve11)

pw2.setWindowTitle('Example2')
curve12 = pg.PlotCurveItem(pen=(1,2*1.3))
curve12.setPen(pg.mkPen(width=4.5,color='r')) #曲线颜色
pw1.addItem(curve12)

# curve.setFillBrush((0, 0, 255, 10))#填充色
# curve.setFillLevel(0) #填充

curve2 = pw2.plot()
curve2.setPen(pg.mkPen(width=4.5,color='g')) #曲线颜色


data = []
num=0
def update():
    global curve11,curve12,curve2, data, num
    d=np.sin(np.pi*num/50)
    if len(data)<100:
        data.append(d)
    else:
        data[0:-1]=data[1:]
        data[-1]=d
    curve11.setData(data)
    curve12.setData(np.array(data)*0.5)
    curve2.setData(data)
    num += 1
    pw1.setTitle('Example 1')
    pw2.setTitle('Example 2')
    app.processEvents()  ## force complete redraw for every plot
timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start(20)
    


if __name__ == '__main__':
    QtGui.QApplication.instance().exec_()
