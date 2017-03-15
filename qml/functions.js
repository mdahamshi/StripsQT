var blockSize = 20;
var maxColumn = 23;
var maxRow = 15;
var gridWidth = blockSize * maxColumn;
var gridHeight = blockSize  * maxRow;
var colorQueue = ["blue" ,"green" ,"red" ,"yellow" ,"#810512" ,"#888801","lightblue" ,"lightgreen" ,"purple" ,"#759122" ,"lightpink"];
var colorIndex = 0;
var objects = [];
var lastColor = "lightpink";
function index(column, row) {
    return column + (row * maxColumn);
}



function updateBoard() {

    for (var row = 0; row < maxRow; row++) {
        for (var column = 0; column < maxColumn; column++) {
            currentBox.changeColor(row,column);
            desiredBox.changeColor(row,column);
//            (currentBox.hisGrid.children[index(column, row)]).changeColor(row,column);
//            (desiredBox.desiredGrid.children[index(column, row)]).changeColor(row,column);

        }
    }
}
function updateCurrentBoard() {

    for (var row = 0; row < maxRow; row++) {
        for (var column = 0; column < maxColumn; column++) {
            currentBox.changeColor(row,column);

//            (currentBox.hisGrid.children[index(column, row)]).changeColor(row,column);
//            (desiredBox.desiredGrid.children[index(column, row)]).changeColor(row,column);

        }
    }
}

function getAcolor(c){
    return colorQueue[c];
}

