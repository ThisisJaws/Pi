--Ask the user to open the file
savePath = getSaveFileName caption:"Chose File Location" filename:"C:/level.stm" types:"SpaceTripMap file(*.stm)|*.stm"

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
		--Get the eulerAngles of the rotation
		rot = OBJ.rotation as eulerAngles
		
		--Write all the infomation of the selected object to the file
		lineToWrite = "N:" + OBJ.name \
		+ " P:" + OBJ.position.x as string + "," + OBJ.position.y as string + "," + OBJ.position.z as string \
		+ " R:" + rot.x as string + "," + rot.y as string + "," + rot.z as string \
		+ " S:" + OBJ.scale.x as string + "," + OBJ.scale.y as string + "," + OBJ.scale.z as string \
		+ "\n"
		format lineToWrite to:outPutFile
	)
	
	--Make a mark in the file
	format "Export_End\n" to:outPutFile
	--Close the file when we have finished writing
	close outPutFile
)