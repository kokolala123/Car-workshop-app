#include "bossuse.h"
#include "ui_bossuse.h"
#include "QPushButton"
bossUse::bossUse(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::bossUse)
{
    ui->setupUi(this);
    this->setWindowTitle("Staff Infomation");





    //------------------------------------------------------------------------------------
    connect(ui->backbtn, &QPushButton::clicked,[=](){

        emit this->backFromBossUse();
    });



     //receive string data from add page
    connect(ui->addbtn, SIGNAL(clicked()), this, SLOT(addbtn_clicked()),Qt::UniqueConnection);

    connect(ui->firebtn, SIGNAL(clicked()), this, SLOT(firebtn_clicked()),Qt::UniqueConnection);

    connect(ui->calenderbtn,SIGNAL(clicked()),this,SLOT(calenderbtn_clicked()),Qt::UniqueConnection);

    //------------------------------------------------------------------------------------

    staffdb = QSqlDatabase::addDatabase("QSQLITE","sqlite1");
    staffdb.setDatabaseName("staffinfo.db");

    if(!staffdb.open()){

        qDebug()<<"Failed to connect to SQL Sever: " << staffdb.lastError().text();
    }else{
        qDebug()<<"Connected to SQL Sever";

        QSqlQuery query1(staffdb);

        query1.exec("create table staffinfo(id, name, status, price)");//create only once

        QSqlQuery queryForModel("select * from staffinfo", staffdb);
        qmodel = new QSqlQueryModel(this);

        qmodel->setQuery(std::move(queryForModel));
        ui->tableView->setModel(qmodel);
        }
}

bossUse::~bossUse()
{
    QSqlQuery query1(staffdb);

    query1.finish();


    staffdb.close();

    QSqlDatabase::removeDatabase("sqlite1");
    delete ui;
}

void bossUse::send_name_list(){
    QStringList names;
    QSqlQuery query1("select name from staffinfo", staffdb);
    while (query1.next()) {
        QString data = query1.value(1).toString();
        names.append(query1.value(1).toString());
    }
    emit sendStaffList(names);
    // emit sendStaffList();
}



void bossUse::addbtn_clicked(){
    addPage = new add_staff();//create addpage window

    connect(addPage,SIGNAL(existEmptyInput()),this,SLOT(haveEmptyInput()),Qt::UniqueConnection);

    disconnect(addPage,SIGNAL(sendToBossData(QString)),this,SLOT(getFromAddStaffData(QString)));
    connect(addPage,SIGNAL(sendToBossData(QString)),this,SLOT(getFromAddStaffData(QString)),Qt::UniqueConnection);
    addPage->show();
}

void bossUse::getFromAddStaffData(QString data){
    QSqlQuery query1(staffdb);
    connect(addPage,SIGNAL(existEmptyInput()),this,SLOT(haveEmptyInput()));

    query1.exec(data);
    QMessageBox::about(this,"Noice","Add successful!");
     QSqlQuery queryForModel("select * from staffinfo", staffdb);
    qmodel->setQuery(std::move(queryForModel));
}

void bossUse::haveEmptyInput(){
    QMessageBox::about(this,"Notice","Can't input empty parameter!");
}

void bossUse::firebtn_clicked()
{
    deletePage = new delete_staff();
    connect(deletePage,SIGNAL(deleteWrongInput()),this,SLOT(deleteInvalidStaff()));

    disconnect(deletePage, SIGNAL(sendDeleteData(QString)),this,SLOT(getFromDeleteStaffData(QString)));
    connect(deletePage, SIGNAL(sendDeleteData(QString)),this,SLOT(getFromDeleteStaffData(QString)),Qt::UniqueConnection);
    deletePage->show();
}

void bossUse::deleteInvalidStaff(){
    QMessageBox::about(this,"Notice","Delete failed!");
}



void bossUse::getFromDeleteStaffData(QString name){
    QSqlQuery query1(staffdb);
    QString sql_delete = "delete from staffinfo where name='"+name+"'";
    QString sql_select = "select name from staffinfo where name = '"+name+"'";
    query1.exec(sql_select);
    if(query1.next()){
        //Data exits, do operations
        query1.exec(sql_delete);

        QMessageBox::about(this,"Noice","Fire successful!");        
    }else{
        QMessageBox::about(this,"Notice","Fire failed!");
    }   
    QSqlQuery queryForModel("select * from staffinfo", staffdb);
    qmodel->setQuery(std::move(queryForModel));
}

void bossUse::calenderbtn_clicked()
{
    calender_query_page = new calender_query();
    calender_query_page->show();

    connect(calender_query_page,SIGNAL(name_data(QString)),this, SLOT(getFromCalenderQueryData(QString)),Qt::UniqueConnection);

}

void bossUse::getFromCalenderQueryData(QString namedata){
    qDebug()<<namedata;
    QSqlQuery query1(staffdb);

    QString sql_select_name = "select name from staffinfo where name = '"+namedata+"'";
    query1.exec(sql_select_name);
    if(query1.next()){

        qDebug()<<"Data exists!";

        connect(this, SIGNAL(haveName(QString)),calender_query_page,SLOT(getName(QString)));
        emit haveName(namedata);

    }
    else{
        qDebug()<<"Not exist in this database!";


        connect(this, SIGNAL(dontHaveName()),calender_query_page,SLOT(dontGetName()),Qt::UniqueConnection);
        emit dontHaveName();
        QThread::msleep(500);
        QMessageBox::about(this,"Warning","Input staff name invalid!");
    }
}


