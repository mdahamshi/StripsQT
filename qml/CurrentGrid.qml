
import QtQuick 2.0

import "functions.js" as MyScripts

Item {
    enabled: false
    width: MyScripts.gridWidth
    height: MyScripts.gridHeight
    anchors.left: stackRec.right
    anchors.leftMargin: 10
    anchors.top: current.bottom
    anchors.topMargin: 30
    property int addedNum: 0
    property var pressedPoint:Qt.point(-1,-1)
    property var releasedPoint:Qt.point(-1,-1)
    property var lastHoverPoint:Qt.point(-1,-1)
    property int colorIndex: 0

    Grid{
        id: hisGrid
        rows: MyScripts.maxRow; columns: MyScripts.maxColumn

        Repeater{
            model:myBroker.getBoardSize()
            delegate: Block{

            }
        }
    }
    MouseArea{
        id:myMouse
        anchors.fill: parent
        acceptedButtons: Qt.RightButton | Qt.LeftButton
        onPressed: {
            console.log("current mouse area pressed")
            if(mouse.button & Qt.LeftButton){
                pressedPoint.x = Math.floor(mouse.x / MyScripts.blockSize);
                pressedPoint.y = Math.floor(mouse.y / MyScripts.blockSize);
                lastHoverPoint = pressedPoint;
            }

        }

        onReleased: {
            if(mouse.button & Qt.LeftButton){
                releasedPoint.x = Math.floor(mouse.x / MyScripts.blockSize);
                releasedPoint.y = Math.floor(mouse.y / MyScripts.blockSize);

            }
            setTempColor(releasedPoint.x,releasedPoint.y);
            console.log("pressed: "+pressedPoint.x +","+pressedPoint.y + " released: "+ releasedPoint.x + ","+ releasedPoint.y)
        }

        onPositionChanged: {
            if(pressed){
                console.log("in pos chng last hovered "+lastHoverPoint);

                updateHoverRec(Math.floor(mouse.x / MyScripts.blockSize),Math.floor(mouse.y / MyScripts.blockSize));
            }
        }
    }
    function changeColor(i,j){

        hisGrid.childAt(j*MyScripts.blockSize, i*MyScripts.blockSize).changeColor(i,j);
    }
    function setTempColor(j,i){
        hisGrid.childAt(j*MyScripts.blockSize, i*MyScripts.blockSize).tempColor(MyScripts.getAcolor(colorIndex));
        if(MyScripts.getAcolor(colorIndex) === MyScripts.lastColor)
            colorIndex = 0;
        else
            colorIndex += 1;
    }


    function updateHoverRec(x,y){
        console.log("in hovered "+x+","+y);
        clearLastHovered();
        lastHoverPoint = Qt.point(x,y);
        setNewHover();

    }
    function clearLastHovered(){
        var xStep = pressedPoint.x - lastHoverPoint.x > 0 ? -1 : 1 ;
        var yStep = pressedPoint.y - lastHoverPoint.y > 0 ? -1 : 1 ;

    }
    function setNewHover(){

    }

}
