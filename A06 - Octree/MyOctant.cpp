#include "MyOctant.h"

// Call this the first time you're making an octant
Simplex::MyOctant::MyOctant(uint a_nMaxLevel, uint a_nIdealEntityCount)
{

	// If this is the first Octant, this will be the root
	m_pRoot = this;

	// Store necessary variables
	m_uOctantCount++;
	m_uMaxLevel = a_nMaxLevel;
	m_uIdealEntityCount = a_nIdealEntityCount;

	m_pEntityMngr = MyEntityManager::GetInstance();

	// Bounds & Location
	for (uint i = 0; i < m_pEntityMngr->GetEntityCount(); ++i) {

		MyEntity* currentBlock = m_pEntityMngr->GetEntity(i);

		m_v3Center += currentBlock->GetRigidBody()->GetCenterGlobal();

		vector3 tempMin = currentBlock->GetRigidBody()->GetMinGlobal();
		vector3 tempMax = currentBlock->GetRigidBody()->GetMaxGlobal();

		// Find the min and max
		m_v3Min.x = glm::min(tempMin.x, m_v3Min.x);
		m_v3Min.y = glm::min(tempMin.y, m_v3Min.y);
		m_v3Min.z = glm::min(tempMin.z, m_v3Min.z);
		m_v3Max.x = glm::max(tempMax.x, m_v3Max.x);
		m_v3Max.y = glm::max(tempMax.y, m_v3Max.y);
		m_v3Max.z = glm::max(tempMax.z, m_v3Max.z);
	}

	// Assign the center
	m_v3Center /= m_pEntityMngr->GetEntityCount();
		
	m_pMeshMngr->AddWireCubeToRenderList(matrix4(m_v3Center.x, m_v3Center.y, m_v3Center.z, 1.0f) * GetSize(), C_YELLOW);

	// Array of 8 (or null) Children
	// References to its entities

}

Simplex::MyOctant::MyOctant(vector3 a_v3Center, float a_fSize)
{



}

Simplex::MyOctant::MyOctant(MyOctant const & other)
{
}

Simplex::MyOctant::~MyOctant(void)
{
	//SafeDelete(m_lChild[m_uID]);
}

void Simplex::MyOctant::Swap(MyOctant & other)
{
}

// Gets the Width
float Simplex::MyOctant::GetSize(void){return m_v3Max.x - m_v3Min.x;}

// Finds the center of this octant
Simplex::vector3 Simplex::MyOctant::GetCenterGlobal(void){return m_v3Center;}

// Finds the min point of this octant
Simplex::vector3 Simplex::MyOctant::GetMinGlobal(void){return m_v3Min;}

// Finds the max point of this octant
Simplex::vector3 Simplex::MyOctant::GetMaxGlobal(void){return m_v3Max;}

bool Simplex::MyOctant::IsColliding(uint a_uRBIndex)
{

	return false;
}

void Simplex::MyOctant::Display(uint a_nIndex, vector3 a_v3Color)
{
}

void Simplex::MyOctant::Display(vector3 a_v3Color)
{
}

void Simplex::MyOctant::DisplayLeafs(vector3 a_v3Color)
{
}

void Simplex::MyOctant::ClearEntityList(void)
{
}

void Simplex::MyOctant::Subdivide(void)
{
	m_pChild[0] = &Simplex::MyOctant::MyOctant(m_v3Center / vector3(2.0f, 2.0f, 2.0f), m_v3Max.x - m_v3Min.x / 2.0f);
	m_pChild[1] = &Simplex::MyOctant::MyOctant(m_v3Center / vector3(2.0f, 2.0f, 2.0f), m_v3Max.x - m_v3Min.x / 2.0f); // NOT DONE
	m_pChild[2] = &Simplex::MyOctant::MyOctant(m_v3Center / vector3(2.0f, 2.0f, 2.0f), m_v3Max.x - m_v3Min.x / 2.0f); // NOT DONE
	m_pChild[3] = &Simplex::MyOctant::MyOctant(m_v3Center / vector3(2.0f, 2.0f, 2.0f), m_v3Max.x - m_v3Min.x / 2.0f); // NOT DONE

	m_pChild[4] = &Simplex::MyOctant::MyOctant(m_v3Center / vector3(2.0f, 2.0f, 2.0f), m_v3Max.x - m_v3Min.x / 2.0f); // NOT DONE
	m_pChild[5] = &Simplex::MyOctant::MyOctant(m_v3Center / vector3(2.0f, 2.0f, 2.0f), m_v3Max.x - m_v3Min.x / 2.0f); // NOT DONE
	m_pChild[6] = &Simplex::MyOctant::MyOctant(m_v3Center / vector3(2.0f, 2.0f, 2.0f), m_v3Max.x - m_v3Min.x / 2.0f); // NOT DONE
	m_pChild[7] = &Simplex::MyOctant::MyOctant(m_v3Center / vector3(2.0f, 2.0f, 2.0f), m_v3Max.x - m_v3Min.x / 2.0f); // NOT DONE

}

void Simplex::MyOctant::AddObject(String uniqueID)
{

}

Simplex::MyOctant * Simplex::MyOctant::GetChild(uint a_nChild)
{
	return nullptr;
}

Simplex::MyOctant * Simplex::MyOctant::GetParent(void)
{
	return nullptr;
}

bool Simplex::MyOctant::IsLeaf(void)
{
	return false;
}

bool Simplex::MyOctant::ContainsMoreThan(uint a_nEntities)
{
	return false;
}

void Simplex::MyOctant::KillBranches(void)
{
}

void Simplex::MyOctant::ConstructTree(uint a_nMaxLevel)
{
}

void Simplex::MyOctant::AssignIDtoEntity(void)
{
}

Simplex::uint Simplex::MyOctant::GetOctantCount(void)
{
	return uint();
}

void Simplex::MyOctant::Release(void)
{
}

void Simplex::MyOctant::Init(void)
{
}

void Simplex::MyOctant::ConstructList(void)
{
}


