#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//Entity Manager
	m_pEntityMngr = MyEntityManager::GetInstance();

	//creeper
	m_pEntityMngr->AddEntity("Minecraft\\Creeper.obj", "Creeper");
	m_pEntityMngr->SetAxisVisibility(true, "Creeper"); //set visibility of the entity's axis

	//steve
	m_pEntityMngr->AddEntity("Minecraft\\Steve.obj", "Steve");
	m_pEntityMngr->SetAxisVisibility(true, "Steve"); //set visibility of the entity's axis

	//add an entity
	m_pEntityMngr->AddEntity("Minecraft\\Cow.obj", "Cow");
	//set the model matrix and visibility of the last entity added
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(2.0f, -1.5f, -1.0f)));
	m_pEntityMngr->SetAxisVisibility(true);

	//add an entity
	m_pEntityMngr->AddEntity("Minecraft\\Zombie.obj", "Zombie");
	//set the model matrix and visibility of the last entity added
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(0.0f, -2.5f, 0.0f)));
	m_pEntityMngr->SetAxisVisibility(true);

	//add an entity
	m_pEntityMngr->AddEntity("Minecraft\\Pig.obj", "Pig");
	//set the model matrix and visibility of the last entity added
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(-2.0f, -1.0f, -1.0f)));
	m_pEntityMngr->SetAxisVisibility(true);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Set model matrix to the creeper
	matrix4 mCreeper = glm::translate(m_v3Creeper) * ToMatrix4(m_qCreeper) * ToMatrix4(m_qArcBall);
	m_pEntityMngr->SetModelMatrix(mCreeper, "Creeper");


	//Set model matrix to Steve
	matrix4 mSteve = glm::translate(vector3(2.5f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, glm::radians(-55.0f), AXIS_Z);
	m_pEntityMngr->SetModelMatrix(mSteve, "Steve");


	//Move the last entity added slowly to the right
	matrix4 lastMatrix = m_pEntityMngr->GetModelMatrix();// get the model matrix of the last added
	lastMatrix *= glm::translate(IDENTITY_M4, vector3(0.01f, 0.0f, 0.0f)); //translate it
	m_pEntityMngr->SetModelMatrix(lastMatrix); //return it to its owner

	//Update My Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
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
	//release the entity manager
	m_pEntityMngr->ReleaseInstance();

	//release GUI
	ShutdownGUI();
}