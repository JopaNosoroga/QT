#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QList>
#include <QVariant>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

class MyModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        AgeRole,
        // Добавьте роли для других таблиц
        AddressRole,
        PhoneNumberRole,
        JobRole,
        // и т.д.
    };

    MyModel(QObject *parent = nullptr);
    ~MyModel();

    Q_INVOKABLE void addPerson(const QString &name, int age, const QString &address, const QString &phoneNumber, const QString &job);
    Q_INVOKABLE void removePerson(int index);
    Q_INVOKABLE void updatePerson(int index, const QString &name, int age, const QString &address, const QString &phoneNumber, const QString &job);
    Q_INVOKABLE void loadData();
    Q_INVOKABLE void saveData();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    struct Person {
        QString name;
        int age;
        QString address;
        QString phoneNumber;
        QString job;
    };

    QList<Person> m_people;
    QSqlDatabase m_db;

    void initializeDatabase();
};

#endif // MYMODEL_H
