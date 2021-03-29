#ifndef BTHCLIPBOARD_H
#define BTHCLIPBOARD_H

#include <QObject>
#include <QHash>
#include <QClipboard>

class BthClipboard : public QObject
{
    Q_OBJECT
public:
    explicit BthClipboard(QObject *parent = nullptr);
    ~BthClipboard();

    void copyToClipboard(QString clipboardText);
    QString getClipboard();

    QVector<QString> getDeviceClipboards(const QString& id);
    void clearClipboards(const QString& id);
    void addClipboard(const QString& id, QString data);

private:
    QHash<QString, QVector<QString>> clipboardsModel;
    QClipboard* clipboard = nullptr;
};

#endif // BTHCLIPBOARD_H
