#include "bthclipboard.h"

#include <QGuiApplication>

BthClipboard::BthClipboard(QObject *parent)
    :QObject(parent)
{
    clipboard = QGuiApplication::clipboard();
}

BthClipboard::~BthClipboard(){
    clipboard = nullptr;
}

void BthClipboard::copyToClipboard(QString clipboardText){
    clipboard->setText(clipboardText);
}

QString BthClipboard::getClipboard(){
    return clipboard->text();
}

QVector<QString> BthClipboard::getDeviceClipboards(const QString& id){
    return clipboardsModel[id];
}

void BthClipboard::clearClipboards(const QString& id){
    clipboardsModel[id].clear();
}

void BthClipboard::addClipboard(const QString& id, QString data){
    clipboardsModel[id].append(data);
}
