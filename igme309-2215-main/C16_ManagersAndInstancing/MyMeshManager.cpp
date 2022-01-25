#include "MyMeshManager.h"
using namespace BTX;
//  MyMeshManager
MyMeshManager* MyMeshManager::m_pInstance = nullptr;
void MyMeshManager::Init(void)
{
	GenerateCube(1.0f);	//0
	GenerateCone(1.0f, 1.0f, 12); //1
	GenerateCylinder(1.0f, 1.0f, 12); //2
	GenerateTube(1.0f, 0.6f, 1.0f, 12); //3
	GenerateSphere(1.0f, 6); //4
	GenerateTorus(1.0f, 0.6f, 12, 12); //5
}
void MyMeshManager::Release(void)
{
	uint uMeshCount = m_meshList.size();
	for (uint i = 0; i < uMeshCount; ++i)
	{
		Mesh* pMesh = m_meshList[i];
		if (pMesh)
		{
			delete pMesh;
			pMesh = nullptr;
		}
	}
	m_meshList.clear();
	m_renderList.clear();
}
MyMeshManager* MyMeshManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MyMeshManager();
	}
	return m_pInstance;
}
void MyMeshManager::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//The big 3
MyMeshManager::MyMeshManager() { Init(); }
MyMeshManager::MyMeshManager(MyMeshManager const& other) { }
MyMeshManager& MyMeshManager::operator=(MyMeshManager const& other) { return *this; }
MyMeshManager::~MyMeshManager() { Release(); };

//--- Non Standard Singleton Methods
int MyMeshManager::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	Mesh* pMesh = new Mesh();
	pMesh->GenerateCube(a_fSize, a_v3Color);
	return AddMesh(pMesh);
}
int MyMeshManager::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	Mesh* pMesh = new Mesh();
	pMesh->GenerateCone(a_fRadius, a_fHeight, a_nSubdivisions, a_v3Color);
	return AddMesh(pMesh);
}
int MyMeshManager::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	Mesh* pMesh = new Mesh();
	pMesh->GenerateCylinder(a_fRadius, a_fHeight, a_nSubdivisions, a_v3Color);
	return AddMesh(pMesh);
}
int MyMeshManager::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	Mesh* pMesh = new Mesh();
	pMesh->GenerateTube(a_fOuterRadius, a_fInnerRadius, a_fHeight, a_nSubdivisions, a_v3Color);
	return AddMesh(pMesh);
}
int MyMeshManager::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionHeight, int a_nSubdivisionAxis, vector3 a_v3Color)
{
	Mesh* pMesh = new Mesh();
	pMesh->GenerateTorus(a_fOuterRadius, a_fInnerRadius, a_nSubdivisionHeight, a_nSubdivisionAxis, a_v3Color);
	return AddMesh(pMesh);
}
int MyMeshManager::GenerateSphere(float a_fDiameter, int a_nSubdivisions, vector3 a_v3Color)
{
	Mesh* pMesh = new Mesh();
	pMesh->GenerateSphere(a_fDiameter, a_nSubdivisions, a_v3Color);
	return AddMesh(pMesh);
}
void MyMeshManager::AddCubeToRenderList(matrix4 a_m4ToWorld)
{
	// add an instance of the object to the pile
	AddMeshToRenderList((uint)0, a_m4ToWorld);
	return;
}
void MyMeshManager::AddConeToRenderList(matrix4 a_m4ToWorld)
{
	// add an instance of the object to the pile
	AddMeshToRenderList(1, a_m4ToWorld);
	return;
}
void MyMeshManager::AddCylinderToRenderList(matrix4 a_m4ToWorld)
{
	// add an instance of the object to the pile
	AddMeshToRenderList(2, a_m4ToWorld);
	return;
}
void MyMeshManager::AddTubeToRenderList(matrix4 a_m4ToWorld)
{
	// add an instance of the object to the pile
	AddMeshToRenderList(3, a_m4ToWorld);
	return;
}
void MyMeshManager::AddSphereToRenderList(matrix4 a_m4ToWorld)
{
	// add an instance of the object to the pile
	AddMeshToRenderList(4, a_m4ToWorld);
	return;
}
void MyMeshManager::AddTorusToRenderList(matrix4 a_m4ToWorld)
{
	// add an instance of the object to the pile
	AddMeshToRenderList(5, a_m4ToWorld);
	return;
}
void MyMeshManager::AddMeshToRenderList(Mesh* a_pMesh, matrix4 a_m4Transform)
{
	/*
	Doesn't need to check for nullptr, GetMeshIndex will do for me
	*/
	int uIndex = GetMeshIndex(a_pMesh);
	AddMeshToRenderList(uIndex, a_m4Transform);
}
void MyMeshManager::AddMeshToRenderList(uint a_nIndex, matrix4 a_m4Transform)
{
	//Id the index is larger than the number of meshes we know about return
	if (a_nIndex >= m_meshList.size())
		return;
	m_renderList[a_nIndex].push_back(a_m4Transform);
}
int MyMeshManager::GetMeshIndex(Mesh* a_pMesh)
{
	/*
	Doesn't need to check for nullptr, no mesh in the list is null so none will
	match, yet we do it for speed sake, if there are 1 zillion meshes I don't
	want to check them
	*/
	if (!a_pMesh)
		return -1;

	uint uMeshCount = m_meshList.size();
	//Check for each mesh in the mesh list if the provided mesh is in the list
	for (uint nMesh = 0; nMesh < uMeshCount; ++nMesh)
	{
		//if it is in the list return the index
		if (m_meshList[nMesh] == a_pMesh)
			return nMesh;
	}
	//not found
	return -1;
}
int MyMeshManager::AddMesh(Mesh* a_pMesh)
{
	//check if empty pointer
	if (!a_pMesh)
		return -1;

	//if the mesh is already in the list return the index
	int nMesh = GetMeshIndex(a_pMesh);
	if (nMesh > 0)
		return nMesh;

	m_meshList.push_back(a_pMesh);
	std::vector<matrix4> renderListForThisMesh;
	m_renderList.push_back(renderListForThisMesh);
	return m_meshList.size() - 1;
}
Mesh *MyMeshManager::GetMesh(uint nMesh)
{
	if (nMesh >= m_meshList.size())
		return nullptr;
	return m_meshList[nMesh];
}
uint MyMeshManager::GetMeshCount(void) { return m_meshList.size(); }
void MyMeshManager::ClearRenderList(void)
{
	uint uMeshCount = m_meshList.size();
	for (uint uMesh = 0; uMesh < uMeshCount; ++uMesh)
	{
		m_renderList[uMesh].clear();
	}
}
void MyMeshManager::SetCamera(MyCamera* a_pCamera) { m_pCamera = a_pCamera; }
void MyMeshManager::Render(void)
{
	//if the camera is not initialized return;
	if (!m_pCamera)
		return;
	
	//Check how many meshes are in the render list
	uint uMeshCount = m_meshList.size();

	//for each mesh render
	for (uint nMesh = 0; nMesh < uMeshCount; ++nMesh)
	{
		//get view and projection matrices
		matrix4 m4View = m_pCamera->GetViewMatrix();
		matrix4 m4Proj = m_pCamera->GetProjectionMatrix();
		
		//count how many do you have to render for each element in the list
		int nCount = m_renderList[nMesh].size();

		if (nCount > 0)
		{
			//make an array to store the floats, each matrix has 16 of them
			float* fTransformsArray = new float[16 * nCount];
			for (int i = 0; i < nCount; ++i)
			{
				//memcpy the translated values to the array (way faster than copy element by element)
				memcpy(&fTransformsArray[i * 16],
					glm::value_ptr(m_renderList[nMesh][i]),
					16 * sizeof(float)); //attach the value
			}

			//new instance rendering
			m_meshList[nMesh]->Render(m4Proj, m4View, fTransformsArray, nCount, ZERO_V3, RENDER_SOLID | RENDER_WIRE);

			//deallocate memory
			if (fTransformsArray)
			{
				delete[] fTransformsArray;
				fTransformsArray = nullptr;
			}
			//uint uCalls = m_renderList[uMesh].size();
			//for (uint uCall = 0; uCall < uCalls; ++uCall)
			//{
			//	m_meshList[uMesh]->Render(m_pCamera, m_renderList[uMesh][uCall]);
			//}
		}
		
	}
}