#!/bin/bash
echo "Compiling Html Table Editor"
mv Html_Table_Editor/htmlExampleTable.txt htmlExampleTable.txt
g++ -std=c++14 Html_Table_Editor/Cell.h Html_Table_Editor/Cell.cpp Html_Table_Editor/Commands.h Html_Table_Editor/Commands.cpp Html_Table_Editor/Common.h Html_Table_Editor/CommonDef.cpp Html_Table_Editor/CustomExceptions.h Html_Table_Editor/CustomExceptions.cpp Html_Table_Editor/FileManager.h Html_Table_Editor/FileManager.cpp Html_Table_Editor/Msg.h Html_Table_Editor/Msg.cpp Html_Table_Editor/Row.h Html_Table_Editor/Row.cpp Html_Table_Editor/Table.h Html_Table_Editor/Table.cpp Html_Table_Editor/Main.cpp -o HtmlTableEditor
echo "To run the program use ./HtmlTableEditor"
echo "Remember to create a input file with this name: 'htmlExampleTable.txt' next to the executable!"
