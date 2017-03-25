import QtQuick 2.0
import QtQuick.Controls.Styles 1.1
import QtQuick.Controls 1.2
Rectangle {

    x: 8
    y: 8

    width: 200
    height: parent.height - 16
    color: "#fefefe"
    property alias theText: stackText.text
    TextArea {
        id: stackText

        text: qsTr("I'm the Stack :)<br><br>")
//        wrapMode: Text.WordWrap
        readOnly: true
        textFormat: TextEdit.RichText
        verticalAlignment: Text.AlignBottom
        anchors.fill: parent

        anchors.bottomMargin: 0
        style: TextAreaStyle{
        backgroundColor: "#efefef"
            textColor: "black"

        }
        font.pointSize: 12
//        horizontalAlignment: Text.Center
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

        }
    }




}


