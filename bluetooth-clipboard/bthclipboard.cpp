#include "bthclipboard.h"

BthClipboard::BthClipboard(QObject *parent)
    :QObject(parent)
{

}

BthClipboard::~BthClipboard(){

}

void BthClipboard::copyToClipboard(QString clipboardText){

}

QVector<QString> BthClipboard::getClipboards(QBluetoothAddress address){
    return QVector<QString>();
}

void BthClipboard::clearClipboards(QBluetoothAddress address){

}

void BthClipboard::addClipboard(QBluetoothAddress address, QString data){

}
