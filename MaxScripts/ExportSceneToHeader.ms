--Ask the user to open the file
savePath = getSaveFileName caption:"Chose File Location" filename:"C:/rename_to_level_name_system.h" types:"C++ Header File(*.h)|*.h"

--Check if the file has opened properly
if savePath != undefined do(
	--Create the file (will open + delete file contents if one exsists)
	outPutFile = createFile savePath
	
	--Select Everything in the scene
	allObjects = $*
	
	--Make a mark in the file
	format "Export_Begin\n" to:outPutFile
	
	--Iterate through the objects
	for OBJ in allObjects do(
		--Write all the infomation the selected object to the file
		lineToWrite = "N:" + OBJ.name + " P:" + OBJ.position as string + " R:" + OBJ.rotation as string + " S:" + OBJ.scale as string + "\n"
		format lineToWrite to:outPutFile
	)
	
	--Make a mark in the file
	format "Export_End\n" to:outPutFile
	--Close the file when we have finished writing
	close outPutFile
)