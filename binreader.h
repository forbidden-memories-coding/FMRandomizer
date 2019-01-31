#ifndef BINREADER_H
#define BINREADER_H

#define CHUNK_SIZE 2352
// This BinReader assumes that all sectors of the BIN are in mode 2
// Also this is exclusively for reading PS1's CD-ROM XA types and not CD-ROM
// which use different sector structures

class QByteArray;
class QDataStream;

struct Chunk
{
    char syncPattern[12];
    char address[3];
    char mode;
    char subheader[8];
    char data[2324];
    char errorDetect[4];
};

class BinReader
{
public:
    explicit BinReader(QDataStream* binStream);

    unsigned int chunkAmount() const;
    unsigned int chunksLeft() const;
    void resetPosition();
    QByteArray readChunk(unsigned int n = 1);

private:
    QDataStream* m_binStream;
    unsigned int m_chunkAmount;
    unsigned int m_curChunkNum;
};

#endif // BINREADER_H
