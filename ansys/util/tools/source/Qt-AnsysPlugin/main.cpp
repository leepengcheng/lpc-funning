#include <QApplication>
#include "ansysdataplot.h"
#include "matconfigure.h"
#include "fluentparser.h"
using namespace std;
/*���������  �������� ���ݴ���ı���������ͬ��ģ�� */
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QTranslator translator;//���ʻ�
    translator.load(":/cn.qm");
    a.installTranslator(&translator);
    //ֱ�ӵ��EXE ��Ч
    if (argc == 1){return 1;}
    //��������
    const char* moduleName=argv[1];
    //����fluentת��ģ��
    if (strcmp(moduleName,"fluent")==0)
    {
        FluentParser* fluentParser=new FluentParser();
        fluentParser->show();//��ʾfluentת������
    }
    //�������Ϲ���ģ��
    else if(strcmp(moduleName,"mat")==0)
    {
        MatConfigure* matConfig=new MatConfigure();
        matConfig->show();//��ʾMat�������ý���
    }
    else
    {
        //�������߻�ͼģ�飬����Ĳ���Ϊxml��ʽ�Ĳ���
        AnsysDataPlot *w = new AnsysDataPlot();
        if (w->parseXYData(argv[1])!= 0) {
            //��ʾ��������
            w->getEarthQuakePlot();
            w->show();
        }
    }
    return a.exec();
}
