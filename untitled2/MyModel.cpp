#include "MyModel.h"
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QDebug>

MyModel::MyModel(QObject *parent)
    : QAbstractListModel(parent) {
    initializeDatabase();
    loadData();
}

MyModel::~MyModel() {
    saveData(); // Сохраните данные при уничтожении
}

void MyModel::initializeDatabase() {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("people.db");

    if (!m_db.open()) {
        qWarning() << "Cannot open database:" << m_db.lastError().text();
        return;
    }

    QSqlQuery query;

    // Создание таблицы для людей
    query.exec("CREATE TABLE IF NOT EXISTS people ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT, "
               "age INTEGER, "
               "address TEXT, "
               "phone TEXT, "
               "job TEXT)");

    // Создание таблицы для работ
    query.exec("CREATE TABLE IF NOT EXISTS jobs ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "jobTitle TEXT, "
               "salary REAL)");

    // Создание таблицы для адресов
    query.exec("CREATE TABLE IF NOT EXISTS addresses ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "street TEXT, "
               "city TEXT, "
               "zipCode TEXT)");

    // Создание таблицы для контактов
    query.exec("CREATE TABLE IF NOT EXISTS contacts ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "phone TEXT, "
               "email TEXT, "
               "personId INTEGER, "
               "FOREIGN KEY(personId) REFERENCES people(id))");
}

void MyModel::addPerson(const QString &name, int age, const QString &address, const QString &phoneNumber, const QString &job) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    Person person = {name, age, address, phoneNumber, job};
    m_people.append(person);

    QSqlQuery query;
    query.prepare("INSERT INTO people (name, age, address, phone, job) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(age);
    query.addBindValue(address);
    query.addBindValue(phoneNumber);
    query.addBindValue(job);
    query.exec();

    endInsertRows();
}

void MyModel::removePerson(int index) {
    if (index < 0 || index >= m_people.size())
        return;

    beginRemoveRows(QModelIndex(), index, index);
    m_people.removeAt(index);
    endRemoveRows();

    QSqlQuery query;
    query.prepare("DELETE FROM people WHERE id = ?");
    query.addBindValue(index + 1); // Учитываем, что id начинается с 1
    query.exec();
}

void MyModel::updatePerson(int index, const QString &name, int age, const QString &address, const QString &phoneNumber, const QString &job) {
    if (index < 0 || index >= m_people.size())
        return;

    m_people[index].name = name;
    m_people[index].age = age;
    m_people[index].address = address;
    m_people[index].phoneNumber = phoneNumber;
    m_people[index].job = job;

    emit dataChanged(createIndex(index, 0), createIndex(index, 0));

    QSqlQuery query;
    query.prepare("UPDATE people SET name = ?, age = ?, address = ?, phone = ?, job = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(age);
    query.addBindValue(address);
    query.addBindValue(phoneNumber);
    query.addBindValue(job);
    query.addBindValue(index + 1); // Учитываем, что id начинается с 1
    query.exec();
}

void MyModel::loadData() {
    QSqlQuery query("SELECT * FROM people");
    while (query.next()) {
        Person person;
        person.name = query.value("name").toString();
        person.age = query.value("age").toInt();
        person.address = query.value("address").toString();
        person.phoneNumber = query.value("phone").toString();
        person.job = query.value("job").toString();
        m_people.append(person);
    }
}

void MyModel::saveData() {
    // В данном случае, данные сохраняются при добавлении, удалении и обновлении
}

int MyModel::rowCount(const QModelIndex &parent) const {
    return m_people.count();
}

QVariant MyModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_people.count())
        return QVariant();

    const Person &person = m_people[index.row()];

    if (role == NameRole)
        return person.name;
    else if (role == AgeRole)
        return person.age;
    else if (role == AddressRole)
        return person.address;
    else if (role == PhoneNumberRole)
        return person.phoneNumber;
    else if (role == JobRole)
        return person.job;

    return QVariant();
}

QHash<int, QByteArray> MyModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[AgeRole] = "age";
    roles[AddressRole] = "address";
    roles[PhoneNumberRole] = "phone";
    roles[JobRole] = "job";
    return roles;
}
