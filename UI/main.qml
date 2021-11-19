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
    //color: "black"
    title: qsTr("SynServer")

    ChartView {
        title: ""
        titleColor: "black"
        anchors.fill: parent
        antialiasing: true

        LineSeries {
            //name: ""
            color: "black"
            XYPoint { x: 0; y: 0 }
            XYPoint { x: 1.1; y: 2.1 }
            XYPoint { x: 1.9; y: 3.3 }
            XYPoint { x: 2.1; y: 2.1 }
            XYPoint { x: 2.9; y: 4.9 }
            XYPoint { x: 3.4; y: 3.0 }
            XYPoint { x: 4.1; y: 3.3 }

        }
    }

    Button {
        x: 56
        y: 470
        anchors.left: parent
        //width: 100
        //height: 40
        font.pixelSize: 20
        checkable: true
        text: (checked ? "VNA enabled" : "VNA off")
    }


    /*Button {
        text: "VNA"
        x: 73
        y: 45
    }*/

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

    /*Rectangle {
        id: sas_VNA
        width: myText_VNA.contentWidth + 40
        height: 46
        x: 73
        y: 450
        color: "white"
        border.color: "black"

        MouseArea {
            id: myMouseArea_VNA
            anchors.fill: parent
            onClicked: parent.width = myText_SN.contentWidth
        }


        TextInput {
            id: myText_VNA
            anchors.centerIn: parent
            font.family: "Helvetica"
            text: qsTr("VNA")
            focus: true
            selectByMouse: true
            horizontalAlignment: Text.AlignHCenter
            cursorVisible: false
            signal qmlSignal(string msg)
        }
    }*/

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
            text: qsTr("Серийный номер!")
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
        //left: 200
        color: "white"
        border.color: "black"
        //anchors.left: parent

        MouseArea {
            id: myMouseArea
            anchors.fill: parent
            onClicked: parent.width = myText.contentWidth
        }

        TextInput {
            id: myText
            anchors.centerIn: parent
            font.family: "Helvetica"
            //font.pointSize:  50
            font.pixelSize: 20
            text: qsTr("Введите IP адрес!")
            focus: true;
            selectByMouse: true

            horizontalAlignment: Text.AlignHCenter
            cursorVisible: false

            signal qmlSignal(string msg)
        }
    }

    /*Button {
        text: "VNA"
    }*/
}


