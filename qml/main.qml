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
    minimumHeight: 650
    title: qsTr("STRIPS , Professor Lari Edition.")

    Item {
        anchors.fill: parent
        id: mainFrame



            Stack{
                id:stripsStack
            }


                Text {
                    id: current
                    font.pointSize: 14
                    textFormat: Text.StyledText
                    anchors.left: stripsStack.right
                    anchors.leftMargin: stripsStack.width / 2

                    horizontalAlignment: Text.AlignJustify
                    text:"<h1>Current state</h1><br/>"
                }

                Text {
                    id: desired
                    font.pointSize: 14
                    textFormat: Text.StyledText
                    anchors.left: desiredBox.left
                    anchors.leftMargin: stripsStack.width / 2
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
                        desiredBox.enabled = true;
                        desiredBox.opacity = 1;
                        begin.enabled = true;
                        begin.opacity = 1;

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
                enabled: false
                opacity: 0.5
                onButtonClicked: {
                    if(setDesired.enabled === true)
                        status.text = "Add some Objects !"
                    else
                        parent.beginTheFun();
                }
            }
            MyButton{
                id: pause
                width: 100
                height: 50
                customText: "<b>Pause</b>"
                x: (parent.width ) /2 + width / 2
                anchors.bottom: parent.bottom
                anchors.margins: 5
                toolTipText: "Click to pause/resume the simulation"
                property bool toggle: false
                visible: false

                onButtonClicked: {
                    myToggle();
                    myBroker.togglePause();


                }
                function myToggle(){
                    if(toggle){
                        toggle = ! toggle;
                        customText = "<b>Pause</b>";
                    }
                    else{
                        toggle = ! toggle;
                        customText = "<b>Resume</b>";
                    }
                }
                function reset(){
                    customText = "<b>Pause</b>";
                    toggle = false;
                    visible = false;
                }
            }

            MyButton{
                id: quit
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.margins: 8
                width: 40;height: 40
                color: "red"
                customText: "X"
                fontSize: 20
                toolTipText:"Click to Quit"

                onButtonClicked: {
                    status.text = "Please wait ..."
                    myBroker.setResetReq();
                    myBroker.togglePause();
                       Qt.quit();
                }
            }

            MyButton{
                id: about
                anchors.bottom: parent.bottom
                anchors.left: stripsStack.right
                anchors.margins: 8
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
                text: qsTr("Hello !<br>Begin with adding some objects to current state")
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 20
                color: "black"
                visible: true
                anchors.bottom: begin.top
                anchors.bottomMargin: 10
                 x: (parent.width -width ) /2 + stripsStack.width / 2
            }

            //dialogs
            About{
                id:myAbout
            }
            Help{
                id:myHelp
                visible: false
            }

            //Connections
            Connections{
                target: myBroker
                onUpdateBuilding:{
//                    console.log("in update building..");
                    MyScripts.updateBoard();

                }
                onUpdateState:{
                    status.text = "Rotation failed, restoring board...";
                }

                onUpdateCurrent:{
                    MyScripts.updateCurrentBoard();
                     status.text = "Here we Go !<br/>We are now stripping things for you :)"
                }

                onResetAll:{
                    resetVars();
                    pause.reset();
                }
                onUpdateStack:{
                    stripsStack.theText = str;

                }
                onSolved:{
                    status.text = "Solved successfully !"

                    MyScripts.updateCurrentBoard();
                    pause.reset();

                }
                onNoSol:{
                    status.text = "No solution found !"
                    pause.reset();

                }
            }
            Connections{
                target: currentBox
                onSetTheStatus:{
                    status.text = msg;
                }
            }
            Connections{
                target: desiredBox
                onSetTheStatus:{
                    status.text = msg;
                }
            }


            //functions
            function resetVars(){
                currentBox.resetGame();
                desiredBox.resetGame();
                setDesired.enabled = true;
                setDesired.opacity = 1;
                desiredBox.enabled = true;
                desiredBox.opacity = 0.5;
                begin.enabled = true;
                pause.reset();
                begin.opacity = 1;
                begin.enabled = false;
                begin.opacity = 0.5;
            }
            function beginTheFun(){
                status.text = "Here we Go !<br/>We are now stripping things for you :)"
                desiredBox.addObjectsToBackend();
                desiredBox.enabled = false;
                currentBox.opacity = 1;
                begin.enabled = false;
                begin.opacity = 0.5;
                pause.visible = true;
                myBroker.beginSolving();
            }

            Component.onCompleted: {
                currentBox.enabled = true;

//                console.log(myBroker.getBoardSize());
                MyScripts.updateBoard();

            }


    }

}
