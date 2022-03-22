from openpyxl import load_workbook
from scipy import spatial
CD=[]
PD=[]
tempWindow=[]
slidingW=[]
window_size=7
past_window_size=14
rowCounter=2
maxRowCounter=0
readings=8
wb=load_workbook('data.xlsx')
ws=wb.active

def printTable(x,S):
    print(S)
    for a in x:
        print(a)

def printWindows(windows):
    print(f'Windows :{len(windows)}')
    for x in range(readings):
        printTable(windows[x],f'Window {x+1}')



def init():
    global PD,CD,rowCounter,tempWindow,slidingW
    for row in ws.iter_rows(min_row=2,min_col=2,max_row=past_window_size+1, max_col=5,  values_only=True):
        PD.append(row)
    for row in ws.iter_rows(min_row=2,min_col=8,max_row=window_size+1, max_col=11,  values_only=True):
        CD.append(row)

    while rowCounter<readings+2:
        for row in ws.iter_rows(min_row=rowCounter,min_col=2,max_row=window_size-1+rowCounter, max_col=5,  values_only=True):
            tempWindow.append(row)
        slidingW.append(tempWindow)
        rowCounter+=1
        tempWindow=[]


#Main Function
init()
printTable(PD,'Past Data')
printTable(CD,'Current Data')
printWindows(slidingW)

Y =spatial.distance.cdist(CD, slidingW[1], 'euclidean')
print("Euclidean Distance :",Y)
