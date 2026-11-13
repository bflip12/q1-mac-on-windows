#Requires AutoHotkey v2.0
; One-time: make mac-keys.ahk work in admin windows, for every user.
; Preferred: start it with AutoHotkey's "UI Access" build (no elevation needed).
; Fallback: a scheduled task that starts it with highest privileges at any user's logon.

if !A_IsAdmin {
    try Run '*RunAs "' A_AhkPath '" "' A_ScriptFullPath '"'
    ExitApp
}

logFile := A_ScriptDir "\admin-support-log.txt"
try FileDelete logFile
L(msg) => FileAppend(FormatTime(, "HH:mm:ss") "  " msg "`n", logFile)

script := "C:\Users\Public\Scripts\mac-keys.ahk"
lnk := A_StartupCommon "\mac-keys.lnk"
SplitPath A_AhkPath, , &ahkDir
uia := ahkDir "\AutoHotkey64_UIA.exe"
L("AutoHotkey: " A_AhkPath)

if FileExist(uia) {
    FileCreateShortcut uia, lnk, , '"' script '"'
    L("UI Access build found; startup shortcut now uses " uia)
    try RunWait 'schtasks /delete /tn "MacKeys" /f', , "Hide"
    launch := '"' uia '" "' script '"'
} else {
    L("UI Access build not found; using scheduled task instead")
    xml := A_Temp "\mackeys-task.xml"
    try FileDelete xml
    FileAppend '
    (
<?xml version="1.0" encoding="UTF-16"?>
<Task version="1.2" xmlns="http://schemas.microsoft.com/windows/2004/02/mit/task">
  <Triggers><LogonTrigger><Enabled>true</Enabled></LogonTrigger></Triggers>
  <Principals><Principal id="Author"><GroupId>S-1-5-32-545</GroupId><RunLevel>HighestAvailable</RunLevel></Principal></Principals>
  <Settings>
    <MultipleInstancesPolicy>Parallel</MultipleInstancesPolicy>
    <DisallowStartIfOnBatteries>false</DisallowStartIfOnBatteries>
    <StopIfGoingOnBatteries>false</StopIfGoingOnBatteries>
    <ExecutionTimeLimit>PT0S</ExecutionTimeLimit>
    <Priority>5</Priority>
  </Settings>
  <Actions Context="Author"><Exec><Command>AHKPATH</Command><Arguments>"SCRIPTPATH"</Arguments></Exec></Actions>
</Task>
    )', xml, "UTF-16"
    txt := StrReplace(StrReplace(FileRead(xml, "UTF-16"), "AHKPATH", A_AhkPath), "SCRIPTPATH", script)
    FileDelete xml
    FileAppend txt, xml, "UTF-16"
    rc := RunWait('schtasks /create /tn "MacKeys" /xml "' xml '" /f', , "Hide")
    L("Scheduled task create exit code " rc " (0 = OK)")
    if rc = 0 && FileExist(lnk) {
        FileDelete lnk
        L("Removed all-users startup shortcut (task replaces it)")
    }
    launch := '"' A_AhkPath '" "' script '"'
}

; Restart the running copy with the new rights
Run launch
L("Restarted mac-keys.ahk")
L("DONE")
MsgBox "Admin support set up. Details in admin-support-log.txt", "Mac keys", "Iconi T10"
