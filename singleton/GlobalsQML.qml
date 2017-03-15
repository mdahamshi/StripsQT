pragma Singleton
import QtQuick 2.0

QtObject {

    property int buildWidth: 20
    property int buildHeight: 12
    property int verWalls: 3
    property int horWalls: 3
    property int totalHeight: buildHeight + verWalls
    property int totalWidth: buildWidth + horWalls
    property int blockSize: 20
    property int wall: 0
    property int free: 1
    property int full: 2
    property string wallColor: "black"
    property string freeColor: "#efefef"
    property int currentBoard: 0
    property int desiredBoard: 1


        property string blankDir: "Res/blank2.png"
        property string activeDir: "Res/active.png"
        property string blackDir: "Res/black.png"
        property string whiteDir: "Res/white.png"
        property string possibleDir: "Res/pos.png"






}
