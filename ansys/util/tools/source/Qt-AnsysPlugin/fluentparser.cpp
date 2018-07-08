#include "fluentparser.h"
#include "ui_fluentparser.h"
#include "pugixml.hpp"
using namespace pugi;
using namespace std;

/*��ģ������ת��fluent���� */

FluentParser::FluentParser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FluentParser)
{
    ui->setupUi(this);
    this->Initialize();
}

FluentParser::~FluentParser()
{
    delete ui;
}

//����ÿһ������
QStringList FluentParser::getDataItems(QString line)
{
    QStringList items;
    //ȥ���հ���
    for(QString item:line.split(separator)){
        item=item.trimmed();
        if (!item.isEmpty()) {
            items.append(item);
        }
    }
    return items;
}


//����ļ���ʽ�Ƿ���ȷ,�����طָ����ͽ������
bool FluentParser::isFluentResultFileInvalid()
{
    results.clear();//�������
    QFile file(ui->lineEdit_txtFile->text());
    if(!file.open(QIODevice::ReadOnly))
    {
        separator="";
        return true;
    }
    //��1������
    QString resultLine=file.readLine().trimmed();
    file.close();//�ر�
    separator=resultLine.contains(",")?",":resultLine.contains(" ")?" ":"";
    for(QString result:this->getDataItems(resultLine))
    {
        results.append(resultMapTransformer.value(result,result));
    }
    return separator.isEmpty();

}

//�鿴��Щ������ͱ�ѡ��
QVector<int> FluentParser::getExportIndexs()
{
    QVector<int> index;
    for (int i = 0; i < ui->treeView->topLevelItemCount(); ++i) {
        if(ui->treeView->topLevelItem(i)->checkState(0)==Qt::Checked)
        {
            index.push_back(i);
        }
    }
    return index;
}

//���������ļ�
void FluentParser::exportMesh(QString cas_file,QString cdb_file)
{
    QFile in(cas_file);
    QFile out(cdb_file);
    if(in.open(QIODevice::ReadOnly))
    {
        this->getCasMeshText(in);//cas����
        if(out.open(QIODevice::WriteOnly))
        {
            this->exportProperty(out);//д����Ŀ����
            this->exportNBlock(out);//д���ڵ���Ϣ
            this->exportEBlock(out);//д����Ԫ��Ϣ
            this->exportBBlock(out);//д���߽���Ϣ
            out.close();
        }
        in.close();
    }


}

//��ʼ��
void FluentParser::Initialize()
{
    this->setFixedSize(this->width(),this->height());//�̶����ڴ�С
    this->setWindowIcon(QIcon(":/ANSYS.ico"));//����ͼ��
    this->ui->btn_casFile->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    this->ui->btn_cdbFile->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    this->ui->btn_txtFile->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    this->ui->btn_xmlFile->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    this->setWindowTitle(QString::fromLocal8Bit("Fluent���ת��"));
    resultList=QStringList::fromStdList({"Id","Ux","Uy","Uz"});
    this->ui->treeView->setColumnCount(1);//����
    this->ui->treeView->setColumnWidth(0,150);//���
    this->ui->treeView->setHeaderLabel(QString::fromLocal8Bit("�������"));//���������
    this->ui->comboBox_caseID->addItems({"1","2","3","4","5","6","7","8","9"});//�������ID
    this->ui->comboBox_Units->addItems({"MPA","SI"});//��λ���

    //�������������ӳ�䵽XMLԪ������
    resultMapTransformer["nodenumber"]="Id";
    resultMapTransformer["x-coordinate"]="Ux";
    resultMapTransformer["y-coordinate"]="Uy";
    resultMapTransformer["z-coordinate"]="Uz";
    resultMapTransformer["pressure"]="P";
    resultMapTransformer["pressure-coefficient"]="Cp";
    resultMapTransformer["dynamic-pressure"]="Dp";
    resultMapTransformer["absolute-pressure"]="Ap";
    resultMapTransformer["total-pressure"]="Tp";
    ui->checkBox_mesh->setChecked(true);
    ui->checkBox_result->setChecked(true);

    ////////////////////////////////////////�źŲ��¼�/////////////////
    //// ѡ��fluent �������txt�ļ�
    connect(ui->btn_txtFile,&QPushButton::clicked,[this](){
        QString txtFile = QFileDialog::getOpenFileName(this, tr("Open Fluent Result Text File"), ".", "TxT Files(*.txt)").trimmed();
        ui->lineEdit_txtFile->setText(txtFile);//����ļ�·��
        if(txtFile.isEmpty()){return;}//δѡ���ļ�
        //����ļ���ʽ��
        if(isFluentResultFileInvalid())
        {
            QMessageBox::information(this,tr("Tips"),tr("Please Check the Format of Fluent Result File!"));
            ui->lineEdit_txtFile->setFocus();//�����ļ�·��
            return;
        }
        ui->treeView->clear();
        for(QString result:results)
        {
            QTreeWidgetItem* result_item=new QTreeWidgetItem(QStringList::fromStdList({tr(result.toStdString().c_str())}));
            bool isUseless=resultList.contains(result);
            result_item->setCheckState(0,isUseless?Qt::Unchecked:Qt::Checked);
            ui->treeView->addTopLevelItem(result_item);
            result_item->setHidden(isUseless);
        }
    });
    ////ѡ��ANSYS��xml����ļ�����·��
    connect(ui->btn_xmlFile,&QPushButton::clicked,[this](){
        QString ansysResultFile = QFileDialog::getSaveFileName(this, tr("Open Ansys Result Xml File"), ".", "Xml Files(*.xml)");
        ui->lineEdit_xmlFile->setText(ansysResultFile);
    });
    ////ѡ�����fluent CAS�ļ�·��
    connect(ui->btn_casFile,&QPushButton::clicked,[this](){
        QString casFile = QFileDialog::getOpenFileName(this, tr("Open Fluent cas File"), ".", "Cas Files(*.cas)");
        ui->lineEdit_casFile->setText(casFile);
    });
    ////ѡ�����ansys CDB�ļ�·��
    connect(ui->btn_cdbFile,&QPushButton::clicked,[this](){
        QString cdbFile = QFileDialog::getSaveFileName(this, tr("Open Ansys cdb File"), ".", "Cdb Files(*.cdb)");
        ui->lineEdit_cdbFile->setText(cdbFile);
    });

    connect(ui->checkBox_mesh,&QCheckBox::clicked,[this](bool ischecked){
        this->ui->groupBox_mesh->setEnabled(ischecked);
    });

    connect(ui->checkBox_result,&QCheckBox::clicked,[this](bool ischecked){
        this->ui->groupBox_result->setEnabled(ischecked);
    });

    //// ����ansys ���xml�ļ���cdb����
    connect(ui->btn_Export,&QPushButton::clicked,[this](){
        QString msg=this->ValidateInputData();
        if(!msg.isEmpty())
        {
            QMessageBox::information(this, tr("Error"),msg);
            return;
        }
        if(ui->checkBox_mesh->isChecked())
        {
            this->exportMesh(ui->lineEdit_casFile->text(),ui->lineEdit_cdbFile->text());
        }
        if(ui->checkBox_result->isChecked())
        {
            this->exportResult(ui->lineEdit_txtFile->text(),ui->lineEdit_xmlFile->text());
        }

        QMessageBox::information(this, tr("Tips"),tr("Succeccfully Export!"));
    });

    ////�˳�
    connect(ui->btn_Exit,&QPushButton::clicked,[this](){
        this->close();
    });
}

//����Casģ���ļ��еĵ�Ԫ������
void FluentParser::getCasMeshText(QFile &in)
{
    nodeData.swap(QVector<QVector<double>>());//��սڵ�����
    meshData.swap(QMultiHash<int,QVector<int>>());//��յ�Ԫ����
    boundaryData.swap(QHash<QString,int>());//��ձ߽絥Ԫ����
    QRegExp rx("\\(.*\\((.*)?\\)");
    while (!in.atEnd()) {
        QString line=in.readLine();
        //ƥ�������ݵ�λ��
        if(line.startsWith("(13") && !line.endsWith("))\n"))
        {
            line.indexOf(rx);//����ƥ��
            QStringList infoList=rx.cap(1).split(" ");//�ָ�
            int face_start=infoList[1].toInt(0,16);//�������ʼ���
            int face_end=infoList[2].toInt(0,16);//�������ֹ���
            int face_type=infoList[3].toInt(0,16);//����������
            int node_num=infoList[4].toInt();//��õ�Ԫ�ڵ���Ŀ
            in.readLine();//������һ�е�")"
            for (int i = face_start; i <= face_end; ++i) {
                line=in.readLine();//��ȡ1������
                QVector<int> face;//��
                QStringList nodes=line.trimmed().replace(")","").split(" ");//�ָ��ַ���
                int count=node_num?node_num:nodes[0].toInt();//���node_num=0,��Ԫ�ڵ������ڵ�1����
                int j=node_num?0:1;//���node_num=0,���1��ʼ����
                for (; j < nodes.size(); ++j) {
                    int node_id=nodes[j].toInt(0,16);//�ڵ�ID
                    if(count>0)
                    {
                        face.push_back(node_id);//����ڵ㵽��
                    }
                    else
                    {
                        if(node_id!=0)
                        {
                            meshData.insert(node_id,face);//���뵥Ԫ��,���node_idΪ��Ԫ��
                            //����߽絥Ԫ��4-�����  5-������  10-�ٶȽ���
                            if (boundaryTypeVector.contains(face_type)) {
                                QStringList strList;
                                QVector<int> boundaryFace(face);//���Ʊ߽���
                                qSort(boundaryFace.begin(),boundaryFace.end(),qGreater<int>());//����
                                for (int node:boundaryFace) {
                                    strList.append(QString("%1").arg(node));//ת��Ϊ�ַ��б�
                                }

                                boundaryData[strList.join("-")]=face_type;//����ڵ��������ַ�����Ϊ��ֵ�����ϣ��
                            }

                        }
                    }
                    count--;
                }
            }
        }
        //ƥ��߽���Ϣ��λ��
        else if(line.startsWith("(10 (") && !line.endsWith("))\n"))
        {
            line.indexOf(rx);//����ƥ��
            QStringList infoList=rx.cap(1).split(" ");//�ָ�
            int node_start=infoList[1].toInt(0,16);//��ýڵ���ʼ���
            int node_end=infoList[2].toInt(0,16);//��ýڵ���ֹ���
            in.readLine();//������һ�е�")"
            for (int i = node_start; i <= node_end; ++i) {
                line=in.readLine();//��ȡ1������
                QVector<double> xyz;
                QStringList nodes=line.trimmed().replace(")","").split(" ");//�ָ��ַ���
                for (QString node:nodes) {
                    if(!node.trimmed().isEmpty())
                    {
                        xyz.push_back(node.toDouble());
                    }
                }
                nodeData.push_back(xyz);
            }
        }
    }
}

//д����Ŀ��Ϣ��xml
void FluentParser::exportProperty(QFile &out)
{
    QString projectType("!FLUENT EXPORT\n");
    QString projectName("*SET,_PROJECT_NAME,'%1'\n");
    QString projectProperty("*SET,_PROJECT_PROPERTY,'%1'\n");

    out.write(projectType.toStdString().c_str());//��Ŀ����Fluent
    out.write(projectName.arg(ui->lineEdit_projectName->text()).toStdString().c_str());//��Ŀ����
    out.write(projectProperty.arg(ui->lineEdit_projectDetail->text()).toStdString().c_str());//��Ŀ����
}

//д����Ԫ���˹�ϵ��CDB
void FluentParser::exportEBlock(QFile &out)
{
    int elementid=1;
    //�߶�����
    QVector<QVector<int>> orders{{{0,1},{1,2},{2,3},{3,0}}};
    //�ڵ�ӳ��
    QHash<int,int> map;
    char buffer[256];//ÿһ����Ԫ�������
    QSet<int> keys=meshData.keys().toSet();
    int ele_sum=keys.size();
    //д��EBLOCK��ʶ
    sprintf(buffer,"EBLOCK,%d,SOLID,%10d,%10d\n",19,ele_sum,ele_sum);
    out.write(buffer);
    out.write("(19i9)\n");
    for(int key:keys)
    {
        QList<QVector<int>> ele=meshData.values(key);//������Ԫ
        int face_num=ele.size();//��Ԫ�����
        QVector<int> f0;
        int n;//����
        switch (face_num) {
        //����6����ڵ��˳���ع�6����
        case 6:
            map.clear();
            f0=ele[0];//��0����Ԫ��
            for (n= 1; n < 6; ++n)
            {
                for(auto order:orders)
                {
                    int p1=ele[n].at(order[0]);//�߶εĶ˵�1
                    int p2=ele[n].at(order[1]);//�߶εĶ˵�2
                    //����˵�1��f0��,�˵�2����f0��
                    if(f0.contains(p1) && !f0.contains(p2))
                    {
                        map.insert(p1,p2);
                    }
                    if(f0.contains(p2) && !f0.contains(p1))
                    {
                        map.insert(p2,p1);
                    }
                }
            }
            sprintf(buffer,"%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d\n",
                    1,1,1,1,0,0,0,0,8,0,elementid,f0[0],f0[1],f0[2],f0[3],map[f0[0]],map[f0[1]],map[f0[2]],map[f0[3]]);
            out.write(buffer);
            elementid++;//��Ԫ���+1
            break;
        //����5����ڵ��˳���ع�5����
        case 5:
            map.clear();
            for (auto e:ele)
            {
                if(e.size()==3){
                    f0=e;
                    break;
                }
            }
            for(auto e:ele){
                if(e.size()==3)continue;
                for(auto order:orders)
                {
                    int p1=e.at(order[0]);//�߶εĶ˵�1
                    int p2=e.at(order[1]);//�߶εĶ˵�2
                    //����˵�1��f0��,�˵�2����f0��
                    if(f0.contains(p1) && !f0.contains(p2))
                    {
                        map.insert(p1,p2);
                    }
                    if(f0.contains(p2) && !f0.contains(p1))
                    {
                        map.insert(p2,p1);
                    }
                }
            }
            sprintf(buffer,"%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d\n",
                    1,1,1,1,0,0,0,0,8,0,elementid,f0[0],f0[1],f0[2],f0[2],map[f0[0]],map[f0[1]],map[f0[2]],map[f0[2]]);
            out.write(buffer);
            elementid++;//��Ԫ���+1
            break;
        case 4:
            f0.append(ele[0]);
            f0.append(ele[1]);
            f0=f0.toList().toSet().toList().toVector();
            sprintf(buffer,"%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d%9d\n",
                    1,1,1,1,0,0,0,0,8,0,elementid,f0[0],f0[1],f0[2],f0[2],f0[3],f0[3],f0[3],f0[3]);
            out.write(buffer);
            elementid++;//��Ԫ���+1
            break;
        }
    }
}

//д���ڵ�����λ�����ݵ�CDB
void FluentParser::exportNBlock(QFile &out)
{
    int nodeid=1;//�ڵ����
    char buffer[200];
    int node_sum=nodeData.size();
    sprintf(buffer,"NBLOCK,%d,SOLID,%10d,%10d\n",6,node_sum,node_sum);
    out.write(buffer);
    out.write("(3i9,6e21.13e3)\n");
    //    out.write(QString("NBLOCK,%1,SOLID,%2,%3").arg(6).arg(node_sum,10,10).arg(node_sum,10,10).toStdWString());
    for (auto node:nodeData) {
        sprintf(buffer,"%9d%9d%9d%21.13e%21.13e%21.13e\n",nodeid,0,0,node[0],node[1],node[2]);
        out.write(buffer);
        nodeid++;
    }
}


//����߽���Ϣ
void FluentParser::exportBBlock(QFile &out)
{
    QList<QString> boundaryFaces=boundaryData.keys();
    int faceNum=boundaryFaces.size();
    char buffer[200];
    sprintf(buffer,"BBLOCK,%d,SOLID,%10d,%10d\n",6,faceNum,faceNum);
    out.write(buffer);
    out.write("(1i10,1i40,1i10)\n");
    int faceid=1;//�����
    for(auto face:boundaryFaces){
        sprintf(buffer,"%10d%40s%10d\n",faceid,face.toStdString().c_str(),boundaryData[face]);
        out.write(buffer);
        faceid++;
    }

}

//������Ϣ��֤
QString FluentParser::ValidateInputData()
{
    if(!ui->checkBox_mesh->isChecked() && !ui->checkBox_result->isChecked()) {return tr("no export type was select!");}
    if(ui->lineEdit_projectName->text().trimmed().isEmpty()){return tr("projectname is empty!");}
    if(ui->checkBox_mesh->isChecked())
    {
        if(ui->lineEdit_casFile->text().trimmed().isEmpty()){return tr("casfile is empty!");}
        if(ui->lineEdit_cdbFile->text().trimmed().isEmpty()){return tr("cdbfile is empty!");}
    }
    if(ui->checkBox_result->isChecked())
    {
        if(ui->lineEdit_txtFile->text().trimmed().isEmpty()){return tr("txtfile is empty!");}
        if(ui->lineEdit_caseName->text().trimmed().isEmpty()){return tr("casename is empty!");}
        if(ui->lineEdit_xmlFile->text().trimmed().isEmpty()){return tr("xmlfile is empty!");}
        if(this->getExportIndexs().length()==0){return tr("result type is empty!");}
    }

    return "";
}

//void FluentParser::initializeDB()
//{
//    //    QString dbfile="d:\\data.db";
//    //    db.setDatabaseName(dbfile);
//    //    QSqlQuery query(db); //����ִ�����QSL���
//    //    query
//    //    if (db.open()) {
//    //        query.exec("create table if not exists faces ("
//    //                   "id INTEGER PRIMARY KEY AUTOINCREMENT,nodenum TINYINT, elementid INT,"
//    //                   "node0 INT,node1 INT,node2 INT,node3 INT,node4 INT,node5 INT,node6 INT,node7 INT)");
//    ////        query.exec("insert into faces values(NULL, 1,2,3,4,5,6,7,8,9,10)");
//    ////    }
//    //    query.exec("select * from faces");
//    //    while (query.next()) {
//    //        qDebug()<<query.value(0).toInt();
//    //    }
//    //    db.close();
//}

//��������ļ�
void FluentParser::exportResult(QString txt_file,QString xml_file)
{
    QFile txtfile(txt_file);
    if(!txtfile.open(QIODevice::ReadOnly) || separator.isEmpty())
    {
        return;
    }
    QVector<int> index=getExportIndexs();
    xml_document doc;
    xml_node node_declare=doc.prepend_child(node_declaration);
    node_declare.append_attribute("version")="1.0";
    node_declare.append_attribute("encoding")="UTF-8";
    xml_node node_root=doc.append_child("Results");//Results���ڵ�
    xml_node node_project=node_root.append_child("Project");//��Ŀ�ڵ�
    node_project.append_attribute("name")=ui->lineEdit_projectName->text().toStdString().c_str();//��Ŀ�ڵ��name����
    xml_node node_case=node_project.append_child("Case");//�����ڵ�
    node_case.append_attribute("id")=ui->comboBox_caseID->currentText().toInt();//�����ڵ��id����
    node_case.append_attribute("name")=ui->lineEdit_caseName->text().toStdString().c_str();//�����ڵ��name����
    node_case.append_attribute("property")=ui->lineEdit_caseDetail->text().toStdString().c_str();//�����ڵ��property����
    txtfile.readLine();//������һ�б�ͷ
    int count=0;
    while(!txtfile.atEnd())
    {
        QStringList nodeDataList=this->getDataItems(txtfile.readLine().trimmed());
        if(nodeDataList.length())
        {
            count++;
            xml_node node_node=node_project.append_child("Node");//�ڵ�ڵ�
            node_node.append_attribute("id")=nodeDataList[0].toStdString().c_str();
            for(int i:index)
            {
                node_node.append_child(results[i].toStdString().c_str()).text()=nodeDataList[i].toStdString().c_str();
            }
            if(count%100==0){this->statusBar()->showMessage(QString("Node%1").arg(count));}
        }
    }
    doc.save_file(xml_file.toStdString().c_str(),"\t",format_no_escapes,encoding_utf8);
    this->statusBar()->showMessage(tr("Result File Successfully Saved!"),1000);
}
