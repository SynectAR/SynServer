import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtCharts 2.3
import QtQuick.Layouts 1.15

ChartView {
    anchors.fill: parent
    antialiasing: true
    legend.alignment: Qt.AlignLeft

    Timer {
         id: refreshTimer
         interval: 1 / 60 * 1000
         running: false
         repeat: true
         onTriggered: {
             chartControl.updateData();
         }
     }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

        RowLayout {
            Layout.alignment: Qt.AlignBottom | Qt.AlignRight

            ComboBox {
                model: [ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 ]
                onCurrentValueChanged: {
                    chartControl.channel = currentValue
                }
            }

            Button {
                font.pixelSize: 20
                checkable: true
                text: (checked ? "VNA on" : "VNA off")
                onClicked: {
                    if (checked) {
                        chartControl.initTraces();
                        chartControl.initAxis();
                        chartControl.updateData();
                        refreshTimer.running = true;
                    }
                    else {
                        chartControl.clear();
                        refreshTimer.running = false;
                    }
                }
            }
        }
    }

    id: rootWindow;
    visible: true
    width: 200
    height: 200
    Rectangle {
        id: redRect;
        color: "white";
        border.color: "black"
        anchors.margins: 10;
        anchors.top: parent.top;
        anchors.left: parent.left
        width: parent.width/3 ;
        height: parent.height/16;

        TextInput {
            id: myText
            anchors.centerIn: parent
            font.family: "Helvetica"
            //font.pointSize:  50
            font.pixelSize: 20
            text: qsTr("IP address: ")
            focus: true;
            selectByMouse: true

            horizontalAlignment: Text.AlignHCenter
            cursorVisible: false

            signal qmlSignal(string msg)
        }
    }

    Rectangle {
        id: redRect1;
        color: "white";
        border.color: "black"
        anchors.margins: 10;
        anchors.top: parent.top;
        anchors.right: parent.right;
        width: parent.width/3 ;
        height: parent.height/16;

        TextInput {
            id: myText1
            anchors.centerIn: parent
            font.family: "Helvetica"
            //font.pointSize:  50
            font.pixelSize: 20
            text: qsTr("Serial number: ") + calibrator.deviceInfo
            focus: true;
            selectByMouse: true

            horizontalAlignment: Text.AlignHCenter
            cursorVisible: false

            signal qmlSignal(string msg)
        }
    }

    Rectangle {
        id: greenRect;
        color: "green";
        //opacity: 0.5;
        anchors.margins: 10;
        //anchors.bottom: parent.bottom;
        anchors.right: parent.right;
        anchors.top: redRect.verticalCenter;
        anchors.left: redRect.horizontalCenter;
    }
}
