#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->centralWidget, &BthCentralWidget::scanClicked, this, [this](bool isActiveState){
        if(isActiveState){
            ui->peripheralWidget->resetWidget();
            ui->peripheralWidget->setEnabled(false);
        }
        else{
            ui->peripheralWidget->setEnabled(true);
        }
    });

    connect(ui->peripheralWidget, &BthPeripheralWidget::advertisingClicked, this, [this](bool isActiveState){
        if(isActiveState){
            ui->centralWidget->resetWidget();
            ui->centralWidget->setEnabled(false);
        }
        else{
            ui->centralWidget->setEnabled(true);
        }
    });

    connect(ui->peripheralWidget, &BthPeripheralWidget::emptyDeviceSelection, ui->clipboardWidget, &BthClipboardWidget::onAbsentDevice);
    connect(ui->centralWidget, &BthCentralWidget::emptyDeviceSelection, ui->clipboardWidget, &BthClipboardWidget::onAbsentDevice);

    connect(ui->peripheralWidget, &BthPeripheralWidget::deviceDataReceived, ui->clipboardWidget, &BthClipboardWidget::onDeviceDataReceived);
    connect(ui->centralWidget, &BthCentralWidget::deviceDataReceived, ui->clipboardWidget, &BthClipboardWidget::onDeviceDataReceived);

    connect(ui->peripheralWidget, &BthPeripheralWidget::deviceChanged, ui->clipboardWidget, &BthClipboardWidget::onDeviceChanged);
    connect(ui->centralWidget, &BthCentralWidget::deviceChanged, ui->clipboardWidget, &BthClipboardWidget::onDeviceChanged);

    connect(ui->clipboardWidget, &BthClipboardWidget::writeDeviceData, ui->peripheralWidget, &BthPeripheralWidget::deviceWriteData);
    connect(ui->clipboardWidget, &BthClipboardWidget::writeDeviceData, ui->centralWidget, &BthCentralWidget::deviceWriteData);
}

MainWindow::~MainWindow()
{
    delete ui;
}
