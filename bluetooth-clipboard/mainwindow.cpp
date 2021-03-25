#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bthcentralwidget.h"
#include "bthperipheralwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#ifdef Q_OS_ANDROID
    BthCentralWidget* widget = new BthCentralWidget(ui->widget->parentWidget());
    ui->verticalLayout->replaceWidget(ui->widget, widget);

    connect(static_cast<BthCentralWidget*>(ui->widget), &BthCentralWidget::emptyDeviceSelection, ui->clipboardWidget, &BthClipboardWidget::onAbsentDevice);
    connect(static_cast<BthCentralWidget*>(ui->widget), &BthCentralWidget::deviceDataReceived, ui->clipboardWidget, &BthClipboardWidget::onDeviceDataReceived);
    connect(static_cast<BthCentralWidget*>(ui->widget), &BthCentralWidget::deviceChanged, ui->clipboardWidget, &BthClipboardWidget::onDeviceChanged);
    connect(ui->clipboardWidget, &BthClipboardWidget::writeDeviceData, static_cast<BthCentralWidget*>(ui->widget), &BthCentralWidget::deviceWriteData);
#else
    BthPeripheralWidget* widget = new BthPeripheralWidget(ui->widget->parentWidget());
    ui->verticalLayout->replaceWidget(ui->widget, widget);

    connect(static_cast<BthPeripheralWidget*>(ui->widget), &BthPeripheralWidget::emptyDeviceSelection, ui->clipboardWidget, &BthClipboardWidget::onAbsentDevice);
    connect(static_cast<BthPeripheralWidget*>(ui->widget), &BthPeripheralWidget::deviceDataReceived, ui->clipboardWidget, &BthClipboardWidget::onDeviceDataReceived);
    connect(static_cast<BthPeripheralWidget*>(ui->widget), &BthPeripheralWidget::deviceChanged, ui->clipboardWidget, &BthClipboardWidget::onDeviceChanged);
    connect(ui->clipboardWidget, &BthClipboardWidget::writeDeviceData, static_cast<BthPeripheralWidget*>(ui->widget), &BthPeripheralWidget::deviceWriteData);

#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}
