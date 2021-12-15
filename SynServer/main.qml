/*import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: window

    width: 300
    height: 100
    visible: true
    title: qsTr("Hello World")

    Text {
        id: deviceId
        text: qsTr("Device id: ") + calibrator.deviceInfo
    }
}*/
import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtCharts 2.3
import QtQuick.Layouts 1.15

Window {
    width: 833
    height: 505
    visible: true
    title: qsTr("SynServer")

    ChartView {
        title: ""
        titleColor: "black"
        objectName: "chart"
        anchors.fill: parent
        antialiasing: true

        LineSeries {
            objectName: "lineSeries"
            name: "S11"
            color: "black"

        }
    }

    Button {
        x: 56
        y: 470
        objectName: "vnaButton"
        anchors.left: parent
        font.pixelSize: 20
        checkable: true
        text: (checked ? "VNA enabled" : "VNA off")
        onClicked: chartControl.updateData()
    }

    Text {
        id: sas_1
        font.pixelSize: 20
        text: qsTr("IP")
        x: 45
        y: 38
    }

    Text {
        id: sas_2_SN
        font.pixelSize: 20
        text: qsTr("SN")
        x: 470
        y: 38
    }

    Rectangle {
        id: sas_SN
        width: myText_SN.contentWidth + 20
        height: 46
        x: 500
        y: 26
        color: "white"
        border.color: "black"

        MouseArea {
            id: myMouseArea_SN
            anchors.fill: parent
            onClicked: parent.width = myText_SN.contentWidth
        }

        TextInput {
            id: myText_SN
            anchors.centerIn: parent
            font.family: "Helvetica"
            font.pixelSize: 20
            text: qsTr(" ") + calibrator.deviceInfo
            focus: true;
            selectByMouse: true

            horizontalAlignment: Text.AlignHCenter
            cursorVisible: false

            signal qmlSignal(string msg)
        }
    }

    Rectangle {
        id: sas_IP
        width: myText.contentWidth + 20
        height: 46
        x: 73
        y: 26
        color: "white"
        border.color: "black"

        MouseArea {
            id: myMouseArea
            anchors.fill: parent
            onClicked: parent.width = myText.contentWidth
        }

        TextInput {
            id: myText
            anchors.centerIn: parent
            font.family: "Helvetica"
            font.pixelSize: 20
            text: qsTr("Введите IP адрес!")
            focus: true;
            selectByMouse: true

            horizontalAlignment: Text.AlignHCenter
            cursorVisible: false

            signal qmlSignal(string msg)
        }
    }
}


