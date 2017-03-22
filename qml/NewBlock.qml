import QtQuick 2.0
import "functions.js" as MyScripts


Item {
    id: root

    property string colorKey
    property int myId: -1
    property var defaultParent: parent

    MouseArea {
            id: mouseArea

            width: root.width; height: root.height
//            anchors.centerIn: parent

            drag.target: tile

            onReleased: {

                if(tile.Drag.target !== null){
                    var newX = tile.Drag.target.x;
                    var newY = tile.Drag.target.y;
                    if(defaultParent.checkDrag(newX ,newY ,width ,height ,myId)){
                        parent = tile.Drag.target !== null ? tile.Drag.target.parent.parent : root;
                        root.x = newX;
                        root.y = newY;
                        x = newX;
                        y = newY;
                    }

                }

//                console.log("x,y ",x,y,parent,myId);
            }

            Rectangle {
                id: tile

                width: parent.width; height: parent.height
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                color: colorKey

                Drag.keys: [  ]
                Drag.active: mouseArea.drag.active
//                Drag.hotSpot.x: 20
//                Drag.hotSpot.y: 20
                states: State {
                    when: mouseArea.drag.active
                    ParentChange { target: tile; parent: root }
                    AnchorChanges { target: tile; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
                }

            }
        }



}
