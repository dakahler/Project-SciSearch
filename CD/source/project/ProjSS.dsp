# Microsoft Developer Studio Project File - Name="ProjSS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=ProjSS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ProjSS.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ProjSS.mak" CFG="ProjSS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ProjSS - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "ProjSS - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "ProjSS - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f ProjSS.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "ProjSS.exe"
# PROP BASE Bsc_Name "ProjSS.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "nmake /f "ProjSS.mak""
# PROP Rebuild_Opt "/a"
# PROP Target_File "ProjSS.bin"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "ProjSS - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f ProjSS.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "ProjSS.exe"
# PROP BASE Bsc_Name "ProjSS.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "nmake /f "ProjSS.mak""
# PROP Rebuild_Opt "/a"
# PROP Target_File "ProjSS.bin"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "ProjSS - Win32 Release"
# Name "ProjSS - Win32 Debug"

!IF  "$(CFG)" == "ProjSS - Win32 Release"

!ELSEIF  "$(CFG)" == "ProjSS - Win32 Debug"

!ENDIF 

# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\obsolete.cpp
# End Source File
# Begin Source File

SOURCE=.\PSSDisplay.cpp
# End Source File
# Begin Source File

SOURCE=.\PSSInit.cpp
# End Source File
# Begin Source File

SOURCE=.\PSSInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\PSSOAM_alloc.cpp
# End Source File
# Begin Source File

SOURCE=.\PSSSimulation.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\dispcnt.h
# End Source File
# Begin Source File

SOURCE=.\extern.h
# End Source File
# Begin Source File

SOURCE=.\gba.h
# End Source File
# Begin Source File

SOURCE=.\gbavars.h
# End Source File
# Begin Source File

SOURCE=.\imagedata.h
# End Source File
# Begin Source File

SOURCE=.\keypad.h
# End Source File
# Begin Source File

SOURCE=.\precomp.h
# End Source File
# Begin Source File

SOURCE=.\PSSDisplay.h
# End Source File
# Begin Source File

SOURCE=.\PSSInit.h
# End Source File
# Begin Source File

SOURCE=.\PSSInterface.h
# End Source File
# Begin Source File

SOURCE=.\PSSOAM_alloc.h
# End Source File
# Begin Source File

SOURCE=.\PSSSimulation.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\boot.o
# End Source File
# Begin Source File

SOURCE=.\boot.s
# End Source File
# Begin Source File

SOURCE=.\default.doxygen
# End Source File
# Begin Source File

SOURCE=.\ProjSS.mak
# End Source File
# Begin Source File

SOURCE=.\vblank.s
# End Source File
# End Target
# End Project
