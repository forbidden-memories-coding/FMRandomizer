#include "imageloader.h"

ImageLoader::ImageLoader(QObject *parent) : QObject(parent)
{

}

bool ImageLoader::loadSlusMrg(QString slusPath, QString mrgPath)
{
    qDebug() << "Loading SLUS/MRG pair...";
    qDebug() << "SLUS path " << slusPath;
    qDebug() << "MRG path " << mrgPath;
    QFile slus(slusPath);
    QFile mrg(mrgPath);

    if (!slus.open(QIODevice::ReadOnly) || !mrg.open(QIODevice::ReadOnly))
    {
        return false;
    }

    m_slus.setDevice(&slus);
    m_mrg.setDevice(&mrg);


    return true;
}

bool ImageLoader::loadCueBin(QString cuePath)
{
    qDebug() << "Loading CUE/BIN pair...";
    return true;
}
