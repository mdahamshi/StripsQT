import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.2
import QtQuick 2.7


Dialog{
    id: help
    title: "Help"
    width: 640
    height: 640


    contentItem: Column{

            MyButton{
                id: ret
                width: 100
                height: 50
                customText: "return"
                z:2
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.rightMargin: 20
                onButtonClicked: {
                    help.visible = false
                }
                toolTipText: "Click to return to Home"
            }
            MyButton{
                id: zoomin
                width: 50
                height: 50
                customText: "+"
                z:2
                anchors.right: parent.right
                anchors.bottom: ret.bottom
                anchors.rightMargin: 18
                toolTipText: "Click to zoom in"
                onButtonClicked: {
                    helpText.fontSize = helpText.fontSize + 1
                }
            }
            MyButton{
                id: zoomout
                width: 50
                height: 50
                customText: "-"
                z:2
                anchors.left: parent.left
                anchors.bottom: ret.bottom
                anchors.rightMargin: 20
                toolTipText: "Click to zoom out"
                onButtonClicked: {
                    helpText.fontSize = helpText.fontSize - 1
                }
            }




        TextArea {
            id: helpText
            property alias fontSize: helpText.font.pointSize
            width: parent.width
            height: parent.height
            textFormat: TextEdit.RichText
            textMargin: 10
            horizontalAlignment: Text.AlignJustify
            readOnly: true
            font.pointSize: 13
            anchors.centerIn: parent
            wrapMode: Text.WordWrap
            text: qsTr("<h1>How to use:</h1><br>
                <ol>
                    <li>Begin by adding the objects to the current state - click and drag.</li><p></p>
                    <br/><img src=\"qrc:/Res/h1.png\"></img><br/>
                     <li>When you finish adding all the items, click on \"Set Desired->\" button.</li>
                   <br/> <br/><img src=\"qrc:/Res/h2.png\"></img><br/>
                    <li>Now arrange the desired state as you like - click and drag.</li> <br/>
                   <br/> <br/><img src=\"qrc:/Res/h3.png\"></img><br/>
                     <li>After finishing the arrange operation, Click on begin to start the simulator.</li>
               <br/>     <br/><img src=\"qrc:/Res/h4.png\"></img><br/>
                       </ol><br/>
                        <b>** At any time, you can click the \"reset\" button to clean the two boards.<p></p>
                        </br><br/><br/><br/></b><p></p>");

        }

    }
}
