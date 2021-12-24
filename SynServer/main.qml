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

        Rectangle {
            QRcode {
            }
        }
    }

    StackLayout {
        width: parent.width
        currentIndex: bar.currentIndex

        Item {
            id: homeTab
        }

        Item {
            id: discoverTab
        }
        Item {
            id: activityTab
        }
    }
}
