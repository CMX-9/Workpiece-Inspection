; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHVSnapContinuousView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "hvsnapcontinuous.h"
LastPage=0

ClassCount=6
Class1=CErrorBox
Class2=CHVSnapContinuousApp
Class3=CAboutDlg
Class4=CHVSnapContinuousDoc
Class5=CHVSnapContinuousView
Class6=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME (English (U.S.))
Resource2=IDD_ABOUTBOX (English (U.S.))
Resource3=IDD_ERRORBOX (English (U.S.))

[CLS:CErrorBox]
Type=0
BaseClass=CDialog
HeaderFile=ErrorBox.h
ImplementationFile=ErrorBox.cpp

[CLS:CHVSnapContinuousApp]
Type=0
BaseClass=CWinApp
HeaderFile=HVSnapContinuous.h
ImplementationFile=HVSnapContinuous.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=HVSnapContinuous.cpp
ImplementationFile=HVSnapContinuous.cpp
LastObject=CAboutDlg

[CLS:CHVSnapContinuousDoc]
Type=0
BaseClass=CDocument
HeaderFile=HVSnapContinuousDOC.h
ImplementationFile=HVSnapContinuousDOC.cpp
LastObject=CHVSnapContinuousDoc

[CLS:CHVSnapContinuousView]
Type=0
BaseClass=CView
HeaderFile=HVSnapContinuousVIEW.h
ImplementationFile=HVSnapContinuousVIEW.cpp
LastObject=CHVSnapContinuousView
Filter=C
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
LastObject=CMainFrame
Filter=T
VirtualFilter=fWC

[DLG:IDD_ERRORBOX]
Type=1
Class=CErrorBox

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CHVSnapContinuousView
Command1=ID_SNAP_OPEN
Command2=ID_SNAP_START
Command3=ID_SNAP_STOP
Command4=ID_SNAP_CLOSE
Command5=ID_MENUITEM32775
CommandCount=5

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ERRORBOX (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_ERROR,static,1342312961

