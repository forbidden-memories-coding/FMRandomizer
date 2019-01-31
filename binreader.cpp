#include "binreader.h"
#include <QDataStream>
#include <QByteArray>
#include <QDebug>

BinReader::BinReader(QDataStream* binStream) : m_curChunkNum(0)
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
    return m_chunkAmount - m_curChunkNum;
}

// Reads n chunks of BIN returning raw data as QByteArray
QByteArray BinReader::readChunk(unsigned int n)
{
    if (m_curChunkNum + n > m_chunkAmount)
    {
        throw std::exception("Attempted to read more chunks than what was left in the BIN file.");
    }

    QByteArray res_data;

    return res_data;
}
