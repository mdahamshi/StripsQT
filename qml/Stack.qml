import QtQuick 2.0

Rectangle {

    x: 8
    y: 8

    width: 200
    height: parent.height - 16
    color: "#efefef"
    property alias theText: stackText.text
    Text {
        id: stackText
        text: qsTr("text")
        anchors.fill: parent
        font.pointSize: 16
        horizontalAlignment: Text.Center
        property alias fontSize: stackText.font.pointSize
    }
    MyButton{
        id: zoomin
        width: 40
        height: 40
        customText: "+"
        z:2
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        toolTipText: "Click to zoom in"
        onButtonClicked: {
            stackText.fontSize = stackText.fontSize + 1
            names.fontSize = names.fontSize + 1
        }
    }
    MyButton{
        id: zoomout
        width: 40
        height: 40
        customText: "-"
        z:2
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        toolTipText: "Click to zoom out"
        onButtonClicked: {
            stackText.fontSize = stackText.fontSize - 1
             names.fontSize = names.fontSize - 1
        }
    }




}


