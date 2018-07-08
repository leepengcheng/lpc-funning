#include "matdataparse.h"
#include <QDir>
//#include <random>
//#include <ctime>


/*���Ϲ���ģ�����οؼ���������� */

TreeData::TreeData(const char *xmlfile, const char *msgfile)
{
    xml_document doc;
    xml_parse_result result=doc.load_file(xmlfile);
    if(result.status!=xml_parse_status::status_ok)
    {
        return;
    }
    //�ڵ㷭���ֵ�
    this->parseMaterialMsg(msgfile);//��ò��ϵ�id ��property
    xpath_node_set type_set=doc.select_nodes("//Type");
    int row=0;
    int col=0;
    for(auto node:type_set)
    {
        xml_node type_node=node.node();
        QString type_key=type_node.attribute("id").value();
        QString type_name=matNameHashMap.value(type_key,type_key);
        QTreeWidgetItem* type_item=new QTreeWidgetItem(QStringList({type_name,""}));
//        type_item->setIcon(0,getRootPixMap(row));//������ͼ�� ʡ�ĳ�Ƥ
        for(auto mat_node:type_node.children())
        {
            QString mat_key=mat_node.attribute("id").value();
            QString mat_name=matNameHashMap.value(mat_key,mat_key);
            QString mat_data =mat_node.text().as_string();
            QTreeWidgetItem* mat_item=new QTreeWidgetItem(QStringList({mat_name,mat_data}));
//            mat_item->setIcon(0,getSubPixMap(row,col));//������ͼ�� ʡ�ĳ�Ƥ
            mat_item->setToolTip(0,mat_data);//��ʾ
            type_item->addChild(mat_item);
            col++;
        }
        this->widgetItemList.push_back(type_item);
        row++;
    }
}

//����MSG�ļ�
void TreeData::parseMaterialMsg(const char* msgfile)
{
    matNameHashMap.clear();//����ֵ�
    QFile file(msgfile);
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        return;
    }
    while(!file.atEnd())
    {
        QByteArray line=file.readLine().trimmed();
        if (line.contains("{") || line.contains("}"))
        {
            continue;
        }
        else
        {
            QList<QByteArray> strList=line.split(' ');
            QString key=strList[0].replace("\"","");
            QString val=(*strList.rbegin()).replace("\"","");
            matNameHashMap.insert(key,val);
        }
    }
}

//��ò���������ĳ�ֲ���ͼ��
QPixmap TreeData::getSubPixMap(int row, int col)
{
    QPixmap* pixMap=new QPixmap(":/sprite.png");
    int rowNum=7;
    int colNum=11;
    int r=row%rowNum;//ȡ��
    int c=col%(colNum-1)+1;//ȡ��
    return pixMap->copy(c*64,r*64,64,64);

}

//��ò������͵�ͼ��
QPixmap TreeData::getRootPixMap(int row)
{
    QPixmap* pixMap=new QPixmap(":/sprite.png");
    int rowNum=7;
    int r=row%rowNum;//ȡ��
    return pixMap->copy(0,r*64,64,64);
}

