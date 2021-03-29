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
    ui->peripheralWidget->hide();

    connect(static_cast<BthCentralWidget*>(ui->centralWidget), &BthCentralWidget::emptyDeviceSelection, ui->clipboardWidget, &BthClipboardWidget::onAbsentDevice);
    connect(static_cast<BthCentralWidget*>(ui->centralWidget), &BthCentralWidget::deviceDataReceived, ui->clipboardWidget, &BthClipboardWidget::onDeviceDataReceived);
    connect(static_cast<BthCentralWidget*>(ui->centralWidget), &BthCentralWidget::deviceChanged, ui->clipboardWidget, &BthClipboardWidget::onDeviceChanged);
    connect(ui->clipboardWidget, &BthClipboardWidget::writeDeviceData, static_cast<BthCentralWidget*>(ui->centralWidget), &BthCentralWidget::deviceWriteData);
#else
    ui->centralWidget->hide();

    connect(static_cast<BthPeripheralWidget*>(ui->peripheralWidget), &BthPeripheralWidget::emptyDeviceSelection, ui->clipboardWidget, &BthClipboardWidget::onAbsentDevice);
    connect(static_cast<BthPeripheralWidget*>(ui->peripheralWidget), &BthPeripheralWidget::deviceDataReceived, ui->clipboardWidget, &BthClipboardWidget::onDeviceDataReceived);
    connect(static_cast<BthPeripheralWidget*>(ui->peripheralWidget), &BthPeripheralWidget::deviceChanged, ui->clipboardWidget, &BthClipboardWidget::onDeviceChanged);
    connect(ui->clipboardWidget, &BthClipboardWidget::writeDeviceData, static_cast<BthPeripheralWidget*>(ui->peripheralWidget), &BthPeripheralWidget::deviceWriteData);

#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}
