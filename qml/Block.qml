import QtQuick 2.0
import QtQuick.Controls 2.0
import "functions.js" as MyScripts
import "../singleton"

Item {
    id: block
    width: MyGlobals.blockSize
    height: MyGlobals.blockSize
    property int type: 0
    property string oldColor: blockRec.color
    property int oldType: 0
    property string oldBorder: "white"

    Rectangle{
        id:blockRec
        anchors.fill: parent
        border.color : "white"
        color: "#efefef"
    }



    function changeColor(i,j,z){
        var status = myBroker.getStatus(i,j,z);

        if(status === MyGlobals.free){
            blockRec.color = MyGlobals.freeColor;
            blockRec.border.color = "white";
            block.type = status;
        }
        else if (status === MyGlobals.wall){
            blockRec.color = MyGlobals.wallColor;
            blockRec.border.color = "black";
            block.enabled = false;
            block.type = status;
        }else{
            block.type = MyGlobals.full;
            blockRec.color = MyScripts.getAcolor(status - 3)
            blockRec.border.color = blockRec.color;
        }


        oldType = type;
    }
    function tempColor(color){
        if(block.type === MyGlobals.free){
            oldColor = blockRec.color;
//            console.log("seting to temp: "+toBlockCor(block.x,block.y)+oldColor);
            oldBorder = blockRec.border.color;
            blockRec.border.color = color;
            blockRec.color = color;

        }

    }
    function resetColor(){
         if(block.type !== MyGlobals.wall){
//             console.log("reseting to oldcolor: "+toBlockCor(block.x,block.y)+oldColor);
             blockRec.border.color = oldBorder;
             blockRec.color = oldColor;
             resetType();

         }
    }
    function setTypeFull(){
        oldType = type;
        type = MyGlobals.full;
    }

    function resetType(){
        block.type = oldType;
    }

    function toBlockCor(x,y){
       return Qt.point(Math.floor(x / MyScripts.blockSize) ,Math.floor(y / MyScripts.blockSize));
    }
    function getGuiColor(){
        return blockRec.color;
    }
    function getGuiType(){
//        console.log("get block type : "+block.type);
        return block.type;
    }

    MouseArea{
//            anchors.fill: parent
//           hoverEnabled: true
//            onEntered: {
//                block.parent.parent.updateHoverRec(toBlockCor(block.x,block.y));
//            }
//            onExited: {
//                block.parent.parent.updateHoverRec(toBlockCor(block.x,block.y));
//            }


        }





}
