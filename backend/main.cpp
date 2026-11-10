#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "backend/datagenerator/datagenerator.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("DeviceSimulator", "Main");

    DataGenerator generator(100, {0, 100}, 100, 5);             // testing purposes

    return QGuiApplication::exec();
}
