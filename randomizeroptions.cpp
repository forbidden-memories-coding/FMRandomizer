#include "randomizeroptions.h"

#include <QDataStream>
#include <QFile>
#include "config.h"

RandomizerOptions::RandomizerOptions(QObject *parent) : QObject(parent) { m_config = new Config(); m_seed = 7681239; }

void RandomizerOptions::setRandAttrib(const bool& flag)
{
    if (flag != m_randAttrib)
    {
        qDebug() << "Changed randomizing attribute";
        m_randAttrib = flag;
        emit randAttribChanged();
    }
}
bool RandomizerOptions::randAttrib() const
{
    return m_randAttrib;
}

void RandomizerOptions::setRandPass(const bool& flag)
{
    if (flag != m_randPass)
    {
        m_randPass = flag;
        emit randPassChanged();
    }
}
bool RandomizerOptions::randPass() const
{
    return m_randPass;
}

void RandomizerOptions::setRandStarCost(const bool& flag)
{
    if (flag != m_randStarCost)
    {
        m_randStarCost = flag;
        emit randStarCostChanged();
    }
}
bool RandomizerOptions::randStarCost() const
{
    return m_randStarCost;
}

void RandomizerOptions::setRandFuse(const bool& flag)
{
    if (flag != m_randFuse)
    {
        m_randFuse = flag;
        emit randFuseChanged();
    }
}
bool RandomizerOptions::randFuse() const
{
    return m_randFuse;
}

void RandomizerOptions::setRandEquip(const bool& flag)
{
    if (flag != m_randEquip)
    {
        m_randEquip = flag;
        emit randEquipChanged();
    }
}
bool RandomizerOptions::randEquip() const
{
    return m_randEquip;
}

void RandomizerOptions::setRandDuelistDeck(const bool& flag)
{
    if (flag != m_randDuelistDeck)
    {
        m_randDuelistDeck = flag;
        emit randDuelistDeckChanged();
    }
}
bool RandomizerOptions::randDuelistDeck() const
{
    return m_randDuelistDeck;
}

void RandomizerOptions::setRandCardDrop(const bool& flag)
{
    if (flag != m_randCardDrop)
    {
        m_randCardDrop = flag;
        emit randCardDropChanged();
    }
}
bool RandomizerOptions::randCardDrop() const
{
    return m_randCardDrop;
}

void RandomizerOptions::setRandType(const bool& flag)
{
    if (flag != m_randType)
    {
        m_randType = flag;
        emit randTypeChanged();
    }
}
bool RandomizerOptions::randType() const
{
    return m_randType;
}

void RandomizerOptions::setZeroGlitchFuse(const bool& flag)
{
    if (flag != m_zeroGlitchFuse)
    {
        m_zeroGlitchFuse = flag;
        emit zeroGlitchFuseChanged();
    }
}
bool RandomizerOptions::zeroGlitchFuse() const
{
    return m_zeroGlitchFuse;
}

void RandomizerOptions::setEnAtkDefScramble(const bool& flag)
{
    if (flag != m_enAtkDefScramble)
    {
        m_enAtkDefScramble = flag;
        emit enAtkDefScrambleChanged();
    }
}
bool RandomizerOptions::enAtkDefScramble() const
{
    return m_enAtkDefScramble;
}

void RandomizerOptions::setAlGlitchGuardStars(const bool& flag)
{
    if (flag != m_alGlitchGuardStars)
    {
        m_alGlitchGuardStars = flag;
        emit alGlitchGuardStarsChanged();
    }
}
bool RandomizerOptions::alGlitchGuardStars() const
{
    return m_alGlitchGuardStars;
}

void RandomizerOptions::setRandGuardStars(const bool& flag)
{
    if (flag != m_randGuardStars)
    {
        m_randGuardStars = flag;
        emit randGuardStarsChanged();
    }
}
bool RandomizerOptions::randGuardStars() const
{
    return m_randGuardStars;
}

void RandomizerOptions::setMaxStarCost(const int& newCost)
{
    if (newCost != m_maxStarCost)
    {
        int old = m_maxStarCost;
        m_maxStarCost = newCost;
        emit maxStarCostChanged(old);
    }
}
int RandomizerOptions::maxStarCost() const
{
    return m_maxStarCost;
}

void RandomizerOptions::setMinStarCost(const int& newCost)
{
    if (newCost != m_minStarCost)
    {
        int old = m_minStarCost;
        m_minStarCost = newCost;
        emit minStarCostChanged(old);
    }
}
int RandomizerOptions::minStarCost() const
{
    return m_minStarCost;
}

void RandomizerOptions::setMaxDrop(const int& newRate)
{
    if (newRate != m_maxDrop)
    {
        int old = m_maxDrop;
        m_maxDrop = newRate;
        emit maxDropChanged(old);
    }
}
int RandomizerOptions::maxDrop() const
{
    return m_maxDrop;
}

void RandomizerOptions::setMinDrop(const int& newRate)
{
    if (newRate != m_minDrop)
    {
        int old = m_minDrop;
        m_minDrop = newRate;
        emit minDropChanged(old);
    }
}
int RandomizerOptions::minDrop() const
{
    return m_minDrop;
}

void RandomizerOptions::setMaxDef(const int& newDef)
{
    if (newDef != m_maxDef)
    {
        int old = m_maxDef;
        m_maxDef = newDef;
        emit maxDefChanged(old);
    }
}
int RandomizerOptions::maxDef() const
{
    return m_maxDef;
}

void RandomizerOptions::setMinDef(const int& newDef)
{
    if (newDef != m_minDef)
    {
        int old = m_minDef;
        m_minDef = newDef;
        emit minDefChanged(old);
    }
}
int RandomizerOptions::minDef() const
{
    return m_minDef;
}

void RandomizerOptions::setMaxAtk(const int& newAtk)
{
    if (newAtk != m_maxAtk)
    {
        int old = m_maxAtk;
        m_maxAtk = newAtk;
        qDebug() << "Max atk changed in backend yay! " << m_maxAtk;
        emit maxAtkChanged(old);
    }
}
int RandomizerOptions::maxAtk() const
{
    return m_maxAtk;
}

void RandomizerOptions::setMinAtk(const int& newAtk)
{
    if (newAtk != m_minAtk)
    {
        int old = m_minAtk;
        m_minAtk = newAtk;
        qDebug() << "Min atk changed in backend yay! " << m_minAtk;
        emit maxAtkChanged(old);
    }
}
int RandomizerOptions::minAtk() const
{
    return m_minAtk;
}

void RandomizerOptions::setSeed(const int& newSeed)
{
    if (newSeed != m_seed)
    {
        int old = m_seed;
        m_seed = newSeed;
        qDebug() << "Seed changed in backend yay! " << m_seed;
        emit seedChanged(old);
    }
}
int RandomizerOptions::seed() const
{
    return m_seed;
}



void RandomizerOptions::saveSettings(QString path, Config* conf)
{
    QFile fConfig(path);
    fConfig.open(QIODevice::OpenModeFlag::ReadWrite | QIODevice::OpenModeFlag::Truncate);
    QDataStream dat(&fConfig);
    dat << conf->configPath;
    dat << conf->isoPath;
    dat << conf->slusMrgPath;
    dat << conf->winTheme;
    dat << conf->winAccent;
    dat << conf->isoName;
    dat << conf->isoNameFlags;
    dat << conf->useVanillaDrops;
    dat << conf->cardPassToId;
    dat << conf->spoilerFiles;
    fConfig.close();
}

Config* RandomizerOptions::loadSettings(QString path)
{
    try {
        if (m_config) delete m_config;
        Config* conf = new Config();
        QFile fConfig(path);
        fConfig.open(QIODevice::OpenModeFlag::ReadOnly);
        QDataStream dat(&fConfig);
        dat >> conf->configPath;
        dat >> conf->isoPath;
        dat >> conf->slusMrgPath;
        dat >> conf->winTheme;
        dat >> conf->winAccent;
        dat >> conf->isoName;
        dat >> conf->isoNameFlags;
        dat >> conf->useVanillaDrops;
        dat >> conf->cardPassToId;
        dat >> conf->spoilerFiles;
        fConfig.close();
        m_config = conf;
        return conf;
    } catch (...) {
        return nullptr;
    }
}

Config* RandomizerOptions::getConfig() const
{
    return m_config;
}
