#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	m_sModel1 = "Minecraft\\Creeper.obj";
	m_sModel2 = "Minecraft\\Steve.obj";

	//creeper
	m_pModelMngr->LoadModel(m_sModel1);
	m_pModel1RB = new MyRigidBody(m_pModelMngr->GetVertexList(m_sModel1));

	//steve
	m_pModelMngr->LoadModel(m_sModel2);
	m_pModel2RB = new MyRigidBody(m_pModelMngr->GetVertexList(m_sModel2));
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
	m_pModelMngr->AddModelToRenderList(m_sModel1, glm::translate(m_v3Model1) * ToMatrix4(m_qArcBall));
	m_pModel1RB->SetModelMatrix(glm::translate(m_v3Model1) * ToMatrix4(m_qArcBall));
	m_pModel1RB->SetColor(C_WHITE); //reset the color of the rigid bodies to white
	m_pModel1RB->AddToRenderList();
	
	//Set model matrix to Steve
	m_pModelMngr->AddModelToRenderList(m_sModel2, glm::translate(vector3(2.25f, 0.0f, 0.0f)));
	m_pModel2RB->SetModelMatrix(glm::translate(vector3(2.25f, 0.0f, 0.0f)));
	m_pModel2RB->SetColor(C_WHITE); //reset the color of the rigid bodies to white
	m_pModel2RB->AddToRenderList();

	//check collision, if they are colliding render it in red
	if (m_pModel1RB->IsColliding(m_pModel2RB))
	{
		m_pModel1RB->SetColor(C_RED);
		m_pModel2RB->SetColor(C_RED);
	}

	m_pModel1RB->AddToRenderList();
	m_pModel2RB->AddToRenderList();
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
	SafeDelete(m_pModel1RB);

	//release the rigid body for model 2
	SafeDelete(m_pModel2RB);

	//release GUI
	ShutdownGUI();
}