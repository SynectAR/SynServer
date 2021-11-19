import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: window

    width: 300
    height: 100
    visible: true
    title: qsTr("Hello World")

    Text {
        id: deviceId
        text: qsTr("Device id: ") + server.deviceInfo
    }
    Text {
        id: ip
        y: 15
        text: qsTr("Server ip: ") + server.ip
    }
}
