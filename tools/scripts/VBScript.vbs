Dim fileSystemObject
Const ForReading = 1
Const ForWriting = 2
Const ForAppending = 8


Function Main(args)
    If args.Count > 0 Then
        Set fileSystemObject = CreateObject("Scripting.FileSystemObject")

        Select Case args.Item(0)
            Case "FixCocosProject"
                Call FixCocosProject()
            Case "Unzip"
                Call Unzip(args.Item(1), args.Item(2))
            Case "MsgBox"
                MsgBox args.Item(1), args.Item(2), args.Item(3)
            Case "PlaySound"
                Call PlaySound(args.Item(1))
        End Select
    End If
    
    Set fileSystemObject = Nothing
    Main = 0
End Function

Sub FixCocosProject()
    Set objRegEx = New RegExp
    objRegEx.Global = True
    objRegEx.Pattern = "\Dpath\D\s*: \D*(.*?),"

    jsonFile = fileSystemObject.GetAbsolutePathName("../../creator_project/settings/creator-luacpp-support.json")
    jsonText = ReadText(jsonFile)
   
    pathValue = Replace(fileSystemObject.GetAbsolutePathName("../.."), "\", "\\")
    pathFormat = "'path' : '{0}',"
    pathFormat = replace(pathFormat, "{0}", pathValue)
    pathFormat = replace(pathFormat, "'", """")
    
    'Check Project Path
    If Not InStr(jsonText, pathValue) > 0 Then
        strNewString = objRegEx.Replace(jsonText, pathFormat)
        Call WriteFile(jsonFile, strNewString)
        MsgBox "Project Path was changed to: " & pathValue, vbInformation, "Path Fixed"
    End If
End Sub


Sub PlaySound(filename)
    If fileSystemObject.FileExists(filename) Then
        Set oPlayer = CreateObject("WMPlayer.OCX")
        oPlayer.URL = filename
        oPlayer.controls.play

        While oPlayer.playState <> 1 ' 1 = Stopped
            WScript.Sleep 100
        Wend

        oPlayer.close
    End If
End Sub


Sub ReplaceIn(filename, oldstr, newstr)
    Set objFile = fileSystemObject.OpenTextFile(filename, ForReading)
    
    strText = objFile.ReadAll
    objFile.Close
    strNewText = Replace(strText, oldstr, newstr)
    
    Set objFile = fileSystemObject.OpenTextFile(filename, ForWriting)
    objFile.Write strNewText
    objFile.Close
End Sub


Sub DeleteAFolder(filespec)
    If fileSystemObject.FolderExists(filespec) Then
        fileSystemObject.DeleteFolder(filespec)
    End If
End Sub


Sub Run(filename, args, asAdministrator)
    Set application = CreateObject("Shell.Application")
    If asAdministrator Then
        application.ShellExecute filename, args 
    Else
        application.ShellExecute filename, args, "workdir", "runas", 1  
    End If
    
    Set application = Nothing
End Sub


Function ReadText(filename)
    Set objFile = fileSystemObject.OpenTextFile(filename, ForReading)
    text = objFile.ReadAll
    objFile.Close
    ReadText = text
End Function


Sub WriteFile(filename, strNewText)
    Set objFile = fileSystemObject.OpenTextFile(filename, ForWriting)
    objFile.Write strNewText
    objFile.Close
End Sub


Function echo(txt)
    Set stdout = fileSystemObject.GetStandardStream(1)
    stdout.WriteLine txt
End Function


Function Unzip(ZipFile, ExtractTo)
    If  Not fileSystemObject.FolderExists(ExtractTo) Then
        fileSystemObject.CreateFolder(ExtractTo)
    End If
    
    'Extract the contants of the zip file.
    Set objShell = CreateObject("Shell.Application")
    Set FilesInZip = objShell.NameSpace(ZipFile).items
    objShell.NameSpace(ExtractTo).CopyHere(FilesInZip)
    Set objShell = Nothing
End Function


WScript.Quit(Main(WScript.Arguments))