#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtSql/QSql>
#include "MyModel.h"
#include <QQmlContext>


int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    // Инициализация базы данных
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("people.db");

    if (!db.open()) {
        qWarning() << "Cannot open database:" << db.lastError().text();
        return -1;
    }

    // Инициализация модели
    MyModel model;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myModel", &model); // Установим модель в контекст QML

    const QUrl url(QStringLiteral("qrc:/Main.qml"));

    // Исправленный connect: вызываем QCoreApplication::exit только в случае ошибки загрузки
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj) {
                         if (!obj) {
                             qWarning() << "Error loading QML file:" << url.toString();
                             QCoreApplication::exit(-1);
                         }
                     }, Qt::QueuedConnection);

    engine.loadFromModule("untitled2", "Main");

    return app.exec();
}
