# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/media/lee/LinWork/MyGit/lpc-funning/pyqt_ros/ui/ui_main.ui'
#
# Created by: PyQt5 UI code generator 5.5.1
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_mainWindow(object):
    def setupUi(self, mainWindow):
        mainWindow.setObjectName("mainWindow")
        mainWindow.resize(977, 617)
        self.centerWindow = QtWidgets.QWidget(mainWindow)
        self.centerWindow.setObjectName("centerWindow")
        self.vtkWidget = QtWidgets.QWidget(self.centerWindow)
        self.vtkWidget.setGeometry(QtCore.QRect(10, 10, 511, 561))
        self.vtkWidget.setObjectName("vtkWidget")
        self.layoutWidget = QtWidgets.QWidget(self.centerWindow)
        self.layoutWidget.setGeometry(QtCore.QRect(530, 10, 431, 561))
        self.layoutWidget.setObjectName("layoutWidget")
        self.gridLayout = QtWidgets.QGridLayout(self.layoutWidget)
        self.gridLayout.setContentsMargins(10, 5, 10, 5)
        self.gridLayout.setObjectName("gridLayout")
        self.combo_infosys = QtWidgets.QComboBox(self.layoutWidget)
        self.combo_infosys.setObjectName("combo_infosys")
        self.combo_infosys.addItem("")
        self.combo_infosys.addItem("")
        self.combo_infosys.addItem("")
        self.gridLayout.addWidget(self.combo_infosys, 13, 1, 1, 1)
        self.edit_start_z = QtWidgets.QLineEdit(self.layoutWidget)
        self.edit_start_z.setText("")
        self.edit_start_z.setObjectName("edit_start_z")
        self.gridLayout.addWidget(self.edit_start_z, 8, 3, 1, 1)
        self.edit_start_x = QtWidgets.QLineEdit(self.layoutWidget)
        self.edit_start_x.setText("")
        self.edit_start_x.setObjectName("edit_start_x")
        self.gridLayout.addWidget(self.edit_start_x, 8, 1, 1, 1)
        self.label_xspace = QtWidgets.QLabel(self.layoutWidget)
        self.label_xspace.setObjectName("label_xspace")
        self.gridLayout.addWidget(self.label_xspace, 10, 0, 1, 1)
        self.btn_center = QtWidgets.QPushButton(self.layoutWidget)
        self.btn_center.setObjectName("btn_center")
        self.gridLayout.addWidget(self.btn_center, 7, 0, 1, 1)
        self.combo_boundaryid = QtWidgets.QComboBox(self.layoutWidget)
        self.combo_boundaryid.setObjectName("combo_boundaryid")
        self.combo_boundaryid.addItem("")
        self.combo_boundaryid.addItem("")
        self.gridLayout.addWidget(self.combo_boundaryid, 4, 3, 1, 1)
        self.label_sys = QtWidgets.QLabel(self.layoutWidget)
        self.label_sys.setObjectName("label_sys")
        self.gridLayout.addWidget(self.label_sys, 5, 0, 1, 1)
        self.check_polarsys = QtWidgets.QCheckBox(self.layoutWidget)
        self.check_polarsys.setObjectName("check_polarsys")
        self.gridLayout.addWidget(self.check_polarsys, 12, 3, 1, 1)
        self.label_syssize = QtWidgets.QLabel(self.layoutWidget)
        self.label_syssize.setObjectName("label_syssize")
        self.gridLayout.addWidget(self.label_syssize, 11, 0, 1, 1)
        self.combo_patternboundary = QtWidgets.QComboBox(self.layoutWidget)
        self.combo_patternboundary.setObjectName("combo_patternboundary")
        self.combo_patternboundary.addItem("")
        self.combo_patternboundary.addItem("")
        self.gridLayout.addWidget(self.combo_patternboundary, 4, 2, 1, 1)
        self.check_section = QtWidgets.QCheckBox(self.layoutWidget)
        self.check_section.setObjectName("check_section")
        self.gridLayout.addWidget(self.check_section, 5, 1, 1, 1)
        self.edit_xspace = QtWidgets.QLineEdit(self.layoutWidget)
        self.edit_xspace.setObjectName("edit_xspace")
        self.gridLayout.addWidget(self.edit_xspace, 10, 1, 1, 1)
        self.btn_xmlfile = QtWidgets.QPushButton(self.layoutWidget)
        self.btn_xmlfile.setObjectName("btn_xmlfile")
        self.gridLayout.addWidget(self.btn_xmlfile, 1, 3, 1, 1)
        self.label_boundarytype = QtWidgets.QLabel(self.layoutWidget)
        self.label_boundarytype.setObjectName("label_boundarytype")
        self.gridLayout.addWidget(self.label_boundarytype, 4, 0, 1, 1)
        self.check_model = QtWidgets.QCheckBox(self.layoutWidget)
        self.check_model.setObjectName("check_model")
        self.gridLayout.addWidget(self.check_model, 2, 1, 1, 1)
        self.btn_end = QtWidgets.QPushButton(self.layoutWidget)
        self.btn_end.setObjectName("btn_end")
        self.gridLayout.addWidget(self.btn_end, 9, 0, 1, 1)
        self.edit_center_y = QtWidgets.QLineEdit(self.layoutWidget)
        self.edit_center_y.setText("")
        self.edit_center_y.setObjectName("edit_center_y")
        self.gridLayout.addWidget(self.edit_center_y, 7, 2, 1, 1)
        self.label_yspace = QtWidgets.QLabel(self.layoutWidget)
        self.label_yspace.setObjectName("label_yspace")
        self.gridLayout.addWidget(self.label_yspace, 10, 2, 1, 1)
        self.edit_xmlfile = QtWidgets.QLineEdit(self.layoutWidget)
        self.edit_xmlfile.setText("")
        self.edit_xmlfile.setObjectName("edit_xmlfile")
        self.gridLayout.addWidget(self.edit_xmlfile, 1, 1, 1, 2)
        self.label_xmlfile = QtWidgets.QLabel(self.layoutWidget)
        self.label_xmlfile.setObjectName("label_xmlfile")
        self.gridLayout.addWidget(self.label_xmlfile, 1, 0, 1, 1)
        self.edit_result = QtWidgets.QPlainTextEdit(self.layoutWidget)
        self.edit_result.setPlainText("")
        self.edit_result.setObjectName("edit_result")
        self.gridLayout.addWidget(self.edit_result, 15, 0, 1, 4)
        self.edit_cdbfile = QtWidgets.QLineEdit(self.layoutWidget)
        self.edit_cdbfile.setText("")
        self.edit_cdbfile.setObjectName("edit_cdbfile")
        self.gridLayout.addWidget(self.edit_cdbfile, 0, 1, 1, 2)
        self.combo_sys = QtWidgets.QComboBox(self.layoutWidget)
        self.combo_sys.setObjectName("combo_sys")
        self.combo_sys.addItem("")
        self.combo_sys.addItem("")
        self.gridLayout.addWidget(self.combo_sys, 5, 3, 1, 1)
        self.btn_cdbfile = QtWidgets.QPushButton(self.layoutWidget)
        self.btn_cdbfile.setObjectName("btn_cdbfile")
        self.gridLayout.addWidget(self.btn_cdbfile, 0, 3, 1, 1)
        self.btn_selnode = QtWidgets.QPushButton(self.layoutWidget)
        self.btn_selnode.setObjectName("btn_selnode")
        self.gridLayout.addWidget(self.btn_selnode, 13, 0, 1, 1)
        self.combo_infotype = QtWidgets.QComboBox(self.layoutWidget)
        self.combo_infotype.setObjectName("combo_infotype")
        self.combo_infotype.addItem("")
        self.combo_infotype.addItem("")
        self.combo_infotype.addItem("")
        self.combo_infotype.addItem("")
        self.combo_infotype.addItem("")
        self.combo_infotype.addItem("")
        self.combo_infotype.addItem("")
        self.combo_infotype.addItem("")
        self.combo_infotype.addItem("")
        self.combo_infotype.addItem("")
        self.combo_infotype.addItem("")
        self.combo_infotype.addItem("")
        self.combo_infotype.addItem("")
        self.gridLayout.addWidget(self.combo_infotype, 13, 2, 1, 1)
        self.edit_end_y = QtWidgets.QLineEdit(self.layoutWidget)
        self.edit_end_y.setText("")
        self.edit_end_y.setObjectName("edit_end_y")
        self.gridLayout.addWidget(self.edit_end_y, 9, 2, 1, 1)
        self.combo_result = QtWidgets.QComboBox(self.layoutWidget)
        self.combo_result.setObjectName("combo_result")
        self.combo_result.addItem("")
        self.combo_result.addItem("")
        self.combo_result.addItem("")
        self.combo_result.addItem("")
        self.combo_result.addItem("")
        self.combo_result.addItem("")
        self.combo_result.addItem("")
        self.combo_result.addItem("")
        self.combo_result.addItem("")
        self.combo_result.addItem("")
        self.combo_result.addItem("")
        self.combo_result.addItem("")
        self.gridLayout.addWidget(self.combo_result, 2, 3, 1, 1)
        self.edit_p3 = QtWidgets.QLineEdit(self.layoutWidget)
        self.edit_p3.setText("")
        self.edit_p3.setObjectName("edit_p3")
        self.gridLayout.addWidget(self.edit_p3, 6, 3, 1, 1)
        self.edit_center_x = QtWidgets.QLineEdit(self.layoutWidget)
        self.edit_center_x.setText("")
        self.edit_center_x.setObjectName("edit_center_x")
        self.gridLayout.addWidget(self.edit_center_x, 7, 1, 1, 1)
        self.edit_p1 = QtWidgets.QLineEdit(self.layoutWidget)
        self.edit_p1.setText("")
        self.edit_p1.setObjectName("edit_p1")
        self.gridLayout.addWidget(self.edit_p1, 6, 1, 1, 1)
        self.label_cdbfile = QtWidgets.QLabel(self.layoutWidget)
        self.label_cdbfile.setObjectName("label_cdbfile")
        self.gridLayout.addWidget(self.label_cdbfile, 0, 0, 1, 1)
        self.combo_patternmodel = QtWidgets.QComboBox(self.layoutWidget)
        self.combo_patternmodel.setObjectName("combo_patternmodel")
        self.combo_patternmodel.addItem("")
        self.combo_patternmodel.addItem("")
        self.gridLayout.addWidget(self.combo_patternmodel, 2, 2, 1, 1)
        self.check_boundary = QtWidgets.QCheckBox(self.layoutWidget)
        self.check_boundary.setObjectName("check_boundary")
        self.gridLayout.addWidget(self.check_boundary, 4, 1, 1, 1)
        self.btn_start = QtWidgets.QPushButton(self.layoutWidget)
        self.btn_start.setObjectName("btn_start")
        self.gridLayout.addWidget(self.btn_start, 8, 0, 1, 1)
        self.label_model = QtWidgets.QLabel(self.layoutWidget)
        self.label_model.setObjectName("label_model")
        self.gridLayout.addWidget(self.label_model, 2, 0, 1, 1)
        self.edit_yspace = QtWidgets.QLineEdit(self.layoutWidget)
        self.edit_yspace.setObjectName("edit_yspace")
        self.gridLayout.addWidget(self.edit_yspace, 10, 3, 1, 1)
        self.check_polar = QtWidgets.QCheckBox(self.layoutWidget)
        self.check_polar.setObjectName("check_polar")
        self.gridLayout.addWidget(self.check_polar, 12, 0, 1, 1)
        self.btn_saveconf = QtWidgets.QPushButton(self.layoutWidget)
        self.btn_saveconf.setObjectName("btn_saveconf")
        self.gridLayout.addWidget(self.btn_saveconf, 13, 3, 1, 1)
        self.edit_ptsize = QtWidgets.QLineEdit(self.layoutWidget)
        self.edit_ptsize.setObjectName("edit_ptsize")
        self.gridLayout.addWidget(self.edit_ptsize, 11, 3, 1, 1)
        self.label_ptsize = QtWidgets.QLabel(self.layoutWidget)
        self.label_ptsize.setObjectName("label_ptsize")
        self.gridLayout.addWidget(self.label_ptsize, 11, 2, 1, 1)
        self.check_localsys = QtWidgets.QCheckBox(self.layoutWidget)
        self.check_localsys.setObjectName("check_localsys")
        self.gridLayout.addWidget(self.check_localsys, 12, 2, 1, 1)
        self.check_worldsys = QtWidgets.QCheckBox(self.layoutWidget)
        self.check_worldsys.setObjectName("check_worldsys")
        self.gridLayout.addWidget(self.check_worldsys, 12, 1, 1, 1)
        self.edit_end_z = QtWidgets.QLineEdit(self.layoutWidget)
        self.edit_end_z.setText("")
        self.edit_end_z.setObjectName("edit_end_z")
        self.gridLayout.addWidget(self.edit_end_z, 9, 3, 1, 1)
        self.edit_p2 = QtWidgets.QLineEdit(self.layoutWidget)
        self.edit_p2.setText("")
        self.edit_p2.setObjectName("edit_p2")
        self.gridLayout.addWidget(self.edit_p2, 6, 2, 1, 1)
        self.edit_center_z = QtWidgets.QLineEdit(self.layoutWidget)
        self.edit_center_z.setText("")
        self.edit_center_z.setObjectName("edit_center_z")
        self.gridLayout.addWidget(self.edit_center_z, 7, 3, 1, 1)
        self.edit_start_y = QtWidgets.QLineEdit(self.layoutWidget)
        self.edit_start_y.setText("")
        self.edit_start_y.setObjectName("edit_start_y")
        self.gridLayout.addWidget(self.edit_start_y, 8, 2, 1, 1)
        self.combo_patternsection = QtWidgets.QComboBox(self.layoutWidget)
        self.combo_patternsection.setObjectName("combo_patternsection")
        self.combo_patternsection.addItem("")
        self.combo_patternsection.addItem("")
        self.gridLayout.addWidget(self.combo_patternsection, 5, 2, 1, 1)
        self.edit_end_x = QtWidgets.QLineEdit(self.layoutWidget)
        self.edit_end_x.setText("")
        self.edit_end_x.setObjectName("edit_end_x")
        self.gridLayout.addWidget(self.edit_end_x, 9, 1, 1, 1)
        self.edit_syssize = QtWidgets.QLineEdit(self.layoutWidget)
        self.edit_syssize.setObjectName("edit_syssize")
        self.gridLayout.addWidget(self.edit_syssize, 11, 1, 1, 1)
        self.label_sys_2 = QtWidgets.QLabel(self.layoutWidget)
        self.label_sys_2.setObjectName("label_sys_2")
        self.gridLayout.addWidget(self.label_sys_2, 6, 0, 1, 1)
        mainWindow.setCentralWidget(self.centerWindow)
        self.statusbar = QtWidgets.QStatusBar(mainWindow)
        self.statusbar.setObjectName("statusbar")
        mainWindow.setStatusBar(self.statusbar)
        self.menuBar = QtWidgets.QMenuBar(mainWindow)
        self.menuBar.setGeometry(QtCore.QRect(0, 0, 977, 23))
        self.menuBar.setObjectName("menuBar")
        mainWindow.setMenuBar(self.menuBar)
        self.actionUpdatenode = QtWidgets.QAction(mainWindow)
        self.actionUpdatenode.setObjectName("actionUpdatenode")

        self.retranslateUi(mainWindow)
        QtCore.QMetaObject.connectSlotsByName(mainWindow)

    def retranslateUi(self, mainWindow):
        _translate = QtCore.QCoreApplication.translate
        mainWindow.setWindowTitle(_translate("mainWindow", "Ansys调试器"))
        self.combo_infosys.setItemText(0, _translate("mainWindow", "总体坐标系"))
        self.combo_infosys.setItemText(1, _translate("mainWindow", "截面坐标系"))
        self.combo_infosys.setItemText(2, _translate("mainWindow", "截面柱坐标系"))
        self.label_xspace.setText(_translate("mainWindow", "径向间距"))
        self.btn_center.setText(_translate("mainWindow", "选择圆心"))
        self.combo_boundaryid.setItemText(0, _translate("mainWindow", "5"))
        self.combo_boundaryid.setItemText(1, _translate("mainWindow", "10"))
        self.label_sys.setText(_translate("mainWindow", "截面显示"))
        self.check_polarsys.setText(_translate("mainWindow", "显示截面柱坐标"))
        self.label_syssize.setText(_translate("mainWindow", "坐标系大小"))
        self.combo_patternboundary.setItemText(0, _translate("mainWindow", "网格模式"))
        self.combo_patternboundary.setItemText(1, _translate("mainWindow", "线框模式"))
        self.check_section.setText(_translate("mainWindow", "显示截面"))
        self.edit_xspace.setText(_translate("mainWindow", "10"))
        self.btn_xmlfile.setText(_translate("mainWindow", "选择XML文件"))
        self.label_boundarytype.setText(_translate("mainWindow", "边界显示"))
        self.check_model.setText(_translate("mainWindow", "显示模型"))
        self.btn_end.setText(_translate("mainWindow", "选择终点"))
        self.label_yspace.setText(_translate("mainWindow", "环向间距"))
        self.label_xmlfile.setText(_translate("mainWindow", "结果文件"))
        self.combo_sys.setItemText(0, _translate("mainWindow", "笛卡尔"))
        self.combo_sys.setItemText(1, _translate("mainWindow", "柱坐标"))
        self.btn_cdbfile.setText(_translate("mainWindow", "选择CDB文件"))
        self.btn_selnode.setText(_translate("mainWindow", "选择节点"))
        self.combo_infotype.setItemText(0, _translate("mainWindow", "Stress"))
        self.combo_infotype.setItemText(1, _translate("mainWindow", "Displace"))
        self.combo_infotype.setItemText(2, _translate("mainWindow", "Sx"))
        self.combo_infotype.setItemText(3, _translate("mainWindow", "Sy"))
        self.combo_infotype.setItemText(4, _translate("mainWindow", "Sz"))
        self.combo_infotype.setItemText(5, _translate("mainWindow", "Sxy"))
        self.combo_infotype.setItemText(6, _translate("mainWindow", "Syz"))
        self.combo_infotype.setItemText(7, _translate("mainWindow", "Sxz"))
        self.combo_infotype.setItemText(8, _translate("mainWindow", "Seqv"))
        self.combo_infotype.setItemText(9, _translate("mainWindow", "Ux"))
        self.combo_infotype.setItemText(10, _translate("mainWindow", "Uy"))
        self.combo_infotype.setItemText(11, _translate("mainWindow", "Uz"))
        self.combo_infotype.setItemText(12, _translate("mainWindow", "Usum"))
        self.combo_result.setItemText(0, _translate("mainWindow", "无"))
        self.combo_result.setItemText(1, _translate("mainWindow", "Seqv"))
        self.combo_result.setItemText(2, _translate("mainWindow", "Usum"))
        self.combo_result.setItemText(3, _translate("mainWindow", "Sx"))
        self.combo_result.setItemText(4, _translate("mainWindow", "Sy"))
        self.combo_result.setItemText(5, _translate("mainWindow", "Sz"))
        self.combo_result.setItemText(6, _translate("mainWindow", "Sxy"))
        self.combo_result.setItemText(7, _translate("mainWindow", "Syz"))
        self.combo_result.setItemText(8, _translate("mainWindow", "Sxz"))
        self.combo_result.setItemText(9, _translate("mainWindow", "Ux"))
        self.combo_result.setItemText(10, _translate("mainWindow", "Uy"))
        self.combo_result.setItemText(11, _translate("mainWindow", "Uz"))
        self.label_cdbfile.setText(_translate("mainWindow", "网格文件"))
        self.combo_patternmodel.setItemText(0, _translate("mainWindow", "网格模式"))
        self.combo_patternmodel.setItemText(1, _translate("mainWindow", "线框模式"))
        self.check_boundary.setText(_translate("mainWindow", "显示边界"))
        self.btn_start.setText(_translate("mainWindow", "选择起点"))
        self.label_model.setText(_translate("mainWindow", "模型显示"))
        self.edit_yspace.setText(_translate("mainWindow", "30"))
        self.check_polar.setText(_translate("mainWindow", "数值输出"))
        self.btn_saveconf.setText(_translate("mainWindow", "保存配置"))
        self.edit_ptsize.setText(_translate("mainWindow", "1"))
        self.label_ptsize.setText(_translate("mainWindow", "节点大小"))
        self.check_localsys.setText(_translate("mainWindow", "显示截面坐标"))
        self.check_worldsys.setText(_translate("mainWindow", "显示总体坐标"))
        self.combo_patternsection.setItemText(0, _translate("mainWindow", "网格模式"))
        self.combo_patternsection.setItemText(1, _translate("mainWindow", "线框模式"))
        self.edit_syssize.setText(_translate("mainWindow", "5"))
        self.label_sys_2.setText(_translate("mainWindow", "截面节点号"))
        self.actionUpdatenode.setText(_translate("mainWindow", "更新节点信息"))

