#include "randomizeroptions.h"

RandomizerOptions::RandomizerOptions(QObject *parent) : QObject(parent) {}


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

void RandomizerOptions::setSeed(const int& new_seed)
{
    if (new_seed != m_seed)
    {

        int old = m_seed;
        m_seed = new_seed;
        qDebug() << "Seed changed in backend yay! " << m_seed;
        emit seedChanged(old);
    }
}
int RandomizerOptions::seed() const
{
    return m_seed;
}
