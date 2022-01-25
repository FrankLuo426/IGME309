#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);
	//init the mesh
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCone(0.5f, 1.0f, 7, C_RED);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix(); //view Matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix(); //Projection Matrix

	//Get a timer
	static uint uClock = m_pSystem->GenClock();
	float fTimer = m_pSystem->GetTimeSinceStart(uClock);

	//calculate the current position
	matrix4 m4Rotation = glm::rotate(IDENTITY_M4, glm::radians(fTimer * 60.0f), vector3(0.0f, 0.0f, 1.0f));
	matrix4 m4Model;
	for (uint i = 0; i < 2500; ++i)
		m4Model = m4Rotation * glm::translate(IDENTITY_M4, vector3(2.5f, 0.0f, 0.0f)) * glm::transpose(m4Rotation);

	/*
	//extra part, how to rotate around a point (in this case the base of the cone)
	matrix4 m4Translation = glm::translate(IDENTITY_M4, vector3(0.0f, 0.5f, 0.0f));
	matrix4 m4TransInverse = glm::translate(IDENTITY_M4, vector3(0.0f, -0.5f, 0.0f));
	m4Model = m4TransInverse * m4Rotation * m4Translation;
	*/

	// render the object
	m_pMesh->Render(m4Projection, m4View, m4Model);

	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();

	//draw the center of the world
	m_pModelMngr->AddSphereToRenderList(glm::scale(vector3(0.1f)), C_RED, RENDER_WIRE);


	//render list call
	m_uRenderCallCount = m_pModelMngr->Render();

	//clear the render list
	m_pModelMngr->ClearRenderList();

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