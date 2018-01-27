import pandas as pd
from sys import argv
import pyperclip

script,xlsFile,numCols = argv

def getColWidths(table):
    colMax = []
    for cols in table:
        lengths = []
        for entry in table[cols]:
            lengths.append(len(entry))
        colMax.append(max(lengths) if max(lengths)>len(cols) else len(cols) )
    return colMax

def printDivider(colWidths,emptyVec=[],doubleDash = False):
    dash = "=" if doubleDash else "-"
    index = 0
    dividerString = ""
    for width in colWidths:
        insert = dash
        if emptyVec:
            if emptyVec[index]:
                insert = " "
        dividerString += "{0}{1}".format("+",(width+2)*insert)
        index += 1
    dividerString += "+\n"
    return dividerString

def printContents(table,colWidths,isHeader=False):
    contentString  = "| "
    index = 0
    blankCols = []
    for cols in table:
        content =  cols if isHeader else table.loc[row,cols]
        if index == 0 and isHeader==False: #removes .0 if read in as number
            # content = content[:-2]
            print((content))

        if content=="":
            blankCols.append(True)
        else:
            blankCols.append(False)
            flag3 =1
        fill = colWidths[index]-len(content)
        contentString += "{0}{1}{2}".format(content,(fill)*" "," | ")
        index +=1
    contentString += "\n"
    return contentString,blankCols


table = pd.read_excel(xlsFile,usecols=int(numCols)-1).fillna("").astype(str) #read in table from excel file
widths = getColWidths(table) # get the maximum content width of each column

#print header
outputString = printDivider(widths) #first divider
outputString += printContents(table,widths,isHeader=True)[0] #header
outputString += printDivider(widths,doubleDash=True) #header divider

#print table contents
for row in range(len(table)):
    valString,blanks = printContents(table,widths)
    outputString += printDivider(widths,blanks)*(row != 0) + valString
outputString += printDivider(widths) #final divider

#copy string to clipboard
pyperclip.copy(outputString)
print ("Table copied to clipboard!")
