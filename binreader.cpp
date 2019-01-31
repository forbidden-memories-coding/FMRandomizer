#include "binreader.h"
#include <QDataStream>
#include <QByteArray>
#include <QDebug>

BinReader::BinReader(QDataStream* binStream) : m_curChunkInd(0)
{
    m_binStream = binStream;
    qDebug() << "Chunks amount " << binStream->device()->size() / CHUNK_SIZE;
    m_chunkAmount = static_cast<unsigned int>(binStream->device()->size() / CHUNK_SIZE);
}

unsigned int BinReader::chunkAmount() const
{
    return m_chunkAmount;
}

unsigned int BinReader::chunksLeft() const
{
    return m_chunkAmount - m_curChunkInd;
}

void BinReader::resetPosition()
{
    m_curChunkInd = 0;
    m_binStream->device()->seek(0);
}

// Goes to Nth chunk
bool BinReader::seek(unsigned int pos)
{
    if (pos >= m_chunkAmount)
    {
        throw std::exception("Attempted to access outside of BIN file");
    }
    m_curChunkInd = pos;
    return m_binStream->device()->seek(pos * CHUNK_SIZE);
}

// Reads n chunks of BIN returning raw data as QByteArray
QByteArray BinReader::readChunk(unsigned int n)
{
    if (m_curChunkInd + n > m_chunkAmount)
    {
        throw std::exception("Attempted to read more chunks than what was left in the BIN file.");
    }
    m_curChunkInd += n;

    Chunk* chunks = new Chunk[n];

    for(unsigned int i = 0; i < n; ++i)
    {
        m_binStream->readRawData(chunks[i].syncPattern, 12);
        m_binStream->readRawData(chunks[i].address, 3);
        m_binStream->readRawData(&chunks[i].mode, 1);
        m_binStream->readRawData(chunks[i].subheader, 8);
        m_binStream->readRawData(chunks[i].data, DATA_SIZE);
        m_binStream->readRawData(chunks[i].errorDetect, 4);
        m_binStream->readRawData(chunks[i].errorCorrection, 276);
    }

    QByteArray resData;

    for(unsigned int i = 0; i < n; ++i)
    {
        resData.append(chunks[i].data, DATA_SIZE);
    }

    delete[] chunks;

    return resData;
}
