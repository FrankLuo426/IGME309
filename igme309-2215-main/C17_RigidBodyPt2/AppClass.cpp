#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	m_sCreeper = "Minecraft\\Creeper.obj";
	m_sSteve = "Minecraft\\Steve.obj";

	//creeper
	m_pModelMngr->LoadModel(m_sCreeper);
	m_pCreeperRB = new MyRigidBody(m_pModelMngr->GetVertexList(m_sCreeper));

	//steve
	m_pModelMngr->LoadModel(m_sSteve);
	m_pSteveRB = new MyRigidBody(m_pModelMngr->GetVertexList(m_sSteve));
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

	//Set model matrix to the creeper
	m_pModelMngr->AddModelToRenderList(m_sCreeper, glm::translate(m_v3Creeper) * ToMatrix4(m_qArcBall));
	m_pCreeperRB->SetModelMatrix(glm::translate(m_v3Creeper) * ToMatrix4(m_qArcBall));
	m_pCreeperRB->AddToRenderList();
	
	//Set model matrix to Steve
	m_pModelMngr->AddModelToRenderList(m_sSteve, glm::translate(vector3(2.25f, 0.0f, 0.0f)));
	m_pSteveRB->SetModelMatrix(glm::translate(vector3(2.25f, 0.0f, 0.0f)));
	m_pSteveRB->AddToRenderList();

	//check collision, if they are colliding render it in red
	if (m_pCreeperRB->IsColliding(m_pSteveRB))
	{
		// As the IsColliding method returns a boolean, someting else can be done here, but
		// nothing is needed for our case.
	}

	m_pCreeperRB->AddToRenderList();
	m_pSteveRB->AddToRenderList();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();

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
	//release the rigid body for model 1
	SafeDelete(m_pCreeperRB);

	//release the rigid body for model 2
	SafeDelete(m_pSteveRB);

	//release GUI
	ShutdownGUI();
}