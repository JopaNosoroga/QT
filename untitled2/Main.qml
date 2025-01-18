import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 600
    height: 400
    title: "Person Management"

    Column {
        anchors.fill: parent
        spacing: 10

        TextField {
            id: nameInput
            placeholderText: "Enter name"
        }

        TextField {
            id: ageInput
            placeholderText: "Enter age"
            validator: IntValidator { bottom: 0 }
        }

        TextField {
            id: addressInput
            placeholderText: "Enter address"
        }

        TextField {
            id: phoneInput
            placeholderText: "Enter phone number"
        }

        TextField {
            id: jobInput
            placeholderText: "Enter job title"
        }

        Button {
            text: "Add Person"
            onClicked: {
                myModel.addPerson(nameInput.text, ageInput.text, addressInput.text, phoneInput.text, jobInput.text)
                nameInput.text = ""
                ageInput.text = ""
                addressInput.text = ""
                phoneInput.text = ""
                jobInput.text = ""
            }
        }

        ListView {
            id: listView
            width: parent.width
            height: 250
            model: myModel

            delegate: Item {
                width: listView.width
                Column {
                    Text { text: "Name: " + model.name }
                    Text { text: "Age: " + model.age }
                    Text { text: "Address: " + model.address }
                    Text { text: "Phone: " + model.phone }
                    Text { text: "Job: " + model.job }

                    Button {
                        text: "Remove"
                        onClicked: myModel.removePerson(model.id) // Чтобы передать id
                    }
                }
            }
        }
    }
}
