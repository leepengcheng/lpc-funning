# coding:utf-8
import os
import sys
#界面部分
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtWidgets import QApplication, QMainWindow
from ui.ui_main import Ui_mainWindow
import rospy
from std_msgs.msg import String

class MainWindow(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        QtWidgets.QMainWindow.__init__(self, parent)
        self.ui = Ui_mainWindow()
        self.ui.setupUi(self)
        self.initializeSignals()  #初始化信号槽链接
        rospy.init_node("qt_node")
        self.pub= rospy.Publisher('/chatter', String, queue_size=10)
        self.sub=rospy.Subscriber("/chatter", String, self.callback)

    def callback(self,msg):
        print("listener"+msg.data)

    def initializeSignals(self):
        '''
        初始化信号槽
        '''
        self.ui.check_section.clicked.connect(self.showSection)

    def showSection(self,click):
        self.pub.publish("hello world")

    

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())


