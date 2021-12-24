import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtCharts 2.3
import QtQuick.Layouts 1.15


Window {
    width: 1095
    height: 680
    visible: true
    color: "black"
    title: qsTr("SynServer")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Rectangle {
            Chart {
                objectName: "chart"
            }
        }
    }

    Button {
        x: 56
        y: 470
        anchors.left: parent

        font.pixelSize: 20
        checkable: true
        text: (checked ? "VNA enabled" : "VNA off")
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

    StackLayout {
        width: parent.width
        currentIndex: bar.currentIndex

        Item {
            id: homeTab
        }

        TextInput {
            id: myText
            anchors.centerIn: parent
            font.family: "Helvetica"
            //font.pointSize:  50
            font.pixelSize: 20
            text: qsTr(" ") + server.serverAddress
            focus: true;
            selectByMouse: true

            horizontalAlignment: Text.AlignHCenter
            cursorVisible: false

            signal qmlSignal(string msg)
        }
    }
}
