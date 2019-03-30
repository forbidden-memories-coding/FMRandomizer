#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QObject>
#include <QDebug>

class QDataStream;
class QRandomGenerator;
class RandomizerOptions;
class QQmlApplicationEngine;


namespace FMLib
{
    struct IFMLib;
    struct Data;
}

class ImageHandler : public QObject
{
    Q_OBJECT
public:
    explicit            ImageHandler(QObject *parent = nullptr, RandomizerOptions* options = nullptr, QQmlApplicationEngine* engine = nullptr);
                        ~ImageHandler();

    Q_INVOKABLE bool    loadSlusMrg(QString slusPath, QString mrgPath);
    Q_INVOKABLE bool    loadCueBin(QString binPath);

    Q_INVOKABLE bool    saveImage(QString imagePath = "", QString imgName = "");

    Q_INVOKABLE void    shuffleData();

    void PatchImage(QString imagePath = "");

private:
    void shuffleFusions(QRandomGenerator*);
    void shuffleAttributes(QRandomGenerator*);
    void shufflePasswords(QRandomGenerator*);
    void shuffleStarCost(QRandomGenerator*, int minCost, int maxCost);
    void shuffleEquip(QRandomGenerator*);
    void shuffleDuelDeck(QRandomGenerator*);
    void shuffleType(QRandomGenerator*);
    void shuffleGuardStar(QRandomGenerator*);
    void shuffleAtkDef(QRandomGenerator*, int minAtk, int maxAtk, int minDef, int maxDef);
    void shuffleCardDrop(QRandomGenerator*, int minRate, int maxRate);

signals:

public slots:
    void patchFinished();

private:
    QDataStream *m_slus;
    QDataStream *m_mrg;
    QString     m_imagePath;
    FMLib::IFMLib*     m_lib;
    FMLib::Data*       m_data;
    RandomizerOptions* m_options;
    QQmlApplicationEngine* m_engine;
};

#endif // IMAGELOADER_H
