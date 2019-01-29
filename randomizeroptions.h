#ifndef RANDOMIZEROPTIONS_H
#define RANDOMIZEROPTIONS_H

#include <QObject>
#include <QDebug>

class RandomizerOptions : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool randAttrib MEMBER m_randAttrib READ randAttrib WRITE setRandAttrib NOTIFY randAttribChanged)
    Q_PROPERTY(bool randPass MEMBER m_randPass READ randPass WRITE setRandPass NOTIFY randPassChanged)
    Q_PROPERTY(bool randStarCost MEMBER m_randStarCost READ randStarCost WRITE setRandStarCost NOTIFY randStarCostChanged)
    Q_PROPERTY(bool randFuse MEMBER m_randFuse READ randFuse WRITE setRandFuse NOTIFY randFuseChanged)
    Q_PROPERTY(bool randEquip MEMBER m_randEquip READ randEquip WRITE setRandEquip NOTIFY randEquipChanged)
    Q_PROPERTY(bool randDuelistDeck MEMBER m_randDuelistDeck READ randDuelistDeck WRITE setRandDuelistDeck NOTIFY randDuelistDeckChanged)
    Q_PROPERTY(bool randCardDrop MEMBER m_randCardDrop READ randCardDrop WRITE setRandCardDrop NOTIFY randCardDropChanged)
    Q_PROPERTY(bool randType MEMBER m_randType READ randType WRITE setRandType NOTIFY randTypeChanged)
    Q_PROPERTY(bool zeroGlitchFuse MEMBER m_zeroGlitchFuse READ zeroGlitchFuse WRITE setZeroGlitchFuse NOTIFY zeroGlitchFuseChanged)
    Q_PROPERTY(bool enAtkDefScramble MEMBER m_enAtkDefScramble READ enAtkDefScramble WRITE setEnAtkDefScramble NOTIFY enAtkDefScrambleChanged)
    Q_PROPERTY(bool alGlitchGuardStars MEMBER m_alGlitchGuardStars READ alGlitchGuardStars WRITE setAlGlitchGuardStars NOTIFY alGlitchGuardStarsChanged)
    Q_PROPERTY(bool randGuardStars MEMBER m_randGuardStars READ randGuardStars WRITE setRandGuardStars NOTIFY randGuardStarsChanged)
    Q_PROPERTY(int seed MEMBER m_seed READ seed WRITE setSeed NOTIFY seedChanged)
public:
    explicit RandomizerOptions(QObject *parent = nullptr);

    void setRandAttrib(const bool& flag);
    bool randAttrib() const;

    void setRandPass(const bool& flag);
    bool randPass() const;

    void setRandStarCost(const bool& flag);
    bool randStarCost() const;

    void setRandFuse(const bool& flag);
    bool randFuse() const;

    void setRandEquip(const bool& flag);
    bool randEquip() const;

    void setRandDuelistDeck(const bool& flag);
    bool randDuelistDeck() const;

    void setRandCardDrop(const bool& flag);
    bool randCardDrop() const;

    void setRandType(const bool& flag);
    bool randType() const;

    void setZeroGlitchFuse(const bool& flag);
    bool zeroGlitchFuse() const;

    void setEnAtkDefScramble(const bool& flag);
    bool enAtkDefScramble() const;

    void setAlGlitchGuardStars(const bool& flag);
    bool alGlitchGuardStars() const;

    void setRandGuardStars(const bool& flag);
    bool randGuardStars() const;

    void setSeed(const int& old_seed);
    int seed() const;

signals:
    void randAttribChanged();
    void randPassChanged();
    void randStarCostChanged();
    void randFuseChanged();
    void randEquipChanged();
    void randDuelistDeckChanged();
    void randCardDropChanged();
    void randTypeChanged();
    void zeroGlitchFuseChanged();
    void enAtkDefScrambleChanged();
    void alGlitchGuardStarsChanged();
    void randGuardStarsChanged();
    void seedChanged(int newSeed);

public slots:


private:
    bool m_randAttrib;
    bool m_randPass;
    bool m_randStarCost;
    bool m_randFuse;
    bool m_randEquip;
    bool m_randDuelistDeck;
    bool m_randCardDrop;
    bool m_randType;
    bool m_zeroGlitchFuse;
    bool m_enAtkDefScramble;
    bool m_alGlitchGuardStars;
    bool m_randGuardStars;
    int m_seed;
};

#endif // RANDOMIZEROPTIONS_H
