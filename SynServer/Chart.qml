import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtCharts 2.3
import QtQuick.Layouts 1.15

ChartView {
    //title: "Spline"
    anchors.fill: parent
    antialiasing: true

    SplineSeries {
        //name: "SplineSeries"
        XYPoint { x: 0; y: 0.0 }
        XYPoint { x: 1.1; y: 3.2 }
        XYPoint { x: 1.9; y: 2.4 }
        XYPoint { x: 2.1; y: 2.1 }
        XYPoint { x: 2.9; y: 2.6 }
        XYPoint { x: 3.4; y: 2.3 }
        XYPoint { x: 4.1; y: 3.1 }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

        RowLayout {
            Layout.alignment: Qt.AlignBottom | Qt.AlignRight

            Button {
                font.pixelSize: 20
                checkable: true
                text: (checked ? "VNA on" : "VNA off")
            }
        }
    }

        id: rootWindow;
        visible: true
        width: 200
        height: 200
        Rectangle{
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

        Rectangle{
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

        Rectangle{
            id: greenRect;
            color: "green";
            //opacity: 0.5;
            anchors.margins: 10;
            //anchors.bottom: parent.bottom;
            anchors.right: parent.right;
            anchors.top: redRect.verticalCenter;
            anchors.left: redRect.horizontalCenter;
        }

        /*Rectangle{
            id: greenRect;
            color: "green";
            opacity: 0.5;
            anchors.margins: 10;
            anchors.bottom: parent.bottom;
            anchors.right: parent.right;
            anchors.top: redRect.verticalCenter;
            anchors.left: redRect.horizontalCenter;
        }*/
}
