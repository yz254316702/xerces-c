# Microsoft Developer Studio Project File - Name="IO" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=IO - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "IO.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IO.mak" CFG="IO - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IO - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IO - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IO - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IO_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "..\..\..\..\src" /I "..\..\..\..\swig\perl\Transcoder" /I "..\..\..\..\swig\perl\Handler" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IO_EXPORTS" /D "HAS_BOOL" /D uint16_t="unsigned short" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG"
# ADD RSC /l 0x410 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 perl58.lib /nologo /dll /pdb:"..\..\blib\IO.pdb" /machine:I386 /out:"..\..\blib\IO.dll"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "IO - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IO_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\..\..\src" /I "..\..\..\..\swig\perl\Transcoder" /I "..\..\..\..\swig\perl\Handler" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IO_EXPORTS" /D "HAS_BOOL" /D uint16_t="unsigned short" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "_DEBUG"
# ADD RSC /l 0x410 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 perl58.lib /nologo /dll /pdb:"..\..\blib\IO.pdb" /debug /machine:I386 /out:"..\..\blib\IO.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "IO - Win32 Release"
# Name "IO - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\..\swig\perl\Handler\PerlCallbackHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\swig\perl\Handler\PerlDOMCallbackHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\swig\perl\Handler\PerlEntityResolverHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\swig\perl\Handler\PerlErrorCallbackHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\swig\perl\Handler\PerlNodeFilterCallbackHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\swig\perl\Handler\PerlSAXCallbackHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\swig\perl\Transcoder\Transcoder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\swig\perl\IO\Xerces_IO.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\swig\perl\Transcoder\XMLExceptionHandler.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\..\swig\perl\Handler\PerlCallbackHandler.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\swig\perl\Handler\PerlCallbackHandler.swig.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\swig\perl\Handler\PerlDOMCallbackHandler.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\swig\perl\Handler\PerlEntityResolverHandler.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\swig\perl\Handler\PerlErrorCallbackHandler.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\swig\perl\Handler\PerlNodeFilterCallbackHandler.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\swig\perl\Handler\PerlSAXCallbackHandler.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\swig\perl\Transcoder\Transcoder.hpp
# End Source File
# Begin Source File

SOURCE="..\..\..\..\swig\perl\xerces-swig-perl.hpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\..\swig\perl\Transcoder\XMLExceptionHandler.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project