var blockSize = 20;
var maxColumn = 23;
var maxRow = 15;
var gridWidth = blockSize * maxColumn;
var gridHeight = blockSize  * maxRow;

function index(column, row) {
    return column + (row * maxColumn);
}



function updateBoard() {

    for (var column = 0; column < maxColumn; column++) {
        for (var row = 0; row < maxRow; row++) {
            (currentGrid.children[index(column, row)]).changeColor(row,column);
            (desiredGrid.children[index(column, row)]).changeColor(row,column);

        }
    }


}
