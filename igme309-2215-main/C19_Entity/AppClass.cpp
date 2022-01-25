#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//creeper
	m_pCreeper = new MyEntity("Minecraft\\Creeper.obj", "Creeper");

	//Others
	m_pSteve = new MyEntity("Minecraft\\Steve.obj", "Steve");
	m_pCow = new MyEntity("Minecraft\\Cow.obj", "Cow");
	m_pZombie = new MyEntity("Minecraft\\Zombie.obj", "Zombie");
	m_pPig = new MyEntity("Minecraft\\Pig.obj", "Pig");
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
	m_pCreeper->SetModelMatrix(mCreeper);


	//Set model matrix to Steve
	matrix4 mSteve = glm::translate(vector3(2.25f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, glm::radians(-55.0f), AXIS_Z);
	m_pSteve->SetModelMatrix(mSteve);

	matrix4 mCow = glm::translate(vector3(1.55f, 1.0f, 0.0f)) * glm::rotate(IDENTITY_M4, glm::radians(-55.0f), AXIS_Z);
	matrix4 mPig = glm::translate(vector3(0.0f, 0.5f, -1.5f)) * glm::rotate(IDENTITY_M4, glm::radians(-55.0f), AXIS_Z);
	matrix4 mZombie = glm::translate(vector3(1.55f, 0.0f, -3.0f)) * glm::rotate(IDENTITY_M4, glm::radians(-55.0f), AXIS_Z);


	m_pCow->SetModelMatrix(mCow);
	m_pPig->SetModelMatrix(mPig);
	m_pZombie->SetModelMatrix(mZombie);

	//Check collision
	bool bColliding = m_pCreeper->IsColliding(m_pSteve);
	/*
	* Note 1:
	* As you can see here we have to check collisions one by one in the next lesson
	* we will have a manager that does that for us instead no matter how many entities
	* we have, thus avoiding hard-codding per object pair, I can potentially have the
	* creeper check against the other 3 entities but that does not alleviate the fact
	* that the other entities can be colliding among themselves too.
	*/

	//Add objects to render list
	m_pCreeper->AddToRenderList(true);
	m_pSteve->AddToRenderList(true);
	m_pZombie->AddToRenderList(true);
	m_pPig->AddToRenderList(true);
	m_pCow->AddToRenderList(true);

	/*
	* Note 2: 
	I know the following part is confusing, the Entity manager is going to be
	* the next topic we will do our own class "MyEntityManager" but the following one
	* is in the system already and its here just with the purpose of rendering the
	* skybox; it is not related to today's topic
	*/
	//Update Entity Manager
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
	//release the creeper
	SafeDelete(m_pCreeper);

	//release Steve
	SafeDelete(m_pSteve);

	SafeDelete(m_pZombie);
	SafeDelete(m_pCow);
	SafeDelete(m_pPig);

	//release GUI
	ShutdownGUI();
}