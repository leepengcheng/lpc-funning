#include "ansysdataplot.h"
using namespace pugi;
using namespace std;

/*��ģ�����ڻ������� */
AnsysDataPlot::AnsysDataPlot(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //����ͼ��
    this->setWindowIcon(QIcon(":/ANSYS.ico"));
}


//��ͼ���¼���
void AnsysDataPlot::getEarthQuakePlot()
{
    //��Ӽ�ͷ
    ui->customPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->customPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    //���¼�
    connect(ui->customPlot,SIGNAL(legendClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)),\
            this,SLOT(showData(QCPLegend*)));
    connect(ui->customPlot,SIGNAL(mousePress(QMouseEvent*)),this,SLOT(showPointXY(QMouseEvent*)));
    //����λ�úʹ�С
    this->setGeometry(geometry);
    this->centralWidget()->setFixedSize(geometry.size());
    //���ñ�����
    this->setWindowTitle(title);

    //�����������ǩ����
    ui->customPlot->xAxis->setLabel(xlabel);
    ui->customPlot->yAxis->setLabel(ylabel);
	//������������ʾ��Χ,��������ֻ�ܿ���Ĭ�ϵķ�Χ
    ui->customPlot->graph()->rescaleAxes();
    double x_maxval=*max_element(x_max.begin(),x_max.end());
    double y_maxval=*max_element(y_max.begin(),y_max.end());
    double x_minval=*min_element(x_min.begin(),x_min.end());
    double y_minval=*min_element(y_min.begin(),y_min.end());
    ui->customPlot->xAxis->setRange(x_minval*1.2,x_maxval*1.2);
    ui->customPlot->yAxis->setRange(y_minval*1.5,y_maxval*1.5);
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 150));
	//���ý���
    ui->customPlot->setInteractions(QCP::iSelectLegend | QCP::iSelectOther
                                    |QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables|QCP::iSelectItems|QCP::iMultiSelect);
	//�ػ�
	ui->customPlot->replot();
}


//��������Ĳ���
int AnsysDataPlot::parseXYData(const char *xmlstring)
{
    xml_document doc;
    xml_parse_result result=doc.load_string(xmlstring);
    if(result.status!=xml_parse_status::status_ok)
    {
        return 0;
    }
    //���ڵ� root
    xml_node node_root=doc.document_element();
    //////////////////////��������///////////////////////////////////////////
    //���ô��ڱ���
    title = QString::fromLocal8Bit(node_root.attribute("title").value());
    //X���ǩ
    xlabel = QString::fromLocal8Bit(node_root.attribute("xlabel").value());
    //Y���ǩ
    ylabel = QString::fromLocal8Bit(node_root.attribute("ylabel").value());
    //���ø������λ�úʹ�С
    QString  geoString(node_root.attribute("geometry").value());
    geoString.replace("x","+");
    QStringList list=geoString.split("+");
    geometry.setRect(list[2].toInt(),list[3].toInt(),list[0].toInt(),list[1].toInt());
    //////////////////////////��������////////////////////////////////////////////////////
    xpath_node_set graphs=doc.select_nodes("//graph");
    for(xpath_node_set::const_iterator graph=graphs.begin();graph!=graphs.end();graph++)
    {
        this->createGraph(graph->node());
    }
    return 1;
}

AnsysDataPlot::~AnsysDataPlot()
{
	delete ui;
}

//״̬����ʾ����
void AnsysDataPlot::showData(QCPLegend* plottable)
{
    this->statusBar()->showMessage(plottable->objectName(),2000);
}

//��ʾ������λ��
void AnsysDataPlot::showPointXY(QMouseEvent* event)
{
//    QCPGraphDataContainer* points = ui->customPlot->graph(0)->data().data();
//    for(int i=0;i<points->size();i++)
//    {
//        qDebug()<<points->at(i)->key;
//    }
    if(event->button()==Qt::MouseButton::LeftButton)
    {
        double x=ui->customPlot->xAxis->pixelToCoord(event->pos().x());
        double y=ui->customPlot->yAxis->pixelToCoord(event->pos().y());
        QString str=QString("%1--%2").arg(x).arg(y);
        ui->statusBar->showMessage(str,2000);
    }

}

//����ͼ��
void AnsysDataPlot::createGraph(xml_node node_graph)
{
    //���һ������
    ui->customPlot->addGraph();
    //��ȡX Y������
    xml_node node_x=node_graph.child("xlist");
    xml_node node_y=node_graph.child("ylist");
    QVector<double> xdata,ydata;
    //��ȡXML�е�X���Y����ַ������ݲ����зָ�
    QStringList xDataList=QString(node_x.child_value()).split(" ");
    QStringList yDataList=QString(node_y.child_value()).split(" ");
    //ת���ַ�������ΪDouble��
    for(int i=0;i<xDataList.length();i++)
    {
        xdata.append(xDataList[i].toDouble());
        ydata.append(yDataList[i].toDouble());
    }
    //�������ߵ����ֵ���뵽x_max y_max�б�
    x_max.append(*max_element(xdata.begin(),xdata.end()));
    y_max.append(*max_element(ydata.begin(),ydata.end()));
    //�������ߵ���Сֵ���뵽x_min y_min�б�
    x_min.append(*min_element(xdata.begin(),xdata.end()));
    y_min.append(*min_element(ydata.begin(),ydata.end()));
    //�������
    ui->customPlot->graph()->setData(xdata, ydata);
    //������ýڵ�
    xml_node node_style=node_graph.child("style");
     //�������ݵ�����
    ui->customPlot->graph()->setName(QString::fromLocal8Bit(node_style.attribute("legend").value()));

    //��������ʾ���
    QString line(node_style.attribute("line").value());
    if (!line.isEmpty()) {
        QStringList linecolors=line.split(" ");
        //����ɫ
        QColor line_pen(linecolors[0]);
        //��ˢ��ɫ
        QColor line_brush(linecolors[1]);
        //��ˢ͸����
        line_brush.setAlphaF(linecolors[2].toDouble());
        ui->customPlot->graph()->setPen(line_pen);
        ui->customPlot->graph()->setBrush(QBrush(QColor(line_brush)));
    } else {
        ui->customPlot->graph()->setLineStyle(QCPGraph::lsNone);
    }

   //�������ݵ���
    QString point(node_style.attribute("point").value());
    if (!point.isEmpty()) {
        QStringList pointcolors=point.split(" ");
        //����Ȧ��ɫ
        QColor point_pen(pointcolors[0]);
        //����Ȧ��ɫ
        QColor point_brush(pointcolors[1]);
        ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,QPen(point_pen),QBrush(point_brush),pointcolors[2].toInt()));
    } else
    {
        ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot));
    }
}


