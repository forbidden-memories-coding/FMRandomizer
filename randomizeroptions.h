#ifndef RANDOMIZEROPTIONS_H
#define RANDOMIZEROPTIONS_H

#include <QObject>
#include <QDebug>

class Config;

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
    Q_PROPERTY(int maxStarCost MEMBER m_maxStarCost READ maxStarCost WRITE setMaxStarCost NOTIFY maxStarCostChanged)
    Q_PROPERTY(int minStarCost MEMBER m_minStarCost READ minStarCost WRITE setMinStarCost NOTIFY minStarCostChanged)
    Q_PROPERTY(int maxDrop MEMBER m_maxDrop READ maxDrop WRITE setMaxDrop NOTIFY maxDropChanged)
    Q_PROPERTY(int minDrop MEMBER m_minDrop READ minDrop WRITE setMinDrop NOTIFY minDropChanged)
    Q_PROPERTY(int maxDef MEMBER m_maxDef READ maxDef WRITE setMaxDef NOTIFY maxDefChanged)
    Q_PROPERTY(int minDef MEMBER m_minDef READ minDef WRITE setMinDef NOTIFY minDefChanged)
    Q_PROPERTY(int maxAtk MEMBER m_maxAtk READ maxAtk WRITE setMaxAtk NOTIFY maxAtkChanged)
    Q_PROPERTY(int minAtk MEMBER m_minAtk READ minAtk WRITE setMinAtk NOTIFY minAtkChanged)
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

    void setMaxStarCost(const int& newCost);
    int maxStarCost() const;

    void setMinStarCost(const int& newCost);
    int minStarCost() const;

    void setMaxDrop(const int& newRate);
    int maxDrop() const;

    void setMinDrop(const int& newRate);
    int minDrop() const;

    void setMaxDef(const int& newDef);
    int maxDef() const;

    void setMinDef(const int& newDef);
    int minDef() const;

    void setMaxAtk(const int& newAtk);
    int maxAtk() const;

    void setMinAtk(const int& newAtk);
    int minAtk() const;

    void setSeed(const int& newSeed);
    int seed() const;

    Q_INVOKABLE void saveSettings(QString path, Config* conf);
    Q_INVOKABLE Config* loadSettings(QString path);
    Q_INVOKABLE Config* getConfig() const;

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
    void maxStarCostChanged(int oldCost);
    void minStarCostChanged(int oldCost);
    void maxDropChanged(int oldRate);
    void minDropChanged(int oldRate);
    void maxDefChanged(int oldDef);
    void minDefChanged(int oldDef);
    void maxAtkChanged(int oldAtk);
    void minAtkChanged(int oldAtk);
    void seedChanged(int oldSeed);

public slots:

private:
    bool m_randAttrib = false;
    bool m_randPass = false;
    bool m_randStarCost = false;
    bool m_randFuse = false;
    bool m_randEquip = false;
    bool m_randDuelistDeck = false;
    bool m_randCardDrop = false;
    bool m_randType = false;
    bool m_zeroGlitchFuse = false;
    bool m_enAtkDefScramble = false;
    bool m_alGlitchGuardStars = false;
    bool m_randGuardStars = false;
    int m_maxStarCost;
    int m_minStarCost;
    int m_maxDrop;
    int m_minDrop;
    int m_maxDef;
    int m_minDef;
    int m_maxAtk;
    int m_minAtk;
    int m_seed;
    Config* m_config;
};

#endif // RANDOMIZEROPTIONS_H
