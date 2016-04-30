#include <ButtonConstants.au3>
#include <EditConstants.au3>
#include <GUIConstantsEx.au3>
#include <StaticConstants.au3>
#include <WindowsConstants.au3>
#include <File.au3>
#include <GuiEdit.au3>
#include <Array.au3>

$var = FileOpenDialog("Choisissez un fichier dialogue", @WindowsDir & "", "Dialogue (*.dial)", 1)

 If @error Then
    MsgBox(4096, "", "Aucun fichier choisi")
Else
    $var = StringReplace($var, "|", @CRLF)
EndIf
Global $ID=InputBox("","Script ID")
#Region ### START Koda GUI section ###  Form=
Global $Form1_1 = GUICreate("autoText", 554, 217, 414, 401)
GUISetFont(16, 400, 0, "Arial")
Global $Edit1 = GUICtrlCreateEdit("", 16, 32, 337, 145)
GUICtrlSetData(-1, "")
Global $Button1 = GUICtrlCreateButton("Insérer", 392, 72, 115, 49)
Global $Label1 = GUICtrlCreateLabel("Nombre de caractères: 0", 16, 4, 422, 28)
GUISetState(@SW_SHOW)
#EndRegion ### END Koda GUI section ###

While 1
 $nMsg = GUIGetMsg()
 GUICtrlSetData($Label1,"Nombre de caractères: "&_howMany($Edit1))
 if(_howMany($Edit1)<>0 and _howMany($Edit1)>=46 ) Then
	GUICtrlSetData($Edit1,GUICtrlRead($Edit1)&@CRLF)
 EndIf

 Switch $nMsg
	Case $GUI_EVENT_CLOSE


   Exit

	case $Button1
		$ret=StringReplace(GUICtrlRead($Edit1), @CRLF, "|n")
		_FileWriteToLine($var,$ID+1,$ret)

		Dim $aLines
		_FileReadToArray($var, $aLines)
		_ArrayDelete($aLines,$ID+2)
		FileDelete($var)
		For $i=1 to $aLines[0]-1
			If $aLines[$i]<>"" Then FileWriteLine($var,$aLines[$i])
		Next
		MsgBox(0,"","Texte inseré!")

EndSwitch

WEnd
func _howMany($edit)
	return stringlen(_GUICtrlEdit_GetLine($edit,_GUICtrlEdit_GetLineCount($edit)-1))
EndFunc
