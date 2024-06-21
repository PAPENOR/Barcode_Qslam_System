#include "battery_ui.h"
#include "ui_battery_ui.h"

Battery_UI::Battery_UI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Battery_UI)
{
    ui->setupUi(this);
}

Battery_UI::~Battery_UI()
{
    delete ui;
}
