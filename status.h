#ifndef STATUS_H
#define STATUS_H

#include <QWidget>

namespace Ui {
class set_status;
}

class set_status : public QWidget
{
    Q_OBJECT

signals:
    void clickBusy();
    void clickFree();

public:
    explicit set_status(QWidget *parent = nullptr);
    ~set_status();

private slots:
    void busyBtnClicked();
    void freeBtnClicked();
private:
    Ui::set_status *ui;
};

#endif // STATUS_H
