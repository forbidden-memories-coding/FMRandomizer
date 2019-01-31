#include "imageloader.h"
#include "binreader.h"
#include <QFile>
#include <QDataStream>

ImageLoader::ImageLoader(QObject *parent) : QObject(parent)
{
    m_slus = new QDataStream();
    m_mrg = new QDataStream();
}

ImageLoader::~ImageLoader()
{
    delete m_slus;
    delete m_mrg;
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

    m_slus->setDevice(&slus);
    m_mrg->setDevice(&mrg);

    qDebug() << "SLUS open status: " << m_slus->status();
    qDebug() << "MRG open status: " << m_mrg->status();

    slus.close();
    mrg.close();

    return true;
}

bool ImageLoader::loadCueBin(QString binPath)
{
    qDebug() << "Loading CUE/BIN pair...";
    qDebug() << "BIN path" << binPath;

    QFile bin(binPath);
    if (!bin.open(QFile::ReadOnly))
    {
        return false;
    }

    QDataStream binStr(&bin);
    binStr.setByteOrder(QDataStream::LittleEndian);

    BinReader reader(&binStr);


    // Move to SLUS, chunk number of SLUS is 24th
    const uint slusPos = 24;
    reader.seek(slusPos);
    const uint slusSize = 0x1D0800;
    const uint slusChunks = slusSize / DATA_SIZE;
    QByteArray slusData = reader.readChunk(slusChunks);

    // Write SLUS file
    QFile slus("c:/SLUS_014.11");
    slus.open(QIODevice::Truncate | QIODevice::ReadWrite);
    QDataStream slusStr(&slus);
    slusStr.writeRawData(slusData.data(), slusData.size());
    slus.close();

    // Move to MRG, chunk number of MRG is 10102nd
    const uint mrgPos = 10102;
    reader.seek(mrgPos);
    const uint mrgSize = 0x2400000;
    const uint mrgChunks = mrgSize / DATA_SIZE;
    QByteArray mrgData = reader.readChunk(mrgChunks);

    // Write MRG file
    QFile mrg("c:/WA_MRG.MRG");
    mrg.open(QIODevice::Truncate | QIODevice::ReadWrite);
    QDataStream mrgStr(&mrg);
    mrgStr.writeRawData(mrgData.data(), mrgData.size());
    mrg.close();


    bin.close();

    return true;
}
