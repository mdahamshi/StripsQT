
import QtQuick 2.0
import "../singleton"
import "functions.js" as MyScripts



Item {
    id:root
    enabled: false
    width: MyScripts.gridWidth
    height: MyScripts.gridHeight
    anchors.right:  parent.right
    anchors.rightMargin:  10
    anchors.top: desired.bottom
    anchors.topMargin: 30
    property var addedObjects: []
    property var myDynamicComp: Qt.createComponent("NewBlock.qml")
    property var newObjects: []





    Grid{
        id: hisGrid
        rows: MyScripts.maxRow; columns: MyScripts.maxColumn



        Repeater{
            model:myBroker.getBoardSize()
            delegate: DropBlock{

            }
        }


    }




    function changeColor(i,j){

             hisGrid.childAt(j*MyScripts.blockSize, i*MyScripts.blockSize).changeColor(i,j,MyGlobals.desiredBoard);
    }
    function addObject(object){

        var theWidth = (Math.abs(object[0].x - object[1].x)+1) * MyScripts.blockSize;
        var theHeight = (Math.abs(object[0].y - object[1].y)+1) * MyScripts.blockSize;
        var theX = (object[0].x < object[1].x ? object[0].x : object[1].x) * MyScripts.blockSize ;
        var theY = (object[0].y < object[1].y ? object[0].y : object[1].y) * MyScripts.blockSize;
        var theColor = MyScripts.getAcolor(object[2] - 3);


        var myb = myDynamicComp.createObject(root , {"x":theX ,"y": theY,"width":theWidth ,"height":theHeight,"colorKey":theColor,"myId":object[2] });
        addedObjects.push(myb);
    }

    function resetGame(){
        while(addedObjects.length > 0){
            var tmp = addedObjects.pop();
            tmp.destroy();
        }
        newObjects.length = 0;

    }

}
