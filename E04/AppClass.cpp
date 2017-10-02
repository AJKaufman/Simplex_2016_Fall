#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Aidan Kaufman - ak3012@rit.edu";	

	//init the mesh
	m_pMesh = new MyMesh();
	//m_pMesh->GenerateSphere(1.0f, 5, C_WHITE);

	for (uint i = 0; i < 46; ++i) {
		m_pMesh->GenerateCube(1.0f, C_BLACK);
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

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	
	matrix4 m4Scale = glm::scale(IDENTITY_M4, vector3(1.0f,1.0f,1.0f));
	matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(-5.0f, 0.0f, 0.0f));

	static float value = 0.0f;
	m4Translate = glm::translate(m4Translate, vector3(value, 0.0f, 0.0f));
	value += 0.01f;

	uint alien[8][11] = {
		{ 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0 },
		{ 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 }
	};


	for (uint i = 0; i < 8; ++i) {


		for (uint j = 0; j < 11; ++j) {


			if (alien[i][j]) {
				matrix4 m4Model = m4Translate;
				m_pMesh->Render(m4Projection, m4View, m4Model);
			}

			m4Translate = glm::translate(m4Translate, vector3(1.0f, 0.0f, 0.0f));

		}
		m4Translate = glm::translate(m4Translate, vector3(-11.0f, 1.0f, 0.0f));

	}



	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
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
	SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}