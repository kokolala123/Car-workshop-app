#ifndef ITEM_H
#define ITEM_H

#include <QWidget>

namespace Ui {
class add_parts;
}

class add_parts : public QWidget
{
    Q_OBJECT
signals:
    void parts_data(QString,float,float);
public:
    explicit add_parts(QWidget *parent = nullptr);
    ~add_parts();
private slots:
    void confirmBtnClicked();
private:
    Ui::add_parts *ui;
};

#endif // ITEM_H
