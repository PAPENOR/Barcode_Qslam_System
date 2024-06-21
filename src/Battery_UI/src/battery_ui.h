#ifndef BATTERY_UI_H
#define BATTERY_UI_H

#include <QWidget>

namespace Ui {
class Battery_UI;
}

class Battery_UI : public QWidget
{
    Q_OBJECT

public:
    explicit Battery_UI(QWidget *parent = nullptr);
    ~Battery_UI();

private:
    Ui::Battery_UI *ui;
};

#endif // BATTERY_UI_H
