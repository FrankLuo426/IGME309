#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);
	
	//allocate the primitive
	m_pMesh = new Mesh();
	m_pMesh->GenerateCone(0.5f, 1.0f, 6, C_GREEN);

	//Load a model for example with complex models
	m_pModelMngr->LoadModel("Minecraft\\Steve.obj");

	//create a new camera
	m_pCamera = new MyCamera();
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	/*
	Attach the model matrix that takes me from the world coordinate system, the
	model manager does not currently implement changing the model matrices for 
	View and Projection matrices for individual models, only all of the models
	contained in it at once when the render call feeds both of them
	*/
	m_pModelMngr->AddModelToRenderList("Minecraft\\Steve.obj", ToMatrix4(m_qArcBall));

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

	//Camera position
	static float fPos = 0.0f;
	m_pCamera->SetPosition(vector3(fPos, 0.0f, 10.0f));
	m_pCamera->SetTarget(vector3(fPos, 0.0f, 9.0f));
	fPos -= 0.01f;
	/* 
	Steve is in the dll's Camera class space, while the other primitives
	are in the MyCamera class space so they seem to be separating altough
	in reality the camera for the mesh moves to the left (thus making it 
	look like the primitive is moving to the right) and the Dll's camera 
	doesnt move at all!
	*/

	//draw the primitive
	m_pMesh->Render(	m_pCamera->GetProjectionMatrix(),	//Projection
						m_pCamera->GetViewMatrix(),			//View
						IDENTITY_M4);						//model

	//render list call
	m_uRenderCallCount = m_pModelMngr->Render();
	//Example on changing the model and view matrices on the model manager
	//camera position is used to calculate normal maps and other things in the
	//shaders, uncomment the following to have a new render call with the same
	//model but this time using the MyCamera class
	/*
	m_uRenderCallCount = 
		m_pModelMngr->Render(
			m_pCamera->GetProjectionMatrix(),	//Projection
			m_pCamera->GetViewMatrix(),			//View
			m_pCamera->GetPosition());			//camera position
	*/
	//clear the render list
	m_pModelMngr->ClearRenderList();

	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release primitive
	SafeDelete(m_pMesh);

	//release the camera
	SafeDelete(m_pCamera);

	//release GUI
	ShutdownGUI();
}