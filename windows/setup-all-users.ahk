#Requires AutoHotkey v2.0
; One-time setup: makes mac-keys.ahk start for every user on this PC.
; Needs admin; Windows will ask for permission.

if !A_IsAdmin {
    try Run '*RunAs "' A_AhkPath '" "' A_ScriptFullPath '"'
    ExitApp
}

logFile := A_ScriptDir "\install-log.txt"
try FileDelete logFile
L(msg) => FileAppend(FormatTime(, "HH:mm:ss") "  " msg "`n", logFile)

dest := "C:\Users\Public\Scripts"
DirCreate dest
FileCopy A_ScriptDir "\mac-keys.ahk", dest "\mac-keys.ahk", 1
L("Copied script to " dest)

FileCreateShortcut dest "\mac-keys.ahk", A_StartupCommon "\mac-keys.lnk"
L("All-users startup shortcut: " (FileExist(A_StartupCommon "\mac-keys.lnk") ? "OK" : "FAILED"))

if FileExist(A_Startup "\mac-keys.lnk") {
    FileDelete A_Startup "\mac-keys.lnk"
    L("Removed per-user startup shortcut")
}

; Stop the per-user copy and start the shared one (non-elevated, via Explorer)
DetectHiddenWindows true
for hwnd in WinGetList("ahk_class AutoHotkey") {
    title := WinGetTitle(hwnd)
    if InStr(title, "mac-keys.ahk") && !InStr(title, "Public")
        WinClose hwnd
}
Sleep 500
Run 'explorer.exe "' dest '\mac-keys.ahk"'
L("Started shared mac-keys.ahk")

L("DONE")
MsgBox "Setup finished. Details in install-log.txt", "Mac keys for everyone", "Iconi T10"
