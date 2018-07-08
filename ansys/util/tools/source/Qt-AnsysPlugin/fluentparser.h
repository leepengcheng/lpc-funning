#ifndef FLUENTPARSER_H
#define FLUENTPARSER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QRegExp>

namespace Ui {
class FluentParser;
}

class FluentParser : public QMainWindow
{
    Q_OBJECT

public:
    explicit FluentParser(QWidget *parent = 0);
    ~FluentParser();

private:
    Ui::FluentParser *ui;
    QString     separator;//����ļ��ָ���
    QStringList results;//�������
    QStringList resultList;
    QStringList getDataItems(QString line);
    QHash<QString,QString> resultMapTransformer;
    QMultiHash<int,QVector<int>> meshData;//����cas�ļ��õ��ĵ�Ԫ��Ϣ
    QHash<QString,int>  boundaryData;//����cas�ļ��õ��ı߽絥Ԫ��Ϣ
    QVector<QVector<double>>   nodeData;//����cas�ļ��õ��Ľڵ���Ϣ
    const QVector<int> boundaryTypeVector=QVector<int>({4,5,10,20});//�߽����ʹ��ż�����
//    4	pressure-inlet, inlet-vent, intake-fan
//    5	pressure-outlet, exhaust-fan, outlet-vent
//    10	velocity-inlet
//    20	mass-flow-inlet
    bool isFluentResultFileInvalid();//�ж�flunet txt����ļ���ʽ�Ƿ���ȷ
    QVector<int> getExportIndexs();
    void exportResult(QString,QString);//����XML
    void exportMesh(QString,QString);//����CDB
    void Initialize();//��ʼ��
    void getCasMeshText(QFile&);//����Cas�ļ�
    void exportProperty(QFile &out);//������Ŀ��Ϣ
    void exportEBlock(QFile &out);//������Ԫ��Ϣ���ļ�
    void exportNBlock(QFile &out);//�����ڵ���Ϣ���ļ�
    void exportBBlock(QFile &out);//�����߽絥Ԫ��Ϣ
    QString ValidateInputData();//������Ϣ��֤
};

#endif // FLUENTPARSER_H
