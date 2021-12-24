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
                }
            }

            Rectangle {
                QRcode {

                }
            }
        }

        /*TabBar {
            id: tabBar
            currentIndex: swipeView.currentIndex

            TabButton {
                x: 3000
                y: 300
                text: qsTr("Page 1")
            }
            TabButton {
                text: qsTr("Page 2")
            }
        }*/

    /*TabBar {
        id: bar
        width: parent.width
        TabButton {
            text: qsTr("Home")
        }
        TabButton {
            text: qsTr("Discover")
        }
        TabButton {
            text: qsTr("Activity")
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
    }*/
}
