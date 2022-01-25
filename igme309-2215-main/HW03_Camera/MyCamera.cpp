#include "MyCamera.h"
using namespace BTX;
//  MyCamera
void MyCamera::SetPositionTargetAndUpward(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward)
{
	//TODO:: replace the super call with your functionality
	//Tip: Changing any positional vector forces you to calculate new directional ones
	super::SetPositionTargetAndUpward(a_v3Position, a_v3Target, a_v3Upward);

	//After changing any vectors you need to recalculate the MyCamera View matrix.
	//While this is executed within the parent call above, when you remove that line
	//you will still need to call it at the end of this method
	CalculateView();
}
void MyCamera::MoveForward(float a_fDistance)
{
	//Tips:: Moving will modify both positional and directional vectors,
	//		 here we only modify the positional.
	//       The code below "works" because we wrongly assume the forward 
	//		 vector is going in the global -Z but if you look at the demo 
	//		 in the _Binary folder you will notice that we are moving 
	//		 backwards and we never get closer to the plane as we should 
	//		 because as we are looking directly at it.
	m_v3Position += vector3(0.0f, 0.0f, a_fDistance);
	m_v3Target += vector3(0.0f, 0.0f, a_fDistance);
}
void MyCamera::MoveVertical(float a_fDistance)
{
	//Tip:: Look at MoveForward
}
void MyCamera::MoveSideways(float a_fDistance)
{
	//Tip:: Look at MoveForward
}
void MyCamera::CalculateView(void)
{
	//Tips:: Directional vectors will be affected by the orientation in the quaternion
	//		 After calculating any new vector one needs to update the View Matrix
	//		 Camera rotation should be calculated out of the m_v3PitchYawRoll member
	//		 it will receive information from the main code on how much these orientations
	//		 have change so you only need to focus on the directional and positional 
	//		 vectors. There is no need to calculate any right click process or connections.
	m_m4View = glm::lookAt(m_v3Position, m_v3Target, m_v3Upward);
}
//You can assume that the code below does not need changes unless you expand the functionality
//of the class or create helper methods, etc.
void MyCamera::Init(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward)
{
	m_bFPS = true;
	m_nMode = BTXs::eCAMERAMODE::CAM_PERSP;
	m_fFOV = 45.0f;
	m_v2NearFar = vector2(0.001f, 1000.0f);
	m_v3PitchYawRoll = vector3(0.0f);
	SystemSingleton* pSystem = SystemSingleton::GetInstance();
	vector2 v3WidthHeigh(	static_cast<float>(pSystem->GetWindowWidth()),
							static_cast<float>(pSystem->GetWindowHeight()));
	SetWidthAndHeightOfDisplay(v3WidthHeigh);

	return SetPositionTargetAndUpward(a_v3Position, a_v3Target, a_v3Upward);
}
void MyCamera::Swap(MyCamera& other)
{
	std::swap(m_bFPS, other.m_bFPS);

	std::swap(m_nMode, other.m_nMode);

	std::swap(m_fFOV, other.m_fFOV);

	std::swap(m_v2NearFar, other.m_v2NearFar);

	std::swap(m_v3Position, other.m_v3Position);
	std::swap(m_v3Target, other.m_v3Target);
	std::swap(m_v3Above, other.m_v3Above);

	std::swap(m_v3Forward, other.m_v3Forward);
	std::swap(m_v3Upward, other.m_v3Upward);
	std::swap(m_v3Rightward, other.m_v3Rightward);

	std::swap(m_v3PitchYawRoll, other.m_v3PitchYawRoll);

	std::swap(m_m4Projection, other.m_m4Projection);
	std::swap(m_m4View, other.m_m4View);
}
void MyCamera::Release(void){}
//The big 3
MyCamera::MyCamera()
{
	Init(vector3(0.0f, 0.0f, 5.0f), vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 1.0f, 0.0f));
}
MyCamera::MyCamera(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward)
{
	Init(a_v3Position, a_v3Target, a_v3Upward);
}
MyCamera::MyCamera(MyCamera const& other)
{
	m_bFPS = other.m_bFPS;

	m_nMode = other.m_nMode;

	m_fFOV = other.m_fFOV;

	m_v2NearFar = other.m_v2NearFar;

	m_v3Position = other.m_v3Position;
	m_v3Target = other.m_v3Target;
	m_v3Above = other.m_v3Above;

	m_v3Forward = other.m_v3Forward;
	m_v3Upward = other.m_v3Upward;
	m_v3Rightward = other.m_v3Rightward;

	m_v3PitchYawRoll = other.m_v3PitchYawRoll;

	m_m4Projection = other.m_m4Projection;
	m_m4View = other.m_m4View;
}
MyCamera& MyCamera::operator=(MyCamera const& other)
{
	if (this != &other)
	{
		Release();
		Init(other.m_v3Position, other.m_v3Target, other.m_v3Upward);
		MyCamera temp(other);
		Swap(temp);
	}
	return *this;
}
MyCamera::~MyCamera(){ Release(); };
//Accessors
vector3 MyCamera::GetPosition(void){ return m_v3Position; }
vector3 MyCamera::GetForward(void) { return m_v3Forward; }
vector3 MyCamera::GetUpward(void) { return m_v3Upward; }
vector3 MyCamera::GetRightward(void) { return m_v3Rightward; }
void MyCamera::SetForward(vector3 a_v3Input) { m_v3Forward = a_v3Input; }
void MyCamera::SetUpward(vector3 a_v3Input) { m_v3Upward = a_v3Input; }
void MyCamera::SetRightward(vector3 a_v3Input) { m_v3Rightward = a_v3Input; }
matrix4 MyCamera::GetViewMatrix(void){ CalculateView(); return m_m4View; }
matrix4 MyCamera::GetProjectionMatrix(void){ CalculateProjection(); return m_m4Projection; }
void MyCamera::SetNearFarPlanes(float a_fNear, float a_fFar){ m_v2NearFar = vector2(a_fNear, a_fFar); }
void MyCamera::SetFOV(float a_fFOV){ m_fFOV = a_fFOV; }
void MyCamera::SetFPS(bool a_bFPS){ m_bFPS = a_bFPS; }
void MyCamera::SetCameraMode(BTXs::eCAMERAMODE a_nMode){ /*Removed to simplify assignment*/ }
BTXs::eCAMERAMODE MyCamera::GetCameraMode(void){ return m_nMode; }
void MyCamera::SetPosition(vector3 a_v3Position)
{
	return SetPositionTargetAndUpward(a_v3Position, m_v3Target, m_v3Upward);
}
void MyCamera::SetTarget(vector3 a_v3Target)
{
	return SetPositionTargetAndUpward(m_v3Position, a_v3Target, m_v3Upward);
}
matrix4 MyCamera::GetMVP(matrix4 a_m4ModelToWorld)
{
	CalculateProjection();
	CalculateView();
	return m_m4Projection * m_m4View * a_m4ModelToWorld;
}
matrix4 MyCamera::GetVP(void)
{
	CalculateProjection();
	CalculateView();
	return m_m4Projection * m_m4View;
}
//--- Non Standard Singleton Methods
void MyCamera::CalculateProjection(void)
{
	SystemSingleton* pSystem = SystemSingleton::GetInstance();
	vector2 v3WidthHeigh(	static_cast<float>(pSystem->GetWindowWidth()),
							static_cast<float>(pSystem->GetWindowHeight()));
	SetWidthAndHeightOfDisplay(v3WidthHeigh);
	float fRatio = v3WidthHeigh.x / v3WidthHeigh.y;
	m_m4Projection = glm::perspective(m_fFOV, fRatio, m_v2NearFar.x, m_v2NearFar.y);
}

void MyCamera::ChangePitch(float a_fDegree)
{
	m_v3PitchYawRoll.x += a_fDegree;
}
void MyCamera::ChangeYaw(float a_fDegree)
{
	m_v3PitchYawRoll.y += a_fDegree;
}
void MyCamera::ChangeRoll(float a_fDegree)
{
	m_v3PitchYawRoll.z += a_fDegree;
}

void MyCamera::ResetCamera(void)
{
	m_v3PitchYawRoll = vector3(0.0f);

	m_v3Position = vector3(0.0f, 0.0f, 10.0f);
	m_v3Target = vector3(0.0f, 0.0f, 9.0f);
	m_v3Above = vector3(0.0f, 1.0f, 10.0f);

	m_v3Forward = vector3(0.0f, 0.0f, -1.0f);
	m_v3Upward = vector3(0.0f, 1.0f, 0.0f);
	m_v3Rightward = vector3(1.0f, 0.0f, 0.0f);

}
void MyCamera::SetWidthAndHeightOfDisplay(vector2 a_v2WidthHeight)
{
	m_fWidth = a_v2WidthHeight.x;
	m_fHeight = a_v2WidthHeight.y;
}