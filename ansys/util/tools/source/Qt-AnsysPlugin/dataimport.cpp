#include "dataimport.h"
#include "ui_dataimport.h"

/*��ģ�����ڵ���������ݲ�ת�� */

DataImport::DataImport(MatConfigure *parent) :
    QDialog(parent),
    ui(new Ui::DataImport)
{
    ui->setupUi(this);
    this->main=parent;
    this->InitializeDialog();
}

//��������
DataImport::~DataImport()
{
    delete ui;
}


//��ʼ������
void DataImport::InitializeDialog()
{
    this->ui->pushButton_xml->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    this->ui->pushButton_msg->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    QPoint center=main->geometry().center();
    this->move(center.x()-this->geometry().width()/2-10,center.y()-this->geometry().height()/2);
    this->setModal(true);//����ģ̬�Ի���
    connect(ui->pushButton_xml,&QPushButton::clicked,[this](){
        xmlfile = QFileDialog::getOpenFileName(this, tr("Open XmlFile"), ".", "XML Files(*.xml)");
        ui->lineEdit_xml->setText(xmlfile);
    });
    connect(ui->pushButton_msg,&QPushButton::clicked,[this](){
        msgfile = QFileDialog::getOpenFileName(this, tr("Open MsgFile"), ".", "MSG Files(*.msg)");
        ui->lineEdit_msg->setText(msgfile);
    });
    connect(ui->buttonBox,SIGNAL(clicked(QAbstractButton*)),this,SLOT(LoadTreeData(QAbstractButton*)));
}


//������ݵ����οؼ�
void DataImport::LoadTreeData(QAbstractButton* button)
{
    if(button==ui->buttonBox->button(QDialogButtonBox::Cancel))
    {
        return;
    }
    QFile xml_file(xmlfile);
    if(!xml_file.exists())
    {
        QMessageBox::information(this,tr("Tips"),tr("File Not Exists!").prepend("Xml"));
        return;
    }
    QFile msg_file(msgfile);
    if(!msg_file.exists())
    {
        QMessageBox::information(this,tr("Tips"),tr("File Not Exists!").prepend("Msg"));
        return;
    }
    this->main->PopulateTreeData(xmlfile.toStdString().c_str(),msgfile.toStdString().c_str());
}
