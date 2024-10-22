; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMVViewerView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MVViewer.h"
LastPage=0

ClassCount=11
Class1=CAdjustDlg
Class2=CDelayDlg
Class3=CMVViewerApp
Class4=CAboutDlg
Class5=CMVViewerDoc
Class6=CMVViewerView
Class7=CMainFrame
Class8=CWBDlg

ResourceCount=7
Resource1=IDD_DLG_ADJUST
Resource2=IDD_ERRORBOX
Resource3=IDD_ABOUTBOX (English (U.S.))
Resource4=IDD_DIALOG_VIDEOCONFIG
Class9=CDlgVideoConfig
Resource5=IDD_DLG_GAMMA
Class10=CDlgGamma
Resource6=IDD_DLG_WB
Class11=CErrorBox
Resource7=IDR_MAINFRAME (English (U.S.))

[CLS:CAdjustDlg]
Type=0
BaseClass=CDialog
HeaderFile=AdjustDlg.h
ImplementationFile=AdjustDlg.cpp
LastObject=IDC_CM_EXPOSUREMODE
Filter=D
VirtualFilter=dWC

[CLS:CDelayDlg]
Type=0
BaseClass=CDialog
HeaderFile=DelayDlg.h
ImplementationFile=DelayDlg.cpp

[CLS:CMVViewerApp]
Type=0
BaseClass=CWinApp
HeaderFile=MVViewer.h
ImplementationFile=MVViewer.cpp
Filter=N
VirtualFilter=AC
LastObject=CMVViewerApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=MVViewer.cpp
ImplementationFile=MVViewer.cpp
LastObject=ID_VIEW_CONTINUATION

[CLS:CMVViewerDoc]
Type=0
BaseClass=CDocument
HeaderFile=MVViewerDOC.h
ImplementationFile=MVViewerDOC.cpp

[CLS:CMVViewerView]
Type=0
BaseClass=CView
HeaderFile=MVViewerVIEW.h
ImplementationFile=MVViewerVIEW.cpp
Filter=C
VirtualFilter=VWC
LastObject=IDRecognize

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=IDRecognize

[CLS:CWBDlg]
Type=0
BaseClass=CDialog
HeaderFile=WBDlg.h
ImplementationFile=WBDlg.cpp
LastObject=ID_WB_SET
Filter=D
VirtualFilter=dWC

[DLG:IDD_DLG_ADJUST]
Type=1
Class=CAdjustDlg
ControlCount=24
Control1=IDC_CM_ADC,combobox,1344339970
Control2=IDC_CM_GAIN,combobox,1344339970
Control3=IDC_SB_GAIN,scrollbar,1342242816
Control4=IDOK,button,1342242816
Control5=IDCANCEL,button,1342242816
Control6=ID_ADJUST_RESET,button,1342242816
Control7=ID_ADJUST_DEFAULT,button,1342242816
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342308866
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,button,1342177287
Control12=IDC_TEXT_GAIN,static,1342312961
Control13=IDC_STATIC,static,1342308866
Control14=IDC_EDIT_TINT_UPPER,edit,1350631552
Control15=IDC_EDIT_TINT_LOWER,edit,1350631552
Control16=IDC_STATIC,static,1342308353
Control17=IDC_STATIC,button,1342177287
Control18=IDC_SB_HBLANKING,scrollbar,1342242816
Control19=IDC_EDIT_HBLANKING,edit,1350631552
Control20=IDC_STATIC,button,1342177287
Control21=IDC_SB_VBLANKING,scrollbar,1342242816
Control22=IDC_EDIT_VBLANKING,edit,1350631552
Control23=IDC_CM_EXPOSUREMODE,combobox,1344339970
Control24=IDC_STATIC,static,1342308866

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_DLG_WB]
Type=1
Class=CWBDlg
ControlCount=11
Control1=IDC_EDIT_RED_RATIO,edit,1350631552
Control2=IDC_EDIT_GREEN_RATIO,edit,1350633600
Control3=IDC_EDIT_BLUE_RATIO,edit,1350631552
Control4=IDOK,button,1342242816
Control5=IDCANCEL,button,1342242816
Control6=ID_WB_RATIO,button,1342242816
Control7=IDC_STATIC,static,1342308866
Control8=IDC_STATIC,static,1342308866
Control9=IDC_STATIC,static,1342308866
Control10=IDC_STATIC,button,1342177287
Control11=ID_WB_SET,button,1342242816

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN_ONE
Command2=ID_FILE_SAVE_AS_ONE
Command3=ID_FILE_PRINT
Command4=ID_FILE_PRINT_PREVIEW
Command5=ID_FILE_PRINT_SETUP
Command6=ID_APP_EXIT
Command7=ID_VIEW_MODE0
Command8=ID_VIEW_MODE1
Command9=ID_VIEW_MODE2
Command10=ID_VIEW_COLOR
Command11=ID_VIEW_BW
Command12=ID_SNPASPEED_HIGH
Command13=ID_SNAPSPEED_NORMAL
Command14=ID_VIEW_CONVERSION_GB
Command15=ID_VIEW_CONVERSION_GR
Command16=ID_VIEW_CONVERSION_BG
Command17=ID_VIEW_CONVERSION_RG
Command18=ID_CONVERSION_FAST
Command19=ID_CONVERSION_NORMAL
Command20=ID_CONVERSION_BEST
Command21=ID_VIEW_ADJUST
Command22=ID_VIEW_WB
Command23=ID_VIEW_CONTINUATION
Command24=ID_VIEW_TRIGGER
Command25=ID_VIEW_SNAPSHOT
Command26=ID_VIEW_SNAP
Command27=ID_GAMMA_CORRECT
Command28=ID_CANCEL_GAMMA
Command29=ID_GET_BAD_PIEXES
Command30=ID_ELIMINATE_BAD_PIXELS
Command31=ID_GET_TEMPLATE
Command32=ID_TEMPLATE_CORRECT
Command33=ID_HELP_WEBSITE
Command34=ID_HELP_MAILTO
Command35=ID_APP_ABOUT
Command36=IDRecognize
CommandCount=36

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,button,1342177287

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_VIEW_SNAPSHOT
Command2=ID_VIEW_SNAP
Command3=ID_EDIT_COPY
Command4=ID_FILE_NEW
Command5=ID_FILE_OPEN
Command6=ID_FILE_PRINT
Command7=ID_FILE_SAVE
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_NEXT_PANE
Command12=ID_PREV_PANE
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_CUT
Command16=ID_EDIT_UNDO
CommandCount=16

[DLG:IDD_DIALOG_VIDEOCONFIG]
Type=1
Class=CDlgVideoConfig
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDC_COMBO_COMFILTER,combobox,1344340226
Control3=65535,static,1342308352
Control4=65535,static,1342308352
Control5=IDC_SPIN_FRAMERATE,msctls_updown32,1342177378
Control6=IDC_EDIT_FRAMERATE,edit,1350631424
Control7=IDCANCEL,button,1342242816
Control8=65535,static,1342308352
Control9=65535,button,1342177287
Control10=65535,button,1342177287

[CLS:CDlgVideoConfig]
Type=0
HeaderFile=DlgVideoConfig.h
ImplementationFile=DlgVideoConfig.cpp
BaseClass=CDialog

[DLG:IDD_DLG_GAMMA]
Type=1
Class=CDlgGamma
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_GAMMA_RATIO,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:CDlgGamma]
Type=0
HeaderFile=DlgGamma.h
ImplementationFile=DlgGamma.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgGamma

[DLG:IDD_ERRORBOX]
Type=1
Class=CErrorBox
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_ERROR,static,1342312961

[CLS:CErrorBox]
Type=0
HeaderFile=ErrorBox.h
ImplementationFile=ErrorBox.cpp
BaseClass=CDialog

