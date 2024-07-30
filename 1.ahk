;本脚本用于创建桌面快捷方式快捷键，选择单个或多个文件或者文件夹均可用快捷键“Alt+D”实现桌面快捷方式的创建。
;本脚本为“达芬奇科普”所写，请勿用于任何商用目的，更多精彩分享大家可以关注“达芬奇科普”。
;使用方法：打开记事本，将此脚本复制后粘贴进去，然后修改后缀名为".ahk"，然后双击运行。选择目标文件（或文件夹），然后;摁快捷键“Alt+D”，即可实现桌面快捷方式的创建。
#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
 #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.
TrayTip:="Alt+D to creat shortcut"
TrayIconFile:=A_WinDir . "\System32\DDORes.dll" ;
TrayIconNum:="-2108" ;
Menu,Tray,Tip,%TrayTip%
Menu,Tray,Icon,%TrayIconFile%,%TrayIconNum%

#IfWinActive ahk_exe explorer.exe
!d::
ControlGetFocus, mycontrol,A
if(mycontrol = "DirectUIHWND3" or mycontrol = "SysListView321"or mycontrol = "DirectUIHWND2" )
{
clipboard =
SendInput, {Control Down}c{Control Up}
ClipWait,0
folder_path_set := []
file_path_set := []
file_name_ex_set := []
folder_name_set :=[]
file_name_set := []
i =1
j =1
Loop, parse, clipboard, `n, `r
{
   FileGetAttrib, Attributes,  %A_LoopField%
if InStr(Attributes, "A")
{
file_path_set.Insert(i, A_LoopField)
file_name_ex_set[i] := RegExReplace(file_path_set[i], "m)^.+\\", "")
file_name_set[i]  := RegExReplace(file_name_ex_set[i], "mU)\.[0-9a-z]+$")
file_path := file_path_set[i]
file_name := file_name_set[i]
FileCreateShortcut, %file_path%, %A_Desktop%\ %file_name%-快捷方式.lnk
i++
}
else if InStr(Attributes, "D")
{
folder_path_set.Insert(j, A_LoopField)
folder_name_set[j] := RegExReplace(folder_path_set[j], "m)^.+\\", "")
folder_path := folder_path_set[j]
folder_name := folder_name_set[j]
FileCreateShortcut, %folder_path%, %A_Desktop%\ %folder_name%-.lnk
j++
}
}
}
