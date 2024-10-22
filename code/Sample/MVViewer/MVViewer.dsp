# Microsoft Developer Studio Project File - Name="MVViewer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MVViewer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MVViewer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MVViewer.mak" CFG="MVViewer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MVViewer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MVViewer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MVViewer - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 shlwapi.lib /nologo /subsystem:windows /machine:I386 /out:"../../Bin/cn/MVViewer.exe"

!ELSEIF  "$(CFG)" == "MVViewer - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 shlwapi.lib strmbase.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\Bin\MVViewer.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MVViewer - Win32 Release"
# Name "MVViewer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AdjustDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGamma.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrorBox.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MVViewer.cpp
# End Source File
# Begin Source File

SOURCE=.\MVViewer.rc
# End Source File
# Begin Source File

SOURCE=.\MVViewerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\MVViewerView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WBDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AdjustDlg.h
# End Source File
# Begin Source File

SOURCE=.\DlgGamma.h
# End Source File
# Begin Source File

SOURCE=.\ErrorBox.h
# End Source File
# Begin Source File

SOURCE=..\..\Inc\HVDAILT.h
# End Source File
# Begin Source File

SOURCE=..\..\Inc\HVUtil.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MVViewer.h
# End Source File
# Begin Source File

SOURCE=.\MVViewerDoc.h
# End Source File
# Begin Source File

SOURCE=.\MVViewerView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WBDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\MVViewer.ico
# End Source File
# Begin Source File

SOURCE=.\res\MVViewer.rc2
# End Source File
# Begin Source File

SOURCE=.\res\MVViewerDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=..\..\Lib\HVDAILT.LIB
# End Source File
# Begin Source File

SOURCE=..\..\Lib\HVUtil.lib
# End Source File
# Begin Source File

SOURCE=..\..\Lib\Raw2Rgb.lib
# End Source File
# End Target
# End Project
# Section MVViewer : {65220DC3-39FA-460A-9868-34ED34A882F8}
# 	1:14:IDD_DLG_ADJUST:104
# 	2:16:Resource Include:resource.h
# 	2:14:IDD_DLG_ADJUST:IDD_DLG_ADJUST
# 	2:11:AdjustDlg.h:AdjustDlg.h
# 	2:17:CLASS: CAdjustDlg:CAdjustDlg
# 	2:10:ENUM: enum:enum
# 	2:13:AdjustDlg.cpp:AdjustDlg.cpp
# 	2:19:Application Include:MVViewer.h
# End Section
# Section MVViewer : {A13A9FD8-9AB2-4D69-8068-71B5C030E891}
# 	1:13:IDD_DLG_DELAY:103
# 	2:16:Resource Include:resource.h
# 	2:10:DelayDlg.h:DelayDlg.h
# 	2:12:DelayDlg.cpp:DelayDlg.cpp
# 	2:10:ENUM: enum:enum
# 	2:16:CLASS: CDelayDlg:CDelayDlg
# 	2:19:Application Include:MVViewer.h
# 	2:13:IDD_DLG_DELAY:IDD_DLG_DELAY
# End Section
# Section MVViewer : {E2F5541B-F250-4864-8CE7-D817167A0F4D}
# 	1:14:IDD_DLG_ADJUST:104
# 	2:16:Resource Include:resource.h
# 	2:14:IDD_DLG_ADJUST:IDD_DLG_ADJUST
# 	2:10:ENUM: enum:enum
# 	2:17:CLASS: CAdjustDlg:CAdjustDlg
# 	2:11:AdjustDlg.h:AdjustDlg.h
# 	2:13:AdjustDlg.cpp:AdjustDlg.cpp
# 	2:19:Application Include:MVViewer.h
# End Section
# Section MVViewer : {85710223-44BD-4395-9CFB-DAA7712D772D}
# 	1:12:IDD_ERRORBOX:105
# 	2:16:Resource Include:resource.h
# 	2:10:ENUM: enum:enum
# 	2:12:ErrorBox.cpp:ErrorBox.cpp
# 	2:10:ErrorBox.h:ErrorBox.h
# 	2:12:IDD_ERRORBOX:IDD_ERRORBOX
# 	2:19:Application Include:MVViewer.h
# 	2:16:CLASS: CErrorBox:CErrorBox
# End Section
# Section MVViewer : {8AC33B15-5F6A-47B3-ACC6-FD1A8B631A84}
# 	1:16:IDD_DLG_ALLOCATE:102
# 	2:16:Resource Include:resource.h
# 	2:13:AllocateDlg.h:AllocateDlg.h
# 	2:19:CLASS: CAllocateDlg:CAllocateDlg
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:MVViewer.h
# 	2:15:AllocateDlg.cpp:AllocateDlg.cpp
# 	2:16:IDD_DLG_ALLOCATE:IDD_DLG_ALLOCATE
# End Section
# Section MVViewer : {DF941A9F-FBA2-42A7-B100-51C18202A22B}
# 	1:22:IDD_DIALOG_VIDEOCONFIG:104
# 	2:16:Resource Include:resource.h
# 	2:18:DlgVideoConfig.cpp:DlgVideoConfig.cpp
# 	2:10:ENUM: enum:enum
# 	2:22:CLASS: CDlgVideoConfig:CDlgVideoConfig
# 	2:22:IDD_DIALOG_VIDEOCONFIG:IDD_DIALOG_VIDEOCONFIG
# 	2:19:Application Include:MVViewer.h
# 	2:16:DlgVideoConfig.h:DlgVideoConfig.h
# End Section
