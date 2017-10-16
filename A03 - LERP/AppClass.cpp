#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Aidan Kaufman - ak3012@rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));
	
	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUp(AXIS_Z * 20.0f, ZERO_V3, AXIS_Y);

	//if the light position is zero move it
	if (m_pLightMngr->GetPosition(1) == ZERO_V3)
		m_pLightMngr->SetPosition(vector3(0.0f, 0.0f, 3.0f));

	//if the background is cornflowerblue change it to black (its easier to see)
	if (vector3(m_v4ClearColor) == C_BLUE_CORNFLOWER)
	{
		m_v4ClearColor = vector4(ZERO_V3, 1.0f);
	}
	
	//if there are no segments create 7
	if(m_uOrbits < 1)
		m_uOrbits = 7;

	float fSize = 1.0f; //initial size of orbits

	//creating a color using the spectrum 
	uint uColor = 650; //650 is Red
	//prevent division by 0
	float decrements = 250.0f / (m_uOrbits > 1? static_cast<float>(m_uOrbits - 1) : 1.0f); //decrement until you get to 400 (which is violet)
	/*
		This part will create the orbits, it start at 3 because that is the minimum subdivisions a torus can have
	*/
	uint uSides = 3; // start with the minimal 3 sides
	float radius = 0.5f; // the offset used to distance the verts of the circles from the last circle
	for (uint i = uSides; i < m_uOrbits + uSides; i++)
	{

		std::vector<vector3> m_currentCircleVerts;
		float theta = 2.0f * PI / i;
		radius += 0.5f;

		for (uint j = 0; j < i; ++j) {
			
			// Fill a vector of vec3s
			m_currentCircleVerts.push_back(vector3((radius * glm::cos(theta * j)), (radius * glm::sin(theta * j)), 0.0f));
		}

		// Fill our vector of vectors of vec3s with the current vector of vec3s
		m_circleList.push_back(m_currentCircleVerts);

		// Update the next torus ring
		vector3 v3Color = WaveLengthToRGB(uColor); //calculate color based on wavelength
		m_shapeList.push_back(m_pMeshMngr->GenerateTorus(fSize, fSize - 0.1f, 3, i, v3Color)); //generate a custom torus and add it to the meshmanager
		fSize += 0.5f; //increment the size for the next orbit
		uColor -= static_cast<uint>(decrements); //decrease the wavelength
	}
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix(); //view Matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix(); //Projection Matrix
	matrix4 m4Offset = IDENTITY_M4; //offset of the orbits, starts as the global coordinate system
	/*
		The following offset will orient the orbits as in the demo, start without it to make your life easier.
	*/
	m4Offset = glm::rotate(IDENTITY_M4, 90.0f, AXIS_Z);


	//Get a timer
	static float fTimer = 0;	//store the new timer
	static uint uClock = m_pSystem->GenClock(); //generate a new clock for that timer
	fTimer += m_pSystem->GetDeltaTime(uClock); //get the delta time for that timer
	vector3 v3CurrentPos; //calculate the current position
	bool resetting = false;

	float fAnimationLasts = 0.5f;
	float fPercent = MapValue(fTimer, 0.0f, fAnimationLasts, 0.0f, 1.0f);

	static std::vector<uint> jList;
	for (uint i = 0; i < m_uOrbits; ++i) {
		jList.push_back(0);
	}

	// draw a shapes
	for (uint i = 0; i < m_uOrbits; ++i)
	{



		// Lerp between the most recently touched point and the next point in our vector of vector of vec3s

		if (jList[i] + 1 >= m_circleList[i].size()) {
			v3CurrentPos = glm::lerp(m_circleList[i][jList[i]], m_circleList[i][0], fPercent);

			resetting = true;
		}
		else {
			v3CurrentPos = glm::lerp(m_circleList[i][jList[i]], m_circleList[i][jList[i] + 1], fPercent);
		}

		// If the destination has been reached, reset the timer

		if (fPercent > 1.0f) {
			fTimer = 0;
				
			jList[i]++;


			// Reset the values of the jList vector so that they 

			if (resetting) {

				resetting = false;
				jList[i] = 0;
			}
		}

		m_pMeshMngr->AddMeshToRenderList(m_shapeList[i], glm::rotate(m4Offset, 90.0f, AXIS_X));

		//calculate the current position
		//vector3 v3CurrentPos = ZERO_V3;
		matrix4 m4Model = glm::translate(m4Offset, v3CurrentPos);

		//draw spheres
		m_pMeshMngr->AddSphereToRenderList(m4Model * glm::scale(vector3(0.1)), C_WHITE);
	}

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release GUI
	ShutdownGUI();
}