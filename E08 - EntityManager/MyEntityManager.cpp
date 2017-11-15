#include "MyEntityManager.h"
using namespace Simplex;
//  MyEntityManager
MyEntityManager* MyEntityManager::m_pInstance = nullptr;
void MyEntityManager::Init(void)
{
	m_uEntityCount = 0;
	m_entityList.clear();
}
void MyEntityManager::Release(void)
{
	for (uint i = 0; i < m_entityList.size(); ++i) {
		MyEntity* pEntity = m_entityList[i];
		SafeDelete(pEntity);
	}
	m_uEntityCount = 0;
	m_entityList.clear();
}
MyEntityManager* MyEntityManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MyEntityManager();
	}
	return m_pInstance;
}

// Release the singleton
void MyEntityManager::ReleaseInstance()
{
	if (m_pInstance != nullptr) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

// Gets the index from our m_entityList
int Simplex::MyEntityManager::GetEntityIndex(String a_sUniqueID)
{

	for (uint i = 0; i < m_uEntityCount; ++i) {
		if (m_entityList[i]->GenUniqueID == a_sUniqueID) return i;
	}

	return -1;
}
//Accessors
Model* Simplex::MyEntityManager::GetModel(uint a_uIndex)
{

	if (m_entityList.size() == 0) return nullptr;
	if (a_uIndex >= m_uEntityCount) a_uIndex = m_uEntityCount - 1; // If the argument is bigger than the list's size, use the last element

	return m_entityList[a_uIndex]->GetModel();
}
Model* Simplex::MyEntityManager::GetModel(String a_sUniqueID)
{

	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);

	if (pTemp) return pTemp->GetModel();

	return nullptr;
}
RigidBody* Simplex::MyEntityManager::GetRigidBody(uint a_uIndex)
{

	if (m_entityList.size() == 0) return nullptr;
	if (a_uIndex >= m_uEntityCount) a_uIndex = m_uEntityCount - 1; // If the argument is bigger than the list's size, use the last element

	return m_entityList[a_uIndex]->GetRigidBody();
}
RigidBody* Simplex::MyEntityManager::GetRigidBody(String a_sUniqueID)
{
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);

	if (pTemp) return pTemp->GetRigidBody();

	return nullptr;
}
matrix4 Simplex::MyEntityManager::GetModelMatrix(uint a_uIndex)
{

	if (m_entityList.size() >= 0) return IDENTITY_M4;
	if (a_uIndex >= m_uEntityCount) a_uIndex = m_uEntityCount - 1; // If the argument is bigger than the list's size, use the last element

	return m_entityList[a_uIndex]->GetModelMatrix();
}
matrix4 Simplex::MyEntityManager::GetModelMatrix(String a_sUniqueID)
{

	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);

	if (pTemp) return pTemp->GetModelMatrix();

	return IDENTITY_M4;
}
void Simplex::MyEntityManager::SetModelMatrix(matrix4 a_m4ToWorld, String a_sUniqueID)
{
	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);

	if (pTemp) pTemp->SetModelMatrix(a_m4ToWorld);
}
void Simplex::MyEntityManager::SetModelMatrix(matrix4 a_m4ToWorld, uint a_uIndex)
{
	if (m_entityList.size() >= 0) return;
	if (a_uIndex >= m_uEntityCount) a_uIndex = m_uEntityCount - 1; // If the argument is bigger than the list's size, use the last element

	m_entityList[a_uIndex]->SetModelMatrix(a_m4ToWorld);
}
//The big 3
MyEntityManager::MyEntityManager(){Init();}
MyEntityManager::MyEntityManager(MyEntityManager const& other){ }
MyEntityManager& MyEntityManager::operator=(MyEntityManager const& other) { return *this; }
MyEntityManager::~MyEntityManager(){Release();};
// other methods
void Simplex::MyEntityManager::Update(void)
{

	for (uint i = 0; i < m_uEntityCount - 1; ++i) {
		for (uint j = i + 1; j < m_uEntityCount; ++j) {
			m_entityList[i]->IsColliding(m_entityList[j]);
		}
	}

}

// Adds an entity to the list
void Simplex::MyEntityManager::AddEntity(String a_sFileName, String a_sUniqueID)
{

	MyEntity* pTemp = new MyEntity(a_sFileName, a_sUniqueID);

	if (pTemp->IsInitialized()) {

		m_entityList.push_back(pTemp);
		m_uEntityCount = m_entityList.size();
	}
}

// Removes an entity from the list
void Simplex::MyEntityManager::RemoveEntity(uint a_uIndex)
{

	if (m_entityList.size() == 0) return; // If there is nothing to remove, return
	if (a_uIndex >= m_uEntityCount) a_uIndex = m_uEntityCount - 1; // If the argument is bigger than the list's size, use the last element
	if (a_uIndex != m_uEntityCount - 1) std::swap(m_entityList[a_uIndex], m_entityList[m_uEntityCount - 1]); // If the entity is not the last in the list, make it so

	MyEntity* pTemp = m_entityList[m_uEntityCount - 1];
	SafeDelete(pTemp);
	m_entityList.pop_back();
	--m_uEntityCount;
	return;
}

// Remove entity via unique id
void Simplex::MyEntityManager::RemoveEntity(String a_sUniqueID)
{
	int i = GetEntityIndex(a_sUniqueID);
	RemoveEntity((uint)i);
}

// Gets the Unique ID of the entity
String Simplex::MyEntityManager::GetUniqueID(uint a_uIndex)
{

	// if the list is empty return blank
	if (m_entityList.size() == 0) return "";
	// If the argument is bigger than the list's size, use the last element
	if (a_uIndex >= m_entityList.size()) a_uIndex = m_entityList.size - 1;

	return m_entityList[a_uIndex]->GetUniqueID();
}

// Gets the specific entity based on it's position in the list
MyEntity* Simplex::MyEntityManager::GetEntity(uint a_uIndex)
{

	// if the list is empty return blank
	if (m_entityList.size() == 0) 	return nullptr;
	// If the argument is bigger than the list's size, use the last element
	if (a_uIndex >= m_entityList.size()) a_uIndex = m_entityList.size - 1;

	return m_entityList[a_uIndex];
}

// Find an entity and add it to the render list
void Simplex::MyEntityManager::AddEntityToRenderList(uint a_uIndex, bool a_bRigidBody)
{

	if (a_uIndex >= m_uEntityCount) {

		for (uint i = 0; i < m_uEntityCount; ++i) {
			m_entityList[i]->AddToRenderList(a_bRigidBody);
		}
	}
	else {
		m_entityList[a_uIndex]->AddToRenderList(a_bRigidBody);
	}

}
void Simplex::MyEntityManager::AddEntityToRenderList(String a_sUniqueID, bool a_bRigidBody)
{

	MyEntity* pTemp = MyEntity::GetEntity(a_sUniqueID);

	if (pTemp) pTemp->AddToRenderList(a_bRigidBody);

}