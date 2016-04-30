$file=FileOpen("flags.flag",2)
for $i=0 to 4095
	FileWriteLine($file, "0x0"&StringTrimLeft(Hex($i),5) & @CRLF)
Next
FileClose($file)