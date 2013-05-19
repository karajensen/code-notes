-------------------------------------------------------------------------------------------
-- STRUCTS
-------------------------------------------------------------------------------------------
struct FACE
(
	dead = false,
	v1 = 0,
	v2 = 0,
	v3 = 0,
	id = 0,
	normal
)
-------------------------------------------------------------------------------------------
-- FUNCTIONS
-------------------------------------------------------------------------------------------
fn SortVertsByZValue &v1 &v2 =
(
	case of
	(
		(v1.z < v2.z) : -1
		(v1.z > v2.z) : 1
		default: 0
	)
)
-------------------------------------------------------------------------------------------
-- HULL ROLLOUT
-------------------------------------------------------------------------------------------
rollout hulldialog "Convex Hull Generator"
(
	label hulllable "Convex Hull Generator"
	label space ""
	pickbutton hullpick "Pick Mesh" autoDisplay:true
	button hullbutton "Generate Hull"
	progressBar hullprogress value:0
	
	--DIALOG LOCAL VARS
	local selectedObj			--picked object
	local vertArray			--Point3 original mesh verts array
	local faces					--FACE hull faces array
	local illumFaces			--int illuinated faces to test array
	local hullNormalTester	--Point3 Tester for Normal direction
	
	-------------------------------------------------------------------------------------
	--CREATE FACE NORMAL FUNCTION
	-------------------------------------------------------------------------------------
	fn CreateFaceNormal &currentface &tester =
	(
		--Get connected verts to the face
		p0 = vertArray[currentface.v1]
		p1 = vertArray[currentface.v2]
		p2 = vertArray[currentface.v3]
		
		--Arranges the face so the normal is always facing to the outside of the mesh
		v1 = p1-p0
		v2 = p2-p0
		vT = tester-p0
		currentface.normal = cross v1 v2
		currentface.normal = normalize currentface.normal
	
		--if normal is pointing towards tester, reverse face
		if ((dot currentface.normal vT) > 0) then
		(
			currentface.normal *= -1
			tempval = currentface.v2
			currentface.v2 = currentface.v3
			currentface.v3 = tempval
		)	
	)	
	-------------------------------------------------------------------------------------
	--CREATE HULL FACE FUNCTION
	-------------------------------------------------------------------------------------
	fn CreateHullFace &oldFace target connectedFaceId =
	(
		v1 = 0
		v2 = 0
		found1 = false
		newFace = FACE()
		
		--find the shared verts between the two faces
		if oldFace.v1 == faces[connectedFaceId].v1 then
		(
			v1 = oldFace.v1
			found1 = true
		)
		else if oldFace.v1 == faces[connectedFaceId].v2 then
		( 
			v1 = oldFace.v1
			found1 = true
		)
		else if oldFace.v1 == faces[connectedFaceId].v3 then
		(		
			v1 = oldFace.v1
			found1 = true
		)
		
		if oldFace.v2 == faces[connectedFaceId].v1 then
		(
			if found1 == false then
			(			
				v1 = oldFace.v2; 
				found1 = true
			)
			else ( v2 = oldFace.v2 )
		)
		else if oldFace.v2 == faces[connectedFaceId].v2 then
		(
			if found1 == false then
			(			
				v1 = oldFace.v2
				found1 = true
			)				
			else ( v2 = oldFace.v2 )
		)
		else if oldFace.v2 == faces[connectedFaceId].v3 then
		(
			if found1 == false then
			( 
				v1 = oldFace.v2
				found1 = true
			)
			else ( v2 = oldFace.v2 )
		)

		if oldFace.v3 == faces[connectedFaceId].v1 then  ( v2 = oldFace.v3 )
		else if oldFace.v3 == faces[connectedFaceId].v2 then ( v2 = oldFace.v3 )
		else if oldFace.v3 == faces[connectedFaceId].v3 then ( v2 = oldFace.v3 )
		
		--update the new face
		newface.v1 = v1
		newface.v2 = v2
		newface.v3 = target
		newface.id = faces.count+1
	
		--face is good to go
		CreateFaceNormal &newface &hullNormalTester
		append faces newface
	)	
	-------------------------------------------------------------------------------------
	--SHARES VERTS TESTER FUNCTION
	-------------------------------------------------------------------------------------
	fn SharesVerts &f1 & f2 =
	(
		isSharingVerts = false
		numberfound = 0
		if f1.v1 == f2.v1 then ( numberfound+=1 )
		if f1.v1 == f2.v2 then ( numberfound+=1 )
		if f1.v1 == f2.v3 then ( numberfound+=1 )
		if f1.v2 == f2.v1 then ( numberfound+=1 )
		if f1.v2 == f2.v2 then ( numberfound+=1 )
		if f1.v2 == f2.v3 then ( numberfound+=1 )
		if f1.v3 == f2.v1 then ( numberfound+=1 )
		if f1.v3 == f2.v2 then ( numberfound+=1 )
		if f1.v3 == f2.v3 then ( numberfound+=1 )
		if numberfound == 2 then ( isSharingVerts = true	)
		return isSharingVerts
	)
	-------------------------------------------------------------------------------------
	--PICK OBJECT
	-------------------------------------------------------------------------------------
	on hullpick picked obj do
	(
		hullprogress.value = 0
		selectedObj = obj
	)
	-------------------------------------------------------------------------------------
	--CREATE CONVEX HULL
	-------------------------------------------------------------------------------------
	on hullbutton pressed do
	(
		if (selectedObj == undefined) then
			messagebox "Please select a valid object"
		else if (isDeleted selectedObj) then
			messagebox "Please select a valid object"
		else
		(
			--Turn off draws
			hullprogress.value = 0
			--disableSceneRedraw()
			--suspendEditing()
			undo off
			
			--Clean arrays
			vertArray = #()
			faces = #()
			illumFaces = #()
			gc light:true
			
			--Grab the verts from the mesh
			set coordsys world
			tempObject = copy selectedObj
			tempMeshObject = convertToMesh tempObject
			vertNumber = getNumVerts tempMeshObject
			for i = 1 to vertNumber do
				append vertArray (getVert tempMeshObject i)
			delete tempMeshObject
			
			--Sort array by y-value
			qsort vertArray SortVertsByZValue
			--for vert in vertArray do print vert
			
			--create the initial hull from the lowest/highest verts
			for i = 1 to 4 do
				append faces (FACE())
			faces[1].v1 = 1	
			faces[1].v2 = 2							
			faces[1].v3 = vertNumber
			faces[2].v1 = 1	
			faces[2].v2 = vertNumber				
			faces[2].v3 = vertNumber-1
			faces[3].v1 = 1	
			faces[3].v2 = vertNumber-1			
			faces[3].v3 = 2
			faces[4].v1 = 2	
			faces[4].v2 = vertNumber				
			faces[4].v3 = vertNumber-1
					
			faces[1].id = 1
			faces[2].id = 2
			faces[3].id = 3		
			faces[4].id = 4
					
			--create face normals
			CreateFaceNormal &faces[1] &vertArray[vertNumber-1]
			CreateFaceNormal &faces[2] &vertArray[2]
			CreateFaceNormal &faces[3] &vertArray[vertNumber]
			CreateFaceNormal &faces[4] &vertArray[1]			
					
			--create test point (this is roughly in middle but always inside hull)
			mid = ( vertArray[faces[1].v1] + vertArray[faces[1].v2] + vertArray[faces[1].v3] ) / 3.0
			midbar = vertArray[vertNumber-1] - mid
			hullNormalTester = mid + (midbar*0.5)
			--s = sphere pos:hullnormaltester radius:2
	
			--Determine progress amount
			progressIncrement = 90.0/(vertNumber-4)
			savedProgress = 0			
					
			--main algorithm loop, don't bother with first and last two
			lastvert = vertNumber-2
			--for i = 3 to 4 do
			for i = 3 to lastvert do
			(
				--s = sphere pos:vertArray[4] radius:2
				
				--determine which faces the vert illuminates
				for j = 1 to faces.count do
				(
					if faces[j].dead == false then
					(
						faceToVert = vertArray[i]-vertArray[faces[j].v1]
						if (dot faces[j].normal faceToVert > 0) then
							append illumFaces faces[j].id
					)
				)
				
				--process any illuminated faces, these are the faces that are to be deleted
				--as new faces will take their place
				if illumFaces.count > 0 then
				(
					--for all faces that are highlighted
					for k = 1 to illumFaces.count do
					(
						--choose a face to look at
						faces[illumFaces[k]].dead = true
						f1horizon = false
						f2horizon = false
						f3horizon = false
						f1 = 0
						f2 = 0
						f3 = 0
						
						--check to see if any of faces edges are on horizon			
						for s = 1 to faces.count do
						(
							if f1horizon and f2horizon and f3horizon then
							(
								s = faces.count --exit loop
							)
							else
							(
								--if not dead and not the current face
								if faces[s].dead == false and faces[s].id != illumFaces[k] then
								(
									isSharingVerts = SharesVerts &faces[s] &faces[illumFaces[k]]
									if isSharingVerts then
									(
										--check if a highlighted face
										highlighted = false
										for h = 1 to illumFaces.count do
										(
											if faces[s].id == illumFaces[h] then
											(
												highlighted = true
												h = illumFaces.count --exit loop
											)
										)
										if highlighted == false then
										(
											if f1horizon == false then
											( 
												f1horizon = true
												f1 = faces[s].id
											)
											else if f2horizon == false then
											( 
												f2horizon = true
												f2 = faces[s].id
											)
											else if f3horizon == false then
											( 
												f3horizon = true
												f3 = faces[s].id
											)	
										)											
									)
								)
							)
						)
						--face is on the outer horizon, create a new face for each horizon edge
						if f1horizon then
							CreateHullFace &faces[illumFaces[k]] i f1
						if f2horizon then
							CreateHullFace &faces[illumFaces[k]] i f2
						if f3horizon then
							CreateHullFace &faces[illumFaces[k]] i f3
					)
					--clean up array
					illumFaces = #()
					gc light:true
					--for vert in illumFaces do print vert
					
				)
				--increment progress
				savedProgress += progressIncrement
				hullprogress.value = savedProgress
			)
			
			--Create the mesh
			--vertices = #()
			indices = #()
			for i = 1 to faces.count do
			(
				if faces[i].dead == false then
				(
					append indices (point3 faces[i].v1 faces[i].v2 faces[i].v3)
				)
			)
			mesh vertices:vertArray faces:indices
			hullprogress.value = 100
						
			--Turn on draws
			enableSceneRedraw()
			resumeEditing()
			redrawViews()
		)
	)
)

-------------------------------------------------------------------------------------------
-- MAIN BODY OF SCRIPT
-------------------------------------------------------------------------------------------
(
	-- destroy any previous instances of rollout
	if hulldialog != undefined then
		destroyDialog hulldialog

	-- create the dialog
	createDialog hulldialog 150 150
)