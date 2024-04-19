#include "calender_query.h"
#include "ui_calender_query.h"

calender_query::calender_query(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::calender_query)
{
    ui->setupUi(this);
    connect(ui->confirmbtn, SIGNAL(clicked()),this,SLOT(confirmbtn_clicked()),Qt::UniqueConnection);
}

calender_query::~calender_query()
{
    delete ui;
}

void calender_query::confirmbtn_clicked()
{
    staffCalenderPage = new staff_calender();
    staffCalenderPage->show();
    this->hide();
    QString sql = ui->enterline->text();
    emit name_data(sql);
}

void calender_query::dontGetName(){
    //QThread::msleep(0);
    staffCalenderPage->hide();

}

void calender_query::getName(QString namedata){

    qDebug()<<namedata<<"In query";
    connect(this,SIGNAL(send_name_to_calender(QString)),staffCalenderPage,SLOT(get_name_from_query(QString)));
    emit send_name_to_calender(namedata);
}
