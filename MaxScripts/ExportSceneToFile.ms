--Ask the user to open the file
savePath = getSaveFileName caption:"Chose File Location" filename:"C:/level.stm" types:"SpaceTripMap file(*.stm)|*.stm"

--Check if the file has opened properly
if savePath != undefined do(
	--Create the file (will open + delete file contents if one exsists)
	outPutFile = createFile savePath
	
	--Select Everything in the scene
	allObjects = $*
	
	--Iterate through the objects
	for OBJ in allObjects do(
		--Get the eulerAngles of the rotation
		rot = OBJ.rotation as eulerAngles
		--Rotate the Z by 180 degrees
		rot.z += 180
		
		--Write all the infomation of the selected object to the file
		lineToWrite = \
		OBJ.name \
		+ " " + OBJ.position.x as string + " " + OBJ.position.z as string + " " + OBJ.position.y as string \
		+ " " + rot.x as string + " " + rot.z as string + " " + rot.y as string \
		+ " " + OBJ.scale.x as string + " " + OBJ.scale.z as string + " " + OBJ.scale.y as string \
		+ "\n"
		format lineToWrite to:outPutFile
	)
	
	--Close the file when we have finished writing
	close outPutFile
)