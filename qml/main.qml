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
    title: qsTr("STRIPS , Professor Lari Edition.")

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
                    anchors.leftMargin: stackRec.width / 2

                    horizontalAlignment: Text.AlignJustify
                    text:"<h1>Current state</h1><br/>"
                }

                Text {
                    id: desired
                    font.pointSize: 14
                    textFormat: Text.StyledText
                    anchors.left: desiredBox.left
                    anchors.leftMargin: stackRec.width / 2
                    horizontalAlignment: Text.AlignJustify
                    text:"<h1>Desired state</h1><br/>"
                }


            CurrentGrid{
                id: currentBox
            }

            DesiredGrid{
                id: desiredBox
            }

            //Buttons
            MyButton{
                id: help

                anchors.bottom: parent.bottom
                anchors.left: begin.right
                anchors.leftMargin: 20
                anchors.margins: 5
                width: 100;height: 50
                customText: "Help"
                toolTipText: "Click to display Help "

                onButtonClicked: {

                    myHelp.visible = true;
                }
             }

            MyButton{
                id: reset
                width: 100
                height: 50
                customText: "Reset"
                anchors.right: begin.left
                anchors.rightMargin: 20
                anchors.bottom: parent.bottom
                anchors.margins: 5
                toolTipText: "Click to reset board"

                onButtonClicked: {
                    myBroker.resetBoard();
                    reset.parent.resetVars();
                    status.text = "Board reseted !"
                }
            }
            MyButton{
                id: setDesired
                width: 130
                height: 50
                customText: "Set Desired ->"
                anchors.top: currentBox.bottom
                x:begin.x - 10
                anchors.margins: 5
                toolTipText: "Click to set desired state"

                onButtonClicked: {
                    if (currentBox.objects.length !== 0){
                        currentBox.addObjectsToBoard();
                        status.text = "Arrange desired state !";
                        setDesired.enabled = false;
                        opacity = 0.5;

                    }
                    else
                        status.text = "Add some Objects !"
                }
            }

            MyButton{
                id: begin
                width: 100
                height: 50
                customText: "<b>Begin</b>"
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
                toolTipText:"Click to Quit"

                onButtonClicked: {
                       Qt.quit();
                }
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
                toolTipText: "Click to show About"

                onButtonClicked: {
                    myAbout.visible = true
                }
             }

            //status text
            Text {
                id: status
                text: qsTr("Hello !<br> Click Help for instructions")
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 20
                color: "black"
                visible: true
                anchors.bottom: begin.top
                anchors.bottomMargin: 10
                 x: (parent.width -width ) /2 + stackRec.width / 2
            }

            //dialogs
            About{
                id:myAbout
            }
            Help{
                id:myHelp
            }

            //Connections
            Connections{
                target: myBroker
                onUpdateBuilding:{
//                    console.log("in update building..");
                    MyScripts.updateBoard();

                }
            }
            //functions
            function resetVars(){
                currentBox.resetGame();
                desiredBox.resetGame();
                setDesired.enabled = true;
                setDesired.opacity = 1;
            }

            Component.onCompleted: {
                currentBox.enabled = true;
                desiredBox.enabled = true;
//                console.log(myBroker.getBoardSize());
                MyScripts.updateBoard();

            }


    }

}
