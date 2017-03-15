
import QtQuick 2.0

import "functions.js" as MyScripts
import "../singleton"

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
    property var objects: []

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
//            console.log("current mouse area pressed" + mouse.x+","+mouse.y)
            if(mouse.button & Qt.LeftButton){
                pressedPoint = toBlockCor(mouse.x,mouse.y);
                lastHoverPoint = pressedPoint;
                setNewHover();
//                console.log("lastHov" + lastHoverPoint +"pressed:"+pressedPoint)
            }

        }

        onReleased: {
            if(mouse.button & Qt.LeftButton){
                releasedPoint = toBlockCor(mouse.x,mouse.y);
                if(!legalObject(pressedPoint,releasedPoint)){
                    clearLastHovered();
                }
                else{
                    setNewObjectToFull(pressedPoint,releasedPoint);
                    objects.push([pressedPoint,releasedPoint,colorIndex+3]);
//                    console.log(objects)
                    if (MyScripts.getAcolor(colorIndex) === MyScripts.lastColor)
                        colorIndex = 0;
                    else
                        colorIndex += 1;
                }

            }
            else{


            }

//            setTempColor(releasedPoint.x,releasedPoint.y);
//            console.log("pressed: "+pressedPoint.x +","+pressedPoint.y + " released: "+ releasedPoint.x + ","+ releasedPoint.y)
        }

        onPositionChanged: {
            if(pressed){

                var currentBlock = toBlockCor(mouse.x,mouse.y);
                if(currentBlock.x !== lastHoverPoint.x || currentBlock.y !== lastHoverPoint.y)
                    updateHoverRec(currentBlock);
            }
        }
    }
    function changeColor(i,j){

        hisGrid.childAt(j*MyScripts.blockSize, i*MyScripts.blockSize).changeColor(i,j,MyGlobals.currentBoard);
    }
    function setTempColor(x,y){
        if(checkBlockCor(x,y))
             hisGrid.childAt(x*MyScripts.blockSize, y*MyScripts.blockSize).tempColor(MyScripts.getAcolor(colorIndex));

    }
    function resetColor(x,y){
        if(checkBlockCor(x,y))
            hisGrid.childAt(x*MyScripts.blockSize, y*MyScripts.blockSize).resetColor();
    }


    function updateHoverRec(currentBlock){

        clearLastHovered();
//        console.log("currentBlock: "+currentBlock);
        lastHoverPoint =currentBlock;
        setNewHover();
    }

    function clearLastHovered(){
        var incX = pressedPoint.x - lastHoverPoint.x > 0 ? -1 : 1 ;
        var incY = pressedPoint.y - lastHoverPoint.y > 0 ? -1 : 1 ;
        for (var x=pressedPoint.x ;x !== lastHoverPoint.x + incX ;x += incX)
            for(var y=pressedPoint.y ; y !== lastHoverPoint.y + incY ;y += incY){
//                console.log("setNewHover: "+x+","+y);
                if(getGuiType(x,y) === MyGlobals.free)
                    resetColor(x,y);

            }



    }
    function setNewHover(){
        var incX = pressedPoint.x - lastHoverPoint.x > 0 ? -1 : 1 ;
        var incY = pressedPoint.y - lastHoverPoint.y > 0 ? -1 : 1 ;
//        console.log("starting setNewHover for: "+pressedPoint.x+","+pressedPoint.y+" lastHover"+lastHoverPoint+" inc "+incX+","+incY)
        for (var x=pressedPoint.x ;x !== lastHoverPoint.x + incX ;x += incX)
            for(var y=pressedPoint.y ; y !== lastHoverPoint.y + incY ;y += incY){
//                console.log("setNewHover: "+x+","+y);
                setTempColor(x ,y);

            }

    }
    function toBlockCor(x,y){
       return Qt.point(Math.floor(x / MyScripts.blockSize) ,Math.floor(y / MyScripts.blockSize));
    }
    function toBoardCor(point){
        return Qt.point(point.y,point.x);
    }

    function checkBlockCor(x,y){
        if(x < MyScripts.maxColumn && y < MyScripts.maxRow && x > 0 && y > 0)
            return true;
        return false;
    }
    function getGuiType(x,y){
        if(checkBlockCor(x,y))
            return hisGrid.childAt(x*MyScripts.blockSize, y*MyScripts.blockSize).getGuiType();
    }
    function setFull(x,y){
        if(checkBlockCor(x,y))
            return hisGrid.childAt(x*MyScripts.blockSize, y*MyScripts.blockSize).setTypeFull();
    }

    function legalObject(firstCor,secondCor){
        var incX = firstCor.x - secondCor.x > 0 ? -1 : 1 ;
        var incY = firstCor.y - secondCor.y > 0 ? -1 : 1 ;
//        console.log("starting legalObject for: "+firstCor.x+","+firstCor.y+" lastHover"+secondCor+" inc "+incX+","+incY)
        for (var x=firstCor.x ;x !== secondCor.x + incX ;x += incX)
            for(var y=firstCor.y ; y !== secondCor.y + incY ;y += incY){
                if(getGuiType(x,y) !== MyGlobals.free){
//                    console.log("getGuiType = "+getGuiType(x,y)+" x,y"+x+","+y)
                    return false;
                }
            }
        return true;
    }
    function setNewObjectToFull(firstCor,secondCor){
        var incX = firstCor.x - secondCor.x > 0 ? -1 : 1 ;
        var incY = firstCor.y - secondCor.y > 0 ? -1 : 1 ;
        for (var x=firstCor.x ;x !== secondCor.x + incX ;x += incX)
            for(var y=firstCor.y ; y !== secondCor.y + incY ;y += incY)
                setFull(x,y);
    }
    function addObjectsToBoard(){
        while(objects.length > 0)
        {
            var currentObj = objects.pop();
            myBroker.addObject(currentObj[0].y, currentObj[0].x,currentObj[1].y ,currentObj[1].x ,currentObj[2],MyGlobals.currentBoard);
            desiredBox.addObject(currentObj);
        }
        currentBox.enabled = false;
        currentBox.opacity = 0.5;
//        myBroker.copyBoard();
    }
    function resetGame(){
        currentBox.colorIndex = 0;
        currentBox.addedNum = 0;
        currentBox.enabled = true;
        currentBox.opacity = 1;
        objects.length = 0;
    }




}
