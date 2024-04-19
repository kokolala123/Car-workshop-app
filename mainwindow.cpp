#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPushButton"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    this->setWindowTitle("Car Workshop Management System");

    this->boss_use_page = new bossUse;//construct bossUse page class



    connect(ui->bossbtn,&QPushButton::clicked, [=](){
        //hide mainwindow
        this->hide();
        //show boss window
        this->boss_use_page->show();
    });


    connect(this->boss_use_page, &bossUse::backFromBossUse,[=](){
        this->boss_use_page->hide();
        this->show();
    });

    connect(ui->employeebtn,SIGNAL(clicked()),this,SLOT(employeeBtnClicked()),Qt::UniqueConnection);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::check_staff_name(QStringList list){
    qDebug()<<"LIST CONTENT: "<<list.at(0);
}


void MainWindow::employeeBtnClicked(){

    this->hide();
    this->staff_use_page = new repairDlg;
    this->staff_use_page->show();
    connect(this->staff_use_page,SIGNAL(staff_name(QString)),this,SLOT(get_staff_name(QString)));
}


void MainWindow::get_staff_name(QString name){
    this->staff_name=name;


}
