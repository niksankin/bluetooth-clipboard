#ifndef BTHCLIPBOARD_H
#define BTHCLIPBOARD_H

#include <QObject>
#include <QHash>
#include <QtBluetooth/QBluetoothAddress>

class BthClipboard : public QObject
{
    Q_OBJECT
public:
    BthClipboard();
    ~BthClipboard();

    void copyToClipboard(QString clipboardText);

    QVector<QString> getClipboards(QBluetoothAddress address);
    void clearClipboards(QBluetoothAddress address);
    void addClipboard(QBluetoothAddress address, QString data);

private:
    QHash<QString, QVector<QString>> clipboardsModel;
};

#endif // BTHCLIPBOARD_H
