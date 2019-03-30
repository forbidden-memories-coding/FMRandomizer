#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include "randomizeroptions.h"
#include "imagehandler.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    RandomizerOptions options;
    ImageHandler img(nullptr, &options, &engine);

    engine.rootContext()->setContextProperty("options", &options);
    engine.rootContext()->setContextProperty("engine", &img);

    return app.exec();
}
