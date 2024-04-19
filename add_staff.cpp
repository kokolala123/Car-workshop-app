#include "add_staff.h"
#include "ui_add_staff.h"

add_staff::add_staff(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::add_staff)
{
    ui->setupUi(this);
    this->setWindowTitle("Add Window");

    connect(ui->finishbtn,SIGNAL(clicked(bool)),this,SLOT(on_finishbtn_clicked()),Qt::UniqueConnection);
}

add_staff::~add_staff()
{
    delete ui;
}

void add_staff::on_finishbtn_clicked()
{
    QString id = ui->idline->text();
    QString name = ui->nameline->text();
    QString status = ui->statusline->text();
    QString price = ui->priceline->text();
    QString sql = "insert into staffinfo(id, name, status, price) values('"+id+"','"+name+"','"+status+"','"+price+"')";

    if(id.isEmpty()||name.isEmpty()||status.isEmpty()||price.isEmpty()){
        emit existEmptyInput();
    }else{
        emit sendToBossData(sql);
    }
    this->hide();
}

