#include "imagehandler.h"
#include "randomizeroptions.h"
#include <QFile>
#include <QDataStream>
#include <QThread>
#include <QRandomGenerator>
#include <QQmlProperty>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <FMLib.h>

ImageHandler::ImageHandler(QObject *parent, RandomizerOptions* options, QQmlApplicationEngine* engine) : QObject(parent), m_options(options), m_engine(engine)
{
    m_lib = nullptr;
    m_data = nullptr;
}

ImageHandler::~ImageHandler()
{

}

bool ImageHandler::loadSlusMrg(QString slusPath, QString mrgPath)
{
    if (m_lib) delete m_lib;
    if (m_data) delete m_data;
    FMLib::IFMLib* lib = FMLib::GetLibMrgSlus(slusPath.toStdString().c_str(), mrgPath.toStdString().c_str());
    m_data = lib->LoadData();
    qDebug() << "001 card name is " << QString(m_data->Cards[0].Name.c_str());
    qDebug() << "Loading SLUS/MRG pair...";
    qDebug() << "SLUS path " << slusPath;
    qDebug() << "MRG path " << mrgPath;

    m_lib = lib;

    return true;
}

bool ImageHandler::loadCueBin(QString binPath)
{
    if (m_lib) delete m_lib;
    if (m_data) delete m_data;
    qDebug() << "Loading CUE/BIN pair...";
    qDebug() << "BIN path" << binPath;

    FMLib::IFMLib* lib = FMLib::GetLibBin(binPath.toStdString().c_str());

    m_lib = lib;
    m_imagePath = binPath;
    m_data = lib->LoadData();

    return true;
}

bool ImageHandler::saveImage(QString imagePath, QString imgName)
{
    if (imagePath.isEmpty())
    {
        imagePath = m_imagePath;
    }

    m_lib->WriteData(m_data);

    qDebug() << "BIN path to patch " << imagePath;

    m_lib->SetBin(imagePath.toStdString().c_str());

    m_lib->SaveChanges();
    QThread* thr = QThread::create(&ImageHandler::PatchImage, this, imgName);
    QObject::connect(thr, SIGNAL(finished()), this, SLOT(patchFinished()));
    thr->start();
    return true;
}

void ImageHandler::PatchImage(QString imagePath)
{
    m_lib->PatchImage(imagePath.toStdString().c_str());
}

void ImageHandler::patchFinished()
{
    qDebug() << "Patching finished";
    QObject* window = m_engine->rootObjects()[0];
    window->setProperty("busy", QVariant(false));
}

void ImageHandler::shuffleData()
{
    QRandomGenerator gen(static_cast<quint32>(m_options->seed()));

    auto setCardPassToId = [&]() {
        for(Card& card : m_data->Cards)
        {
            card.Starchip.Password = card.Id;
            QString passStr = QString::number(card.Starchip.Password);
            while(passStr.length() != 8)
            {
                passStr.insert(0, '0');
            }
            card.Starchip.PasswordStr = passStr.toStdString();
        }
    };
    if (m_options->idToPass()) setCardPassToId();

    if (m_options->enAtkDefScramble()) shuffleAtkDef(&gen, m_options->minAtk(), m_options->maxAtk(), m_options->minDef(), m_options->maxDef());
    if (m_options->randGuardStars()) shuffleGuardStar(&gen);
    if (m_options->randAttrib()) shuffleAttributes(&gen);
    if (m_options->randCardDrop()) shuffleCardDrop(&gen, m_options->minDef(), m_options->maxDrop());
    if (m_options->randDuelistDeck()) shuffleDuelDeck(&gen);
    if (m_options->randEquip()) shuffleEquip(&gen);
    if (m_options->randFuse()) shuffleFusions(&gen);
    if (m_options->randPass()) shufflePasswords(&gen);
    if (m_options->randStarCost()) shuffleStarCost(&gen, m_options->minStarCost(), m_options->maxStarCost());
    if (m_options->randType()) shuffleType(&gen);
}

void ImageHandler::shuffleAtkDef(QRandomGenerator* gen, int minAtk, int maxAtk, int minDef, int maxDef)
{
    for(auto& card : m_data->Cards)
    {
        card.Attack = static_cast<int>(gen->generate() % (maxAtk-minAtk) + minAtk);
        card.Defense = static_cast<int>(gen->generate() % (maxDef-minDef) + minDef);
    }
}

void ImageHandler::shuffleGuardStar(QRandomGenerator* gen)
{
    for(auto& card : m_data->Cards)
    {
        card.GuardianStar_Primary = static_cast<int>(gen->generate() % 25 + 1);
        card.GuardianStar_Secondary = static_cast<int>(gen->generate() % 25 + 1);
    }
}

void ImageHandler::shuffleAttributes(QRandomGenerator* gen)
{
    for(auto& card : m_data->Cards)
    {
        card.Attribute = static_cast<int>(gen->generate() % 15 + 1);
    }
}

void ImageHandler::shuffleCardDrop(QRandomGenerator* gen, int minRate, int maxRate)
{
    for(auto& duelist : m_data->Duelists)
    {
        int totalRate = 0;
        while(true)
        {
            auto rate = static_cast<int>(gen->generate() % maxRate + minRate);
            if (totalRate + rate > 2048)
            {
                rate = 2048 - totalRate;
            }
            duelist.Drop.BcdPow[gen->generate() % 722] += rate;
            duelist.Drop.SaPow[gen->generate() % 722] += rate;
            duelist.Drop.SaTec[gen->generate() % 722] += rate;
            totalRate += rate;
            if (totalRate == 2048) break;
        }
    }
}

void ImageHandler::shuffleDuelDeck(QRandomGenerator* gen)
{
    for(auto& duelist : m_data->Duelists)
    {
        for (int i = 0; i < 2048; ++i)
        {
            duelist.Deck[gen->generate() % 722]++;
        }
    }
}

void ImageHandler::shuffleEquip(QRandomGenerator* gen)
{
    for(auto& card : m_data->Cards)
    {
        int condition = gen->generate() % 20;
        card.Equips.clear();
        for(int i = 0; i < condition; ++i)
        {
            int num = gen->generate() % (722-1) + 1;
            card.Equips.push_back(num);
        }
    }
}

void ImageHandler::shuffleFusions(QRandomGenerator* gen)
{
    for(auto& card : m_data->Cards)
    {
        for(auto& fus : card.Fusions)
        {
            fus.Card2 = static_cast<int>(gen->generate() % (722-card.Id+1) + card.Id - 1);
            fus.Result = static_cast<int>(gen->generate() % (722-card.Id+1) + card.Id - 1);
        }
    }
}

void ImageHandler::shufflePasswords(QRandomGenerator* gen)
{
    std::vector<int> passwords(722);
    for(auto& card : m_data->Cards)
    {
        int pass = gen->generate() % (m_options->idToPass() ? 722 : 99999999) + 1;
        while(std::find(passwords.begin(), passwords.end(), pass) != passwords.end())
            pass = gen->generate() % (m_options->idToPass() ? 722 : 99999999) + 1;

        if (std::find(passwords.begin(), passwords.end(), pass) == passwords.end())
        {
            QString passStr = QString::number(pass);
            card.Starchip.Password = pass;

            // Pad with 0s at the beginning if resulted string was less than 8 numbers long
            qDebug() << "Password's length is " << passStr.size();
            while(passStr.length() != 8)
            {
                passStr.insert(0, '0');
            }
            qDebug() << "Card's " << card.Id << " result password: " << passStr;

            card.Starchip.PasswordStr = passStr.toStdString();
            passwords[card.Id-1] = pass;
        }
    }
}

void ImageHandler::shuffleStarCost(QRandomGenerator* gen, int minCost, int maxCost)
{
    for(auto& card : m_data->Cards)
    {
        card.Starchip.Cost = static_cast<int>(gen->generate() % (maxCost-minCost) + minCost);
    }
}

void ImageHandler::shuffleType(QRandomGenerator* gen)
{
    for(auto& card : m_data->Cards)
    {
        card.Type = static_cast<int>(gen->generate() % 25 + 1);
    }
}
