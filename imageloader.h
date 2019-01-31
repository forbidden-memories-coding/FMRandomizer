#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QObject>
#include <QDebug>

class QDataStream;

class ImageLoader : public QObject
{
    Q_OBJECT
public:
    explicit ImageLoader(QObject *parent = nullptr);
    ~ImageLoader();

    Q_INVOKABLE bool loadSlusMrg(QString slusPath, QString mrgPath);
    Q_INVOKABLE bool loadCueBin(QString binPath);

signals:

public slots:

private:
    QDataStream *m_slus;
    QDataStream *m_mrg;

};

#endif // IMAGELOADER_H
