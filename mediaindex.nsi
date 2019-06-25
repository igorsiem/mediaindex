; NSIS installation script for MediaIndex
!include "MUI.nsh"

!define MUI_ABORTWARNING # Warn the user if they exit from the installer.

!insertmacro MUI_PAGE_WELCOME # Welcome to the installer page.
!insertmacro MUI_PAGE_DIRECTORY # In which folder install page.
!insertmacro MUI_PAGE_INSTFILES # Installing page.
!insertmacro MUI_PAGE_FINISH # Finished installation page.

!insertmacro MUI_LANGUAGE "English"

Name "MediaIndex"
OutFile "build\$%QPRJ_PROJECT_NAME%-$%QPRJ_PROJECT_VERSION%.exe"
InstallDir "$PROGRAMFILES\MediaIndex"
ShowInstDetails show

Section "MediaIndex"
    SetOutPath $INSTDIR
    File build\bin\mediaindex-gui.exe
    File build\bin\Qt5Concurrent.dll
    File build\bin\Qt5Core.dll
    File build\bin\Qt5DBus.dll
    File build\bin\Qt5Gui.dll
    File build\bin\Qt5Network.dll
    File build\bin\Qt5OpenGL.dll
    File build\bin\Qt5PrintSupport.dll
    File build\bin\Qt5Sql.dll
    File build\bin\Qt5Test.dll
    File build\bin\Qt5Widgets.dll
    File build\bin\Qt5Xml.dll
    File src\gui\resources\mediaindex.ico

    CreateShortCut "$SMPROGRAMS\MediaIndex.lnk" \
        "$INSTDIR\mediaindex-gui.exe" \
        "" \
        "$INSTDIR\mediaindex.ico "

    WriteRegStr HKLM \
        "Software\Microsoft\Windows\CurrentVersion\Uninstall\MediaIndex" \
        "DisplayName" "MediaIndex"
    WriteRegStr HKLM \
        "Software\Microsoft\Windows\CurrentVersion\Uninstall\MediaIndex" \
        "UninstallString" '"$INSTDIR\uninst.exe"'

    WriteUninstaller "Uninst.exe"


SectionEnd

Section "Uninstall"
    Delete $INSTDIR\Uninst.exe
    Delete $INSTDIR\mediaindex-gui.exe
    Delete $INSTDIR\Qt5Concurrent.dll
    Delete $INSTDIR\Qt5Core.dll
    Delete $INSTDIR\Qt5DBus.dll
    Delete $INSTDIR\Qt5Gui.dll
    Delete $INSTDIR\Qt5Network.dll
    Delete $INSTDIR\Qt5OpenGL.dll
    Delete $INSTDIR\Qt5PrintSupport.dll
    Delete $INSTDIR\Qt5Sql.dll
    Delete $INSTDIR\Qt5Test.dll
    Delete $INSTDIR\Qt5Widgets.dll
    Delete $INSTDIR\Qt5Xml.dll
    Delete $INSTDIR\mediaindex.ico
    RmDir $INSTDIR
    DeleteRegKey HKLM \
        "Software\Microsoft\Windows\CurrentVersion\Uninstall\MediaIndex"
SectionEnd
