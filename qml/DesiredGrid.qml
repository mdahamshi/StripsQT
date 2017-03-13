
import QtQuick 2.0

import "functions.js" as MyScripts

Item {

    enabled: false
    width: MyScripts.gridWidth
    height: MyScripts.gridHeight
    anchors.right:  parent.right
    anchors.rightMargin:  10
    anchors.top: desired.bottom
    anchors.topMargin: 30

    Grid{
        id: hisGrid
        rows: MyScripts.maxRow; columns: MyScripts.maxColumn



        property int colorIndex: 0


        Repeater{
            model:myBroker.getBoardSize()
            delegate: Block{

            }
        }


    }
    MouseArea{
        anchors.fill: parent
        acceptedButtons: Qt.RightButton | Qt.LeftButton
        onPressed: {
            console.log(mouse.x)
        }
    }
    function changeColor(i,j){

        hisGrid.childAt(j*MyScripts.blockSize, i*MyScripts.blockSize).changeColor(i,j);
    }

}
