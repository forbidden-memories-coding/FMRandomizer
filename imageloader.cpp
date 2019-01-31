#include "imageloader.h"
#include <QFile>
#include <QDataStream>

#define CEILING(x, y) ((x+(y-1))/y)

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

    // Move to SLUS file
    binStr.skipRawData(0x0000DC98);

    // Check SLUS header
    const uint headLen = 8;
    char slusHeader[] = "PS-X EXE";
    char slusHeaderRead[headLen+1];
    slusHeader[headLen] = '\0';
    binStr.readRawData(slusHeader, headLen);

    qDebug() << "SLUS header " << slusHeader;

    if (strcmp(slusHeaderRead, slusHeader))
    {
        return false;
    }

    // Read SLUS and extract it
    const uint slusSize = 0x1D0800 - headLen;
    char* slusData = new char[slusSize];
    int er = binStr.readRawData(slusData, slusSize);
    qDebug() << "Read bytes " << er;
    if (er == -1)
    {
        return false;
    }

    QFile slus(QString("c:/SLUS_014.11"));
    slus.open(QIODevice::Truncate | QIODevice::ReadWrite);
    QDataStream slusStr(&slus);
    slusStr.setByteOrder(QDataStream::BigEndian);
    slusStr.writeRawData(slusHeader, headLen);
    slusStr.writeRawData(slusData, slusSize);
    slus.close();

    delete[] slusData;

    // Move to WA_MRG file
    auto skipped = binStr.skipRawData(0x14CA7A0);

    qDebug() << "Bytes skipped " << skipped;

    // Check WA_MRG header
    const uint mrgHeadLen = 13;
    char mrgHeader[] = "23.+37752.366";
    char mrgHeaderRead[mrgHeadLen+1];
    mrgHeaderRead[mrgHeadLen] = '\0';
    binStr.readRawData(mrgHeaderRead, mrgHeadLen);

    QByteArray readBytes(mrgHeaderRead);
    auto readHex = readBytes.toHex(' ');

    QByteArray headBytes(mrgHeader);
    auto headHex = headBytes.toHex(' ');

    qDebug() << "MRG header bytes " << headHex;
    qDebug() << "MRG header " << mrgHeader;

    qDebug() << "MRG read header bytes " << readHex;
    qDebug() << "MRG read header " << mrgHeaderRead;

    if (strcmp(mrgHeaderRead, mrgHeader))
    {
        return false;
    }

    // Read WA_MRG and extract it
    const uint mrgSize = 0x2400000;
    const uint parts = 8;
    const uint mrgPartSize = mrgSize / parts;
    QFile mrg(QString("c:/WA_MRG.MRG"));
    mrg.open(QIODevice::Truncate | QIODevice::ReadWrite);
    QDataStream mrgStr(&mrg);
    mrgStr.setByteOrder(QDataStream::BigEndian);
    mrgStr.writeRawData(mrgHeader, mrgHeadLen);
    for(uint i = 0; i < parts; ++i)
    {
        auto partSize = i == 0 ? mrgPartSize - mrgHeadLen : mrgPartSize;
        char* mrgPart = new char[partSize];
        binStr.readRawData(mrgPart, static_cast<int>(partSize));
        mrgStr.writeRawData(mrgPart, static_cast<int>(partSize));
        delete[] mrgPart;
    }
    mrg.close();


    bin.close();

    return true;
}
