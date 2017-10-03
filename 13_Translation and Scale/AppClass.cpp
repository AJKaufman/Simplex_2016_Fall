#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	//m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));
	
	m_pCameraMngr->SetPositionTargetAndUp(
		vector3(0.0f, 0.0f, 20.0f),
		vector3(0.0f, 0.0f, 20.0f),
		vector3(0.0f, 1.0f, 20.0f)
	);

	//init the mesh
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCone(1.0f, 1.5f, 10, C_WHITE);
	//m_pMesh->GenerateSphere(1.0f, 5, C_WHITE);

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
	vector3 v3Stop0 = vector3(0.0f, 0.0f, 0.0f);
	vector3 v3Stop1 = vector3(0.0f, 5.0f, 0.0f);
	vector3 v3Stop2 = vector3(5.0f, 0.0f, 0.0f);

	static DWORD StartTime = GetTickCount();
	DWORD fCurrentTime = GetTickCount();
	float fTime = (fCurrentTime - StartTime) / 1000;
	static float fPercent = fTime;

	float fAnimationLasts = 5.0f;
	float fPercent = MapValue(fTime, 0.0f, fAnimationLasts, 0.0f, 1.0f);

	vector3 v3Current = glm::lerp(v3Stop0, v3Stop1, fPercent);

	if (fPercent > 1.0f) {
		StartTime = GetTickCount();
	}

	matrix4 m4Model =  glm::translate(v3Current);

	m_pMesh->Render(m4Projection, m4View, m4Model);
	m_pMesh->Render(m4Projection, m4View, glm::translate(IDENTITY_M4, v3Stop0) * glm::scale(vector3(0.25f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(IDENTITY_M4, v3Stop1) * glm::scale(vector3(0.25f)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(IDENTITY_M4, v3Stop2) * glm::scale(vector3(0.25f)));
	
#pragma region Debugging Information
	//Print info on the screen
	uint nEmptyLines = 21;
	for (uint i = 0; i < nEmptyLines; ++i)
		m_pMeshMngr->PrintLine("");//Add a line on top
								   //m_pMeshMngr->Print("						");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), C_YELLOW);

	//m_pMeshMngr->Print("						");
	m_pMeshMngr->Print("Time: ");//Add a line on top
	m_pMeshMngr->PrintLine(std::to_string(fTime), C_YELLOW);

	//m_pMeshMngr->Print("						");
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(m_pSystem->GetFPS()), C_RED);
#pragma endregion

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