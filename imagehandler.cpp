#include "imagehandler.h"
#include "randomizeroptions.h"
#include "config.h"
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
    if (m_options->getConfig()->cardPassToId) setCardPassToId();

    if (m_options->enAtkDefScramble()) shuffleAtkDef(&gen, m_options->minAtk(), m_options->maxAtk(), m_options->minDef(), m_options->maxDef());
    if (m_options->randGuardStars()) shuffleGuardStar(&gen);
    if (m_options->randAttrib()) shuffleAttributes(&gen);
    if (m_options->randCardDrop()) shuffleCardDrop(&gen, m_options->minDrop(), m_options->maxDrop());
    if (m_options->randDuelistDeck()) shuffleDuelDeck(&gen);
    if (m_options->randEquip()) shuffleEquip(&gen);
    if (m_options->randFuse()) shuffleFusions(&gen);
    if (m_options->randPass()) shufflePasswords(&gen);
    if (m_options->randStarCost()) shuffleStarCost(&gen, m_options->minStarCost(), m_options->maxStarCost());
    if (m_options->randType()) shuffleType(&gen);

    if (m_options->getConfig()->spoilerFiles) generateSpoilerFiles();
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
        if (!m_options->getConfig()->useVanillaDrops)
        {
            // Nullify all drop rates to 0
            memset(duelist.Drop.BcdPow, 0, sizeof(int) * 722);
            memset(duelist.Drop.SaPow, 0, sizeof(int) * 722);
            memset(duelist.Drop.SaTec, 0, sizeof(int) * 722);
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
        else
        {
            std::vector<int> card_vec(722, -1);
            int index = 0;
            int dropCopy[722];
            memcpy(dropCopy, duelist.Drop.BcdPow, sizeof(int) * 722);
            for(auto drop : dropCopy)
            {
                int cardNum = 0;
                do
                {
                    cardNum = gen->generate() % 722;
                }while(std::find(card_vec.begin(), card_vec.end(), cardNum) != card_vec.end());
                duelist.Drop.BcdPow[cardNum] = drop;
                card_vec[index++] = cardNum;
            }

            card_vec = std::vector<int>(722, -1);
            index = 0;
            memcpy(dropCopy, duelist.Drop.SaPow, sizeof(int) * 722);
            for(auto drop : dropCopy)
            {
                int cardNum = 0;
                do
                {
                    cardNum = gen->generate() % 722;
                }while(std::find(card_vec.begin(), card_vec.end(), cardNum) != card_vec.end());
                duelist.Drop.SaPow[cardNum] = drop;
                card_vec[index++] = cardNum;
            }

            card_vec = std::vector<int>(722, -1);
            index = 0;
            memcpy(dropCopy, duelist.Drop.SaTec, sizeof(int) * 722);
            for(auto drop : dropCopy)
            {
                int cardNum = 0;
                do
                {
                    cardNum = gen->generate() % 722;
                }while(std::find(card_vec.begin(), card_vec.end(), cardNum) != card_vec.end());
                duelist.Drop.SaTec[cardNum] = drop;
                card_vec[index++] = cardNum;
            }
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
            int num = gen->generate() % 722 + 1;
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
        int pass = gen->generate() % (m_options->getConfig()->cardPassToId ? 722 : 99999999) + 1;
        while(std::find(passwords.begin(), passwords.end(), pass) != passwords.end())
            pass = gen->generate() % (m_options->getConfig()->cardPassToId ? 722 : 99999999) + 1;

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

void ImageHandler::generateSpoilerFiles()
{
    if (m_options->randFuse()) fusionSpoilerFile();
    if (m_options->randStarCost() || m_options->randPass()) starchipSpoilerFile();
    if (m_options->randCardDrop()) dropsSpoilerFile();
}

void ImageHandler::fusionSpoilerFile()
{
    QString fName = "Fusion Spoiler[" + QString::number(m_options->seed()) + "].log";
    QFile spoilerF(fName);
    spoilerF.open(QIODevice::OpenModeFlag::ReadWrite | QIODevice::OpenModeFlag::Text);
    spoilerF.write("== Yu-Gi-Oh! Forbidden Memories Randomizer Spoiler File ==\n");
    spoilerF.write("== Version 1.0.0 ==\n");
    spoilerF.write("==========================================================\r\n");

    for(auto c : m_data->Cards)
    {
        spoilerF.write("================================================================\n");
        QString cardInfoHeader = "=> #" + QString::number(c.Id) + " " + QString(c.Name.c_str()) + " (" + QString::number(c.Attack) + "/" + QString::number(c.Defense) + ")\n";
        spoilerF.write(cardInfoHeader.toStdString().c_str());
        spoilerF.write("=> FUSIONS:\n");
        for(auto f : c.Fusions)
        {
            auto findCard = [&](Card* beg, Card* end, int idSearch) {
                while(beg != end)
                {
                    if (beg->Id == idSearch) return beg;
                    beg++;
                }
                return end;
            };
            auto ptrCard1 = findCard(m_data->Cards, m_data->Cards+722, f.Card1);
            auto ptrCard2 = findCard(m_data->Cards, m_data->Cards+722, f.Card2);
            auto ptrRes = findCard(m_data->Cards, m_data->Cards+722, f.Result);
            QString card1Name = "Glitch!";
            QString card2Name = "Glitch!";
            QString resName = "Glitch!";
            if (ptrCard1) card1Name = QString(ptrCard1->Name.c_str());
            if (ptrCard2) card2Name = QString(ptrCard2->Name.c_str());
            if (ptrRes) resName = QString(ptrRes->Name.c_str());
            QString fusInfoHeader = "          => " + QString::number(f.Card1) + " + " + QString::number(f.Card2) + " = " + QString::number(f.Result) + "\t\t" + "(" + card1Name + " + " + card2Name + " = " + resName + ")\n";
            spoilerF.write(fusInfoHeader.toStdString().c_str());
        }
    }

    spoilerF.close();
}

void ImageHandler::starchipSpoilerFile()
{
    QString fName = "StarPass Spoiler[" + QString::number(m_options->seed()) + "].log";
    QFile spoilerF(fName);
    spoilerF.open(QIODevice::OpenModeFlag::ReadWrite | QIODevice::OpenModeFlag::Text);
    spoilerF.write("== Yu-Gi-Oh! Forbidden Memories Randomizer Spoiler File ==\n");
    spoilerF.write("== Version 1.0.0 ==\n");
    spoilerF.write("==========================================================\r\n");

    for(auto c : m_data->Cards)
    {
        QString cardInfo = "    => #" + QString::number(c.Id) + " " + QString(c.Name.c_str()) + "\n";
        spoilerF.write(cardInfo.toStdString().c_str());
        QString passCost = "        Cost: " + QString::number(c.Starchip.Cost) + " Password: " + QString(c.Starchip.PasswordStr.c_str()) + "\n";
        spoilerF.write(passCost.toStdString().c_str());
    }

    spoilerF.close();
}

void ImageHandler::dropsSpoilerFile()
{
    QString fName = "Card Drops Spoiler[" + QString::number(m_options->seed()) + "].log";
    QFile spoilerF(fName);
    spoilerF.open(QIODevice::OpenModeFlag::ReadWrite | QIODevice::OpenModeFlag::Text);
    spoilerF.write("== Yu-Gi-Oh! Forbidden Memories Randomizer Spoiler File ==\n");
    spoilerF.write("== Version 1.0.0 ==\n");
    spoilerF.write("==========================================================\r\n");

    auto getDropMap = [&](FMLib::DropType dropType) {
        std::map<std::string, std::vector<std::pair<Card, int>>> dropMap;
        for(Duelist d : m_data->Duelists)
        {
            std::vector<std::pair<Card, int>> sorted_map;
            for(Card c : m_data->Cards)
            {
                if (d.Drop.GetDropType(dropType)[c.Id - 1] > 0)
                {
                    sorted_map.push_back(std::pair<Card, int>(c, d.Drop.GetDropType(dropType)[c.Id - 1]));
                }
            }
            std::sort(sorted_map.begin(), sorted_map.end(), [=](std::pair<Card, int>& p1, std::pair<Card, int>& p2) {return p2.second < p1.second;});
            dropMap[d.Name] = sorted_map;
        }
        return dropMap;
    };

    auto sapMap = getDropMap(FMLib::DropType::SAPOW);
    auto bcdMap = getDropMap(FMLib::DropType::BCDPOW);
    auto satMap = getDropMap(FMLib::DropType::SATEC);

    for(Duelist d : m_data->Duelists)
    {
        spoilerF.write("=================================================================\n");
        QString dName = QString(d.Name.c_str()) + " S/A-Tec drops\n";
        spoilerF.write(dName.toStdString().c_str());
        auto dropMap = satMap[d.Name];
        for(auto p : dropMap)
        {
            QString cardInfo = "    => #" + QString::number(p.first.Id) + " " + QString(p.first.Name.c_str()) + "\n";
            spoilerF.write(cardInfo.toStdString().c_str());
            QString rateInfo = "        Rate: " + QString::number(p.second) + "/2048\n";
            spoilerF.write(rateInfo.toStdString().c_str());
        }
        spoilerF.write("\n");

        spoilerF.write("=================================================================\n");
        dName = QString(d.Name.c_str()) + " B/C/D drops\n";
        spoilerF.write(dName.toStdString().c_str());
        dropMap = bcdMap[d.Name];
        for(auto p : dropMap)
        {
            QString cardInfo = "    => #" + QString::number(p.first.Id) + " " + QString(p.first.Name.c_str()) + "\n";
            spoilerF.write(cardInfo.toStdString().c_str());
            QString rateInfo = "        Rate: " + QString::number(p.second) + "/2048\n";
            spoilerF.write(rateInfo.toStdString().c_str());
        }
        spoilerF.write("\n");

        spoilerF.write("=================================================================\n");
        dName = QString(d.Name.c_str()) + " S/A-Pow drops\n";
        spoilerF.write(dName.toStdString().c_str());
        dropMap = sapMap[d.Name];
        for(auto p : dropMap)
        {
            QString cardInfo = "    => #" + QString::number(p.first.Id) + " " + QString(p.first.Name.c_str()) + "\n";
            spoilerF.write(cardInfo.toStdString().c_str());
            QString rateInfo = "        Rate: " + QString::number(p.second) + "/2048\n";
            spoilerF.write(rateInfo.toStdString().c_str());
        }
        spoilerF.write("\n");
    }

    spoilerF.close();
}
