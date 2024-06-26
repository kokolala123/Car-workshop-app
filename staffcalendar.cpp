#include "staffcalendar.h"
#include "ui_staff_calender.h"

staff_calender::staff_calender(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::staff_calender)
{
    ui->setupUi(this);

    connect(ui->calendarWidget,SIGNAL(clicked(QDate)),this, SLOT(onCalenderClicked(QDate)));

    connect(ui->savebtn,SIGNAL(clicked()),this,SLOT(saveBtnClicked()));
    //------------------------------------------------------------------------------------





    //------------------------------------------------------------------------------------
    //Define database Qsqlite
    calenderdb = QSqlDatabase::addDatabase("QSQLITE","sqlite2");
    calenderdb.setDatabaseName("calenderinfo.db");
    calenderdb.open();
    if(calenderdb.open()){
        //qDebug is similar with std::cout
        qDebug()<<"Connected to SQL Calender Server!";
    }else{
        //Output connect fail reason
        qDebug()<<"Failed to connect to SQL Sever: "<< calenderdb.lastError().text();//Need include QSqlError header here
    }
    QSqlQuery query(calenderdb);
    query.exec("create table calenderinfo(name, date, status)");//create only once

    QSqlQuery queryForModel("select * from calenderinfo",calenderdb);
    qmodel = new QSqlQueryModel(this);//we use this model to fullfill the table
    qmodel->setQuery(std::move(queryForModel));

    ui->tableView->setModel(qmodel);//include QSqlQueryModel


}

staff_calender::~staff_calender()
{
    delete ui;
}

void staff_calender::get_name_from_query(QString name){

    ui->staffnamebtn->setText(name);
    //We can store name in a member varivale!!!
    this->currentName = name;

}

void staff_calender::onCalenderClicked(const QDate& date){

 QString dateString = date.toString();

    setPage = new set_status();
    setPage->show();

    QSqlQuery query(calenderdb);
    QString sqlInsert = "insert into calenderinfo(name, date) values('"+this->currentName+"','"+dateString+"')";
    query.exec(sqlInsert);
    QSqlQuery queryForDisplayModel("select * from calenderinfo",calenderdb);
    qmodel->setQuery(std::move(queryForDisplayModel));

    //Do button here
    connect(setPage,&set_status::clickFree,this,[=](){
        getFreeBtnClicked(dateString);
    });
    connect(setPage,&set_status::clickBusy,this,[=](){
        getBusyBtnClicked(dateString);
    });


}

void staff_calender::getBusyBtnClicked(QString date){
    //qDebug()<<"Clicked busy";
    QSqlQuery query(calenderdb);
    //QString sqlInsert = "insert into calenderinfo(status) values('busy')";
    QString sqlUpdate = "update calenderinfo set status = 'busy' where name = '"+this->currentName+"' and date = '"+date+"'";
    //query.exec(sqlInsert);
    query.exec(sqlUpdate);
    QSqlQuery queryForDisplayModel("select * from calenderinfo",calenderdb);
    qmodel->setQuery(std::move(queryForDisplayModel));
}

void staff_calender::getFreeBtnClicked(QString date){
    //qDebug()<<"Clicked free";
    QSqlQuery query(calenderdb);
    //QString sqlInsert = "insert into calenderinfo(status) values('free')";
    QString sqlUpdate = "update calenderinfo set status = 'free' where name = '"+this->currentName+"' and date = '"+date+"'";
    //query.exec(sqlInsert);
    query.exec(sqlUpdate);
    QSqlQuery queryForDisplayModel("select * from calenderinfo",calenderdb);
    qmodel->setQuery(std::move(queryForDisplayModel));
}

void staff_calender::exportToPdf(){
    QPdfWriter pdfWriter("staff calender.pdf");//set output path

    QPainter painter(&pdfWriter);//link painter with pdfWriter

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial",10));

    QSqlQuery query(calenderdb);
    QString sql = "select * from calenderinfo";
    if (!query.exec(sql)) {
        qDebug() << "Error executing SQL query:" << query.lastError().text();
        return;
    }/*
    int row=0;
    while(query.next()){
        qDebug()<<"insidewhile";
        for(int col=0;col < query.record().count(); ++col){

            qDebug()<<"query value: "<<query.value(col).toString();
        }
        ++row;
    }*/
    int row = 0;
    int cellWidth = 1500;
    int cellHeight = 200;
    int startX = 50;
    int startY = 100;
    while(query.next()){

        for (int col = 0; col < query.record().count(); ++col) {
            QString data = query.value(col).toString();
            painter.drawText(startX + col * cellWidth, startY + row * cellHeight, data);
        }
        ++row;
    }
    painter.end();
     QMessageBox::about(this,"Notice","PDF file saved!");
}

void staff_calender::saveBtnClicked(){
    qDebug()<<"Save clicked!";
    this->exportToPdf();
}
