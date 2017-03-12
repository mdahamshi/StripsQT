import QtQuick 2.6
import QtQuick.Window 2.2
import "../singleton"
import strips 1.0
import "functions.js" as MyScripts

Window {
    visible: true
    width: 1300
    height: 700
    minimumWidth: 1200
    minimumHeight: 600
    title: qsTr("Strips , Professor Lari Edition.")

    Item {
        anchors.fill: parent
        id: mainFrame



            Rectangle {
                id: stackRec
                x: 8
                y: 8
                width: 200
                height: parent.height - 16
                color: "#efefef"

            }


                Text {
                    id: current
                    font.pointSize: 14
                    textFormat: Text.StyledText
                    anchors.left: stackRec.right
                    anchors.leftMargin: 10

                    horizontalAlignment: Text.AlignJustify
                    text:"<h1>Current state</h1><br/>"
                }

                Text {
                    id: desired
                    font.pointSize: 14
                    textFormat: Text.StyledText
                    anchors.left: desiredGrid.left
                    horizontalAlignment: Text.AlignJustify
                    text:"<h1>Desired state</h1><br/>"
                }


            Grid{
                id: currentGrid
                rows: MyScripts.maxRow; columns: MyScripts.maxColumn
                width: MyScripts.gridWidth
                height: MyScripts.gridHeight
                anchors.left: stackRec.right
                anchors.leftMargin: 10
                anchors.top: current.bottom
                anchors.topMargin: 30

                Repeater{
                    model:myBroker.getBoardSize()
                    delegate: Block{

                    }
                }

            }
            Grid{
                id: desiredGrid
                rows: MyScripts.maxRow; columns: MyScripts.maxColumn
                width: MyScripts.gridWidth
                height: MyScripts.gridHeight
                anchors.right:  parent.right
                anchors.rightMargin:  10
                anchors.top: desired.bottom
                anchors.topMargin: 30

                Repeater{
                    model:myBroker.getBoardSize()
                    delegate: Block{

                    }
                }

            }

            MyButton{
                id: help

                anchors.bottom: parent.bottom
                anchors.left: begin.right
                anchors.leftMargin: 20
                anchors.margins: 5
                width: 100;height: 50
                color: "lightblue"
                customText: "Help"

                onButtonClicked: {

                    myHelp.visible = true;
                }

                toolTipText: "Click to display Help "
             }
            MyButton{
                id: reset
                width: 100
                height: 50
                customText: "Reset"
                color: "lightblue"

                anchors.right: begin.left
                anchors.rightMargin: 20
                anchors.bottom: parent.bottom
                anchors.margins: 5
                toolTipText: "Click to reset board"
                onButtonClicked: {
                    myBroker.resetBoard();

                }
            }

            MyButton{
                id: begin
                width: 100
                height: 50
                customText: "<b>Begin</b>"
                color: "lightblue"

                x: (parent.width ) /2 + width / 2
                anchors.bottom: parent.bottom
                anchors.margins: 5
                toolTipText: "Click to begin simulation"
                onButtonClicked: {
                    myHelp.visible = true;
                }
            }
            MyButton{
                id: quit

                anchors.bottom: parent.bottom
                anchors.right: parent.right

                anchors.margins: 5
                width: 40;height: 40
                color: "red"
                customText: "X"
                fontSize: 20

                onButtonClicked: {

                       Qt.quit();
                }

                toolTipText:"Click to Quit"
            }

            MyButton{
                id: about
                anchors.bottom: parent.bottom
                anchors.left: stackRec.right
                anchors.margins: 5
                width: 40;height: 40
                color: "green"
                customText: "?"
                fontSize: 20
                onButtonClicked: myAbout.visible = true
                toolTipText: "Click to show About"

             }

            //dialogs
            About{
                id:myAbout
            }
            Help{
                id:myHelp
            }

            Connections{
                target: myBroker
                onUpdateBuilding:{
                    console.log("in update building..");
                    MyScripts.updateBoard();

                }
            }

            Component.onCompleted: {
                console.log(myBroker.getBoardSize());
                MyScripts.updateBoard();

            }


    }

}
