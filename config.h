#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>

class Config : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString configPath MEMBER configPath NOTIFY configPathChanged)
    Q_PROPERTY(QString isoPath MEMBER isoPath NOTIFY isoPathChanged)
    Q_PROPERTY(QString slusMrgPath MEMBER slusMrgPath NOTIFY slusMrgPathChanged)
    Q_PROPERTY(int winTheme MEMBER winTheme NOTIFY winThemeChanged)
    Q_PROPERTY(int winAccent MEMBER winAccent NOTIFY winAccentChanged)
    Q_PROPERTY(QString isoName MEMBER isoName NOTIFY isoNameChanged)
    Q_PROPERTY(int isoNameFlags MEMBER isoNameFlags NOTIFY isoNameFlagsChanged)
    Q_PROPERTY(bool useVanillaDrops MEMBER useVanillaDrops NOTIFY useVanillaDropsChanged)
    Q_PROPERTY(bool cardPassToId MEMBER cardPassToId NOTIFY cardPassToIdChanged)
    Q_PROPERTY(bool spoilerFiles MEMBER spoilerFiles NOTIFY spoilerFilesChanged)

public:
    enum IsoNameFlags
    {
        SEED = 1 << 0,
        RAND_FLAGS = 1 << 1,
        DATE = 1 << 2,
    };
    Q_ENUM(IsoNameFlags)

    QString         configPath = "";
    QString         isoPath = "";
    QString         slusMrgPath = "";
    int             winTheme = 0;
    int             winAccent = 0;
    QString         isoName = "";
    int             isoNameFlags = 0;
    bool            useVanillaDrops = false;
    bool            cardPassToId = false;
    bool            spoilerFiles = false;

signals:
    void configPathChanged();
    void isoPathChanged();
    void slusMrgPathChanged();
    void winThemeChanged();
    void winAccentChanged();
    void isoNameChanged();
    void isoNameFlagsChanged();
    void useVanillaDropsChanged();
    void cardPassToIdChanged();
    void spoilerFilesChanged();

private:
    IsoNameFlags    m_isoNameFlags = IsoNameFlags::SEED;
};

#endif // CONFIG_H
