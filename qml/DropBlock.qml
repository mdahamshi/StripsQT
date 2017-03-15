import QtQuick 2.0
import "functions.js" as MyScripts
import "../singleton"
DropArea {
    id: dragTarget

    property string colorKey : ""
    property alias dropProxy: dragTarget
    property string myColor: "white"

    width: MyScripts.blockSize; height: MyScripts.blockSize;
    keys: [  ]      // empty. so every color can drop, except for black blocks (walls) it then "black" so no object drop on wall

    Rectangle {
        id: dropRectangle

        anchors.fill: parent
        color: myColor

        states: [
            State {
                when: dragTarget.containsDrag
                PropertyChanges {
                    target: dropRectangle
                    color: "grey"
                }
            }
        ]
    }

    function changeColor(i,j,z){
        var status = myBroker.getStatus(i,j,z);

        if(status === MyGlobals.free){
            dropRectangle.color = MyGlobals.freeColor;
            dropRectangle.border.color = "white";

        }
        else if (status === MyGlobals.wall){
            dropRectangle.color = MyGlobals.wallColor;
            dropRectangle.border.color = "black";
            dragTarget.colorKey = "black";
            dragTarget.enabled = false;
            keys = ["black"]


        }

    }


}
