#Requires AutoHotkey v2.0
#SingleInstance Force

; Mac-style shortcuts for a Keychron Q1 V2 with the side switch set to WIN.
; Physical keys in Win mode:  cmd key = Alt,  option key = Win,  control = Ctrl
; The shortcuts are disabled while World of Warcraft is focused (see the end for the few that stay on).

GroupAdd "Games", "ahk_exe Wow.exe"
GroupAdd "Games", "ahk_exe WowClassic.exe"
NotGame(*) => !WinActive("ahk_group Games")
SendKeys(keys, *) => Send(keys)

; cmd + key  ->  Ctrl + key
HotIf NotGame
for k in StrSplit("abcdefgijklnoprstuvwxyz0123456789=-,./") {
    Hotkey "!" k, SendKeys.Bind("^" k)
    Hotkey "!+" k, SendKeys.Bind("^+" k)
}
Hotkey "!+z", SendKeys.Bind("^y")     ; redo
Hotkey "!+3", SendKeys.Bind("#+s")    ; screenshot
Hotkey "!+4", SendKeys.Bind("#+s")    ; screenshot (area)
HotIf

; ---------------------------------------------------------------------------
; Auto Fn lock: turn the keyboard's Fn lock on while a game has focus, off when you leave.
; Needs the custom Q1 firmware (VIA custom value channel 0, id 8). Toggle from the tray menu.
; If you unlock it yourself in-game it stays off until the game is focused again.
; ---------------------------------------------------------------------------
global AutoFnLock := true
global GameWasActive := false

A_TrayMenu.Add()
A_TrayMenu.Add("Auto Fn lock in games", ToggleAutoFnLock)
A_TrayMenu.Check("Auto Fn lock in games")
SetTimer WatchGameFocus, 300

ToggleAutoFnLock(*) {
    global AutoFnLock
    AutoFnLock := !AutoFnLock
    A_TrayMenu.ToggleCheck("Auto Fn lock in games")
}

WatchGameFocus() {
    global AutoFnLock, GameWasActive
    active := WinActive("ahk_group Games") ? true : false
    if (active = GameWasActive)
        return
    GameWasActive := active
    if AutoFnLock
        SetKeyboardFnLock(active)
}

; Sends VIA "custom set value" [0x07, channel 0, id 8, on/off] to the keyboard's raw HID
; interface (usage page 0xFF60) on VID 3434 / PID 0107. Returns true if it was sent.
SetKeyboardFnLock(on) {
    guid := Buffer(16)
    DllCall("hid\HidD_GetHidGuid", "Ptr", guid)
    devs := DllCall("setupapi\SetupDiGetClassDevsW", "Ptr", guid, "Ptr", 0, "Ptr", 0, "UInt", 0x12, "Ptr") ; PRESENT|DEVICEINTERFACE
    if (devs = -1)
        return false
    ifd := Buffer(A_PtrSize = 8 ? 32 : 28, 0)
    NumPut("UInt", ifd.Size, ifd)
    sent := false, idx := 0
    while !sent && DllCall("setupapi\SetupDiEnumDeviceInterfaces", "Ptr", devs, "Ptr", 0, "Ptr", guid, "UInt", idx++, "Ptr", ifd) {
        need := 0
        DllCall("setupapi\SetupDiGetDeviceInterfaceDetailW", "Ptr", devs, "Ptr", ifd, "Ptr", 0, "UInt", 0, "UInt*", &need, "Ptr", 0)
        if (need = 0)
            continue
        det := Buffer(need, 0)
        NumPut("UInt", A_PtrSize = 8 ? 8 : 6, det)
        if !DllCall("setupapi\SetupDiGetDeviceInterfaceDetailW", "Ptr", devs, "Ptr", ifd, "Ptr", det, "UInt", need, "Ptr", 0, "Ptr", 0)
            continue
        path := StrGet(det.Ptr + 4, "UTF-16")
        if !InStr(path, "vid_3434&pid_0107")
            continue
        h := DllCall("CreateFileW", "Str", path, "UInt", 0xC0000000, "UInt", 3, "Ptr", 0, "UInt", 3, "UInt", 0, "Ptr", 0, "Ptr")
        if (h = -1)
            continue
        pp := 0
        if DllCall("hid\HidD_GetPreparsedData", "Ptr", h, "Ptr*", &pp) {
            caps := Buffer(64, 0)
            DllCall("hid\HidP_GetCaps", "Ptr", pp, "Ptr", caps)
            page := NumGet(caps, 2, "UShort"), outLen := NumGet(caps, 6, "UShort")
            DllCall("hid\HidD_FreePreparsedData", "Ptr", pp)
            if (page = 0xFF60 && outLen >= 5) {
                rep := Buffer(outLen, 0)              ; byte 0 = report id 0
                NumPut("UChar", 0x07, rep, 1)          ; id_custom_set_value
                NumPut("UChar", 0x00, rep, 2)          ; channel 0
                NumPut("UChar", 0x08, rep, 3)          ; value id 8 = Fn lock
                NumPut("UChar", on ? 1 : 0, rep, 4)
                written := 0
                sent := DllCall("WriteFile", "Ptr", h, "Ptr", rep, "UInt", outLen, "UInt*", &written, "Ptr", 0) && written = outLen
            }
        }
        DllCall("CloseHandle", "Ptr", h)
    }
    DllCall("setupapi\SetupDiDestroyDeviceInfoList", "Ptr", devs)
    return sent
}

#HotIf NotGame()

!q::Send "!{F4}"
!h::WinMinimize "A"
!m::WinMinimize "A"

!Left::Send "{Home}"
!Right::Send "{End}"
!Up::Send "^{Home}"
!Down::Send "^{End}"
!+Left::Send "+{Home}"
!+Right::Send "+{End}"
!+Up::Send "^+{Home}"
!+Down::Send "^+{End}"
!Backspace:: {
    Send "+{Home}"
    Sleep 40          ; let apps like Claude apply the selection first
    Send "{Backspace}"
}

#Left::Send "^{Left}"
#Right::Send "^{Right}"
#+Left::Send "^+{Left}"
#+Right::Send "^+{Right}"
#Backspace::Send "^{Backspace}"

^#Left::Send "#{Left}"
^#Right::Send "#{Right}"
^#Up::Send "#{Up}"
^#Down::Send "#{Down}"

!+[::Send "^+{Tab}"
!+]::Send "^{Tab}"
![::Send "!{Left}"
!]::Send "!{Right}"

; cmd+Space -> PowerToys Command Palette on its default shortcut (Win+Alt+Space), so it works for
; every user without changing Command Palette's settings
$!Space::Send "#!{Space}"

; cmd+click -> Ctrl+click (new background tab in Chrome/Edge, multi-select in Explorer);
; cmd+shift+click -> Ctrl+Shift+click (new foreground tab). Plain Alt+click in Chrome downloads the link.
!LButton::Send "^{Click}"
!+LButton::Send "^+{Click}"

#HotIf

; Everywhere, WoW included: tapping Option (Win) or cmd (Alt) alone does nothing
~LWin::Send "{Blind}{vkE8}"
~RWin::Send "{Blind}{vkE8}"
~LAlt::Send "{Blind}{vkE8}"
~RAlt::Send "{Blind}{vkE8}"

; In WoW only: stop cmd+Space (Alt+Space) from opening the PowerToys launcher over the game
#HotIf WinActive("ahk_group Games")
$!Space::return   ; $ = use the keyboard hook so it wins over PowerToys' own hotkey#HotIf
