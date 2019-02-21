#coding:utf-8
'''
用于将UI文件转换为Python 的界面文件
'''
import os
import glob
 

index=1 
path=os.path.dirname(__file__)
uis=glob.glob(os.path.join(path,"*.ui"))
for ui in uis:
    global out
    name=os.path.basename(ui).split(".")[0]
    out=os.path.join(path,name+".py")
    while os.path.exists(out):
        out=os.path.join(path,"%s-%s.py"%(name,index))
        index+=1
    command="pyuic5 %s -o %s"%(ui,out)
    os.system(command)