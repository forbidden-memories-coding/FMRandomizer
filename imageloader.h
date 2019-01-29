#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDataStream>

class ImageLoader : public QObject
{
    Q_OBJECT
public:
    explicit ImageLoader(QObject *parent = nullptr);

    Q_INVOKABLE bool loadSlusMrg(QString slusPath, QString mrgPath);
    Q_INVOKABLE bool loadCueBin(QString cuePath);

signals:

public slots:

private:
    QDataStream m_slus;
    QDataStream m_mrg;

};

#endif // IMAGELOADER_H
