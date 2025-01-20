#ifndef PROJECTS_H
#define PROJECTS_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlQueryModel>

struct Project{
    int id;
    QString name;
    int id_company;
};

class ProjectModel : public QSqlQueryModel {
    Q_OBJECT
public:
    enum CompanyRoles{
        ProjectIdRole = Qt::UserRole + 1,
        NameRole,
        id_CompanyRole,
    };
    explicit ProjectModel(QObject *parent = nullptr) : QSqlQueryModel(parent) {
        loadData();
    }


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE void loadData();
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    // Структура данных для QML
    QString companyId(int index) const {
        return QSqlQueryModel::data(QSqlQueryModel::index(index, 0)).toString();
    }

    QString name(int index) const {
        return QSqlQueryModel::data(QSqlQueryModel::index(index, 1)).toString();
    }

    double expenses(int index) const {
        return QSqlQueryModel::data(QSqlQueryModel::index(index, 2)).toDouble();
    }
public slots:
    Q_INVOKABLE void addProject(const QString &name, int id_company);

    Q_INVOKABLE void updateProject(const QString &name, int id, int id_compzny);

    Q_INVOKABLE void removeProject(int id);
private:
    QList<Project> m_project;
};



#endif // PROJECTS_H
