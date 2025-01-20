#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlDatabase>
#include <QQmlContext>
#include "it_company.h"
#include "projects.h"
#include <jobtitle.h>
#include "employee.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    // Инициализация базы данных
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("company.db");

    if (!db.open()) {
        qWarning() << "Cannot open database:" << db.lastError().text();
        return -1;
    }

    // Создание таблиц, если они не существуют
    QSqlQuery query;

    query.exec("CREATE TABLE IF NOT EXISTS companies (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, expenses INTEGER NOT NULL)");
    query.exec("CREATE TABLE IF NOT EXISTS projects (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, companyId INTEGER)");
    query.exec("CREATE TABLE IF NOT EXISTS jobtitle (id INTEGER PRIMATY KEY AUTOINCREMENT, name TEXT NOT NULL, salary INTEGER, StandartHours INTEGER)");
    query.exec("CREATE TABLE IF NOT EXISTS employee (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, id_company INTEGER, id_titlejob INTEGER, email TEXT NOT NULL, phone TEXT NOT NULL )");

    // Инициализация моделей
    IT_CompanyModel itCompanyModel;
    ProjectModel projectsModel;
    JobTitleModel jobtitleModel;
    EmployeeModel employeemodel;

    QQmlApplicationEngine engine;
    qmlRegisterType<IT_CompanyModel>("Xaxaxa", 1, 0, "ITCompanyModel");
    qmlRegisterType<ProjectModel>("Xaxaxa", 1, 0, "ProjectModel");  // Регистрация новой модели
    qmlRegisterType<JobTitleModel>("Xaxaxa", 1, 0, "JobTitleModel");
    qmlRegisterType<EmployeeModel>("Xaxaxa", 1, 0, "EmployeeModel");



    engine.loadFromModule("Xaxaxa", "Main");

    return app.exec();
}
