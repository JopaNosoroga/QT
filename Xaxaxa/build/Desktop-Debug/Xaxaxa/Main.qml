import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Xaxaxa 1.0



ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Управление компаниями и проектами"

    ITCompanyModel{
        id: companyModel
        Component.onCompleted: loadData();
    }

    ProjectModel{
        id: projectModel
        Component.onCompleted: loadData();
    }
    JobTitleModel{
        id: jobtitleModel
        Component.onCompleted: loadData();
    }
    EmployeeModel{
        id: employeeModel
        Component.onCompleted: loadData()
    }

    ColumnLayout {
        spacing: 10
        anchors.centerIn: parent

        Text {
            text: "Управление компаниями"
            font.bold: true
            font.pointSize: 16
            padding: 5
        }

        RowLayout {
            spacing: 10

            TextField {
                id: idInput
                placeholderText: "ID компании"
                width: 120
                validator: IntValidator {}
            }

            TextField {
                id: nameInput
                placeholderText: "Название компании"
                width: 180
            }

            TextField {
                id: expensesInput
                placeholderText: "Прочие расходы"
                width: 180
                validator: DoubleValidator {}
            }
        }

        RowLayout {
            spacing: 10

            Button {
                text: "Добавить компанию"
                onClicked: {
                    if (nameInput.text.trim() && expensesInput.text.trim()) {
                        companyModel.addCompany(nameInput.text, parseFloat(expensesInput.text));
                        nameInput.text = "";
                        expensesInput.text = "";
                        companyModel.loadData();
                    } else {
                        console.log("Заполните все поля для добавления компании.");
                    }
                }
            }

            Button {
                text: "Редактировать компанию"
                onClicked: {
                    const companyId = parseInt(idInput.text);
                    if (!isNaN(companyId) && nameInput.text.trim() && expensesInput.text.trim()) {
                        companyModel.updateCompany(companyId, nameInput.text, parseFloat(expensesInput.text));
                        companyModel.loadData();
                    } else {
                        console.log("Введите корректный ID компании и заполните поля для редактирования.");
                    }
                }
            }

            Button {
                text: "Удалить компанию"
                onClicked: {
                    const companyId = parseInt(idInput.text);
                    if (!isNaN(companyId)) {
                        companyModel.removeCompany(companyId);
                    } else {
                        console.log("Введите корректный ID компании для удаления.");
                    }
                }
            }
        }

        ListView {
            id: companyListView
            width: 700
            height: 150
            model: companyModel
            clip: true

            delegate: Item {
                width: companyListView.width
                height: 40

                Rectangle {
                    anchors.fill: parent
                    color: "lightgrey"
                    border.color: "black"
                    border.width: 1

                    Row {
                        anchors.fill: parent
                        spacing: 15
                        padding: 10

                        Text {
                            text: model.companyId + ": " + model.name
                            font.bold: true
                        }

                        Text {
                            text: "Расходы: " + model.expenses
                            font.italic: true
                        }
                    }
                }
            }
        }

        // Добавляем секцию для управления проектами
        Text {
            text: "Управление проектами"
            font.bold: true
            font.pointSize: 16
            padding: 5
        }

        RowLayout {
            spacing: 10

            TextField {
                id: projectIdInput
                placeholderText: "ID проекта"
                width: 120
                validator: IntValidator {}
            }

            TextField {
                id: projectNameInput
                placeholderText: "Название проекта"
                width: 180
            }

            TextField {
                id: projectCompanyIdInput
                placeholderText: "ID компании"
                width: 180
                validator: IntValidator {}
            }
        }

        RowLayout {
            spacing: 10

            Button {
                text: "Добавить проект"
                onClicked: {
                    if (projectNameInput.text && projectCompanyIdInput.text) {
                        projectModel.addProject(projectNameInput.text, parseInt(projectCompanyIdInput.text));
                        projectNameInput.text = "";
                        projectCompanyIdInput.text = "";
                    } else {
                        console.log("Заполните все поля для добавления проекта.");
                    }
                }
            }

            Button {
                text: "Редактировать проект"
                onClicked: {
                    const projectId = parseInt(projectIdInput.text);
                    if (!isNaN(projectId) && projectNameInput.text.trim() && projectCompanyIdInput.text.trim()) {
                        projectModel.updateProject(projectId, projectNameInput.text, parseInt(projectCompanyIdInput.text));
                    } else {
                        console.log("Введите корректный ID проекта и заполните поля для редактирования.");
                    }
                }
            }

            Button {
                text: "Удалить проект"
                onClicked: {
                    const projectId = parseInt(projectIdInput.text);
                    if (!isNaN(projectId)) {
                        projectModel.removeProject(projectId);
                    } else {
                        console.log("Введите корректный ID проекта для удаления.");
                    }
                }
            }
        }

        ListView {
            id: projectListView
            width: 700
            height: 150
            model: projectModel
            clip: true
            delegate: Item {
                width: projectListView.width
                height: 40

                Rectangle {
                    anchors.fill: parent
                    color: "lightgrey"
                    border.color: "black"
                    border.width: 1

                    Row {
                        anchors.fill: parent
                        spacing: 15
                        padding: 10

                        Text {
                            text: model.projectId + ": " + model.тame
                            font.bold: true
                        }

                        Text {
                            text: "ID компании: " + model.id_company
                            font.italic: true
                        }
                    }
                }
            }
        }

        Text {
            text: "Управление должностями"
            font.bold: true
            font.pointSize: 16
            padding: 5
        }

        RowLayout {
            spacing: 10

            TextField {
                id: jobtitleIdInput
                placeholderText: "ID должностт"
                width: 120
                validator: IntValidator {}
            }

            TextField {
                id: jobtitleNameInput
                placeholderText: "Название должности"
                width: 180
            }

            TextField {
                id: jobtitleSalaryInput
                placeholderText: "Зарплата должности"
                width: 180
                validator: IntValidator {}
            }
            TextField{
                id: jobtitleStandartHoursInput
                width: 180
                placeholderText: "Норма часов"
            }
        }

        RowLayout {
            spacing: 10

            Button {
                text: "Добавить должность"
                onClicked: {
                    if (jobtitleNameInput.text && jobtitleSalaryInput.text && jobtitleStandartHoursInput) {
                        jobtitleModel.addJobtitle(projectNameInput.text, parseFloat(jobtitleSalaryInput.text), parseFloat(jobtitleStandartHoursInput));
                        jobtitleNameInput.text = "";
                        jobtitleSalaryInput.text = "";
                        jobtitleStandartHoursInput.text = "";
                    } else {
                        console.log("Заполните все поля для добавления проекта.");
                    }
                }
            }

            Button {
                text: "Редактировать должность"
                onClicked: {
                    const jobtitleId = parseInt(jobtitleIdInput.text);
                    if (!isNaN(jobtitleId) && jobtitleNameInput.text.trim() && jobtitleSalaryInput.text.trim() && jobtitleStandartHoursInput.text) {
                        jobtitleModel.updateJobtitle(jobtitleId, projectNameInput.text, parseInt(projectCompanyIdInput.text));
                    } else {
                        console.log("Введите корректный ID проекта и заполните поля для редактирования.");
                    }
                }
            }

            Button {
                text: "Удалить должность"
                onClicked: {
                    const jobtitleId = parseInt(jobtitleIdInput.text);
                    if (!isNaN(jobtitleId)) {
                        jobtitleModel.removeJobtitle(jobtitleId);
                    } else {
                        console.log("Введите корректный ID проекта для удаления.");
                    }
                }
            }
        }

        ListView {
            id: jobtitleListView
            width: 700
            height: 150
            model: jobtitleModel
            clip: true
            delegate: Item {
                width: jobtitleListView.width
                height: 40

                Rectangle {
                    anchors.fill: parent
                    color: "lightgrey"
                    border.color: "black"
                    border.width: 1

                    Row {
                        anchors.fill: parent
                        spacing: 15
                        padding: 10

                        Text {
                            text: model.jobtitletId + ": " + model.name
                            font.bold: true
                        }

                        Text {
                            text: "зарплата: " + model.salary
                            font.italic: true
                        }
                    }
                }
            }
        }

        Text {
            text: "Управление сотрудниками"
            font.bold: true
            font.pointSize: 16
            padding: 5
        }

        RowLayout {
            spacing: 10

            TextField {
                id: employeeIdInput
                placeholderText: "ID сотрудника"
                width: 120
                validator: IntValidator {}
            }

            TextField {
                id: employeeNameInput
                placeholderText: "имя сотрудника"
                width: 180
            }

            TextField {
                id: employeeid_companyInput
                placeholderText: "id компании"
                width: 180
                validator: IntValidator {}
            }
            TextField{
                id: employeeid_jobtitleInput
                width: 180
                placeholderText: "id должности"
            }
            TextField{
                id: employeeEmailInput
                placeholderText: "Емаил"
                width: 180
            }
            TextField{
                id: employeePhoneInput
                placeholderText: "Номер телефона"
            }
        }

        RowLayout {
            spacing: 10

            Button {
                text: "Добавить сотрудника"
                onClicked: {
                    if (employeeNameInput.text && employeeid_jobtitleInput.text && employeeid_companyInput.text && employeeEmailInput.text && employeePhoneInput.text) {
                        employeeModel.addEmployee(employeeNameInput.text, parseInt(employeeid_companyInput.text), parseInt(employeeid_jobtitleInput), employeeEmailInput.text, employeePhoneInput.text);
                        employeeNameInput.text = "";
                        employeeid_companyInput.text = "";
                        employeeid_jobtitleInput.text = "";
                        employeeEmailInput.text = "";
                        employeePhoneInput.text = "";
                    } else {
                        console.log("Заполните все поля для добавления проекта.");
                    }
                }
            }

            Button {
                text: "Редактировать сотрудника"
                onClicked: {
                    const employeeId = parseInt(employeeIdInput.text);
                    if (!isNaN(employeeId) && employeeNameInput.text.trim() && employeeid_jobtitleInput.text && employeeid_companyInput.text && employeeEmailInput.text && employeePhoneInput.text) {
                        employeeModel.updateEmployee(employeeId, employeeNameInput.text, parseInt(employeeid_companyInput.text), parseInt(employeeid_jobtitleInput), employeeEmailInput.text, employeePhoneInput.text);
                    } else {
                        console.log("Введите корректный ID проекта и заполните поля для редактирования.");
                    }
                }
            }

            Button {
                text: "Удалить сотрудника"
                onClicked: {
                    const employeeId = parseInt(employeeIdInput.text);
                    if (!isNaN(employeeId)) {
                        employeeModel.removeEmployee(employeeId);
                    } else {
                        console.log("Введите корректный ID проекта для удаления.");
                    }
                }
            }
        }

        ListView {
            id: employeeListView
            width: 700
            height: 150
            model: employeeModel
            clip: true
            delegate: Item {
                width: employeeListView.width
                height: 40

                Rectangle {
                    anchors.fill: parent
                    color: "lightgrey"
                    border.color: "black"
                    border.width: 1

                    Row {
                        anchors.fill: parent
                        spacing: 15
                        padding: 10

                        Text {
                            text: model.employeetId + ": " + model.name
                            font.bold: true
                        }

                        Text {
                            text: "Емаил: " + model.email + " ид должности" +model.id_jobtitle
                            font.italic: true
                        }
                    }
                }
            }
        }

    }
}
