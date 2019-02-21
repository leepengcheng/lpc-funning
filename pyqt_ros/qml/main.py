from PyQt5.QtGui import QGuiApplication
from PyQt5.QtQml import QQmlApplicationEngine 


if __name__ == "__main__": 
    import sys # Create an instance of the application 
    app = QGuiApplication(sys.argv) # Create QML 
    engine = QQmlApplicationEngine() # Load the qml file into the engine 
    engine.load("/media/lee/LinWork/MyGit/lpc-funning/pyqt_ros/qml/main.qml") 
    engine.quit.connect(app.quit) 
    sys.exit(app.exec_())
