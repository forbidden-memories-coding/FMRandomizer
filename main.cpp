#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include "randomizeroptions.h"
#include "imagehandler.h"
#include "config.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<Config>("Randomizer", 1, 0, "Config");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    RandomizerOptions options;
    ImageHandler img(nullptr, &options, &engine);

    engine.rootContext()->setContextProperty("options", &options);
    engine.rootContext()->setContextProperty("engine", &img);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
