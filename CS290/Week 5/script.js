var dom = document.body;

function appendButton(name, elem, action)
{
    var button = document.createElement("button");
    button.textContent = name;
    button.style.margin = "5px";
    elem.appendChild(button);

    if(action !== "undefined" )
    {
        button.addEventListener("click", action);
    }
}

var Table = function(appendTo, rows, cols) {

    /* Private functions, variables*/
    var currentRow = 1;
    var currentCol = 1;
    var maxRow = rows;
    var maxCol = cols;
    var defaultBorderStyle = "1px solid";
    var selectedBorderStyle = "3px solid";
    var elements = [];

    var select = function(row, col) {
        if(row > maxRow || col > maxCol || row < 1 || col < 1)
            return;

        elements[currentRow - 1][currentCol - 1].style.border = defaultBorderStyle;
        elements[row - 1][col - 1].style.border = selectedBorderStyle;
        currentRow = row;
        currentCol = col;
    };

    /* Constructor section */
    var domParent = appendTo;
    var construct = function() {
        var insertTable = document.createElement("table");
        var tableHead = document.createElement("thead");
        var tableBody = document.createElement("tbody");
        var headerRow = document.createElement("tr");
        tableHead.appendChild(headerRow);
        insertTable.appendChild(tableHead);
        insertTable.appendChild(tableBody);
        insertTable.style.border = "1px solid";

        for(var i = 1; i < (cols + 1); i++)
        {
            var row = document.createElement("th");
            row.textContent = "Header " + i.toString(10);
            row.style.border = "1px solid";
            tableHead.appendChild(row);
        }

        for(var i = 1; i < (rows + 1); i++)
        {
            var row = document.createElement("tr");
            var rowElems = [];
            for(var j = 1; j < (cols + 1); j++)
            {
                var cell = document.createElement("td");
                cell.textContent = j + ", " + i;
                cell.style.border = "1px solid";
                row.appendChild(cell);
                rowElems.push(cell);
            }
            tableBody.appendChild(row);
            elements.push(rowElems);
        }
        domParent.appendChild(insertTable);
        select(1, 1);
        //initSelect.style.border = "3px solid";
    }();

    /* Public Interface */
    this.Move = function(direction) {
        switch(direction) {
            case "up":
                select(currentRow - 1, currentCol);
                break;
            case "down":
                select(currentRow + 1, currentCol);
                break;
            case "left":
                select(currentRow, currentCol - 1);
                break;
            case "right":
                select(currentRow, currentCol + 1);
                break;
        }

    };

    this.MarkCurrent = function() {
        elements[currentRow - 1][currentCol - 1].style.background = "yellow";
    }
};

var table = new Table(dom, 3, 4);
appendButton("up", dom, function() {table.Move("up") });
appendButton("down", dom, function() {table.Move("down")});
appendButton("left", dom, function() {table.Move("left")});
appendButton("right", dom, function() {table.Move("right")});
appendButton("Mark Cell", dom, table.MarkCurrent);