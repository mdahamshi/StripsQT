
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
    signal setTheStatus(var msg);




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
    function checkDrag(x,y,myWidth ,myHeight ,myId){

        var mySecX = x+myWidth;
        var mySecY = y + myHeight;

        for (var ind = 0 ;ind < addedObjects.length ;ind++){
            var theObject = addedObjects[ind];
            if(theObject.myId !== myId){
                var hisFirstCor = Qt.point(theObject.x,theObject.y);
                var hisSecCor = Qt.point(theObject.x + theObject.width ,theObject.y);
                var hisThirdCor = Qt.point(theObject.x  ,theObject.y + theObject.height);
                var hisForthCor = Qt.point(theObject.x + theObject.width ,theObject.y + theObject.height);

                //checking if there is object in the area before dropping
                if( (hisFirstCor.x > x || hisSecCor.x > x || hisThirdCor.x > x || hisForthCor.x > x )
                        && (hisFirstCor.x < mySecX || hisSecCor.x < mySecX || hisThirdCor.x < mySecX || hisForthCor.x < mySecX)
                        && (hisFirstCor.y > y || hisSecCor.y > y || hisThirdCor.y > y || hisForthCor.y > y)
                        && (hisFirstCor.y < mySecY || hisSecCor.y < mySecY || hisThirdCor.y < mySecY || hisForthCor.y < mySecY)
                        ){
                    setTheStatus("Wrong Move !");
                    return false;
                }



            }
        }
        //checking if there is a wall before dropping
       var firstPoint =  MyScripts.toBoardCor(MyScripts.toBlockCor(x,y));
       var steps =  MyScripts.toBoardCor(MyScripts.toBlockCor(myWidth,myHeight));
//            console.log("check walls x,y,stepx,stepy ",firstPoint,steps);
       for (var i = firstPoint.x ;i <steps.x+firstPoint.x ;i++)
           for (var j = firstPoint.y ;j < steps.y+firstPoint.y  ;j++)
               if(myBroker.getStatus(i,j,MyGlobals.currentBoard) === MyGlobals.wall){
//                        console.log("wall detected at ",i,j);
                   setTheStatus("Wrong Move !");
                   return false;
               }
        setTheStatus("After finishing<br/>Click begin !")
        return true;
    }

    function addObjectsToBackend(){
        var ind = 0;
        while(ind  < addedObjects.length){
            var tmpObject = addedObjects[ind++];
            var firstPoint =  MyScripts.toBoardCor(MyScripts.toBlockCor(tmpObject.x,tmpObject.y));
            var secPoint = MyScripts.toBoardCor(MyScripts.toBlockCor(tmpObject.x+tmpObject.width,tmpObject.y+tmpObject.height));
            myBroker.addObject(firstPoint.x,firstPoint.y,secPoint.x -1,secPoint.y-1,tmpObject.myId ,MyGlobals.desiredBoard);
        }
        myBroker.printBoard();


    }

}
