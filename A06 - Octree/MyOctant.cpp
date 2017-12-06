#include "MyOctant.h"

Simplex::MyOctant::MyOctant(uint a_nMaxLevel, uint a_nIdealEntityCount)
{

	// If this is the first Octant, this will be the root
	if (m_lChild.size() == 0)	m_pRoot = this;

	// Assign the id of this Octant
	m_uID = m_lChild.size();

	// If there are still subdivisions to make, make them
	if (a_nMaxLevel < m_uOctantCount) {

		// Append the lChild list with this octant
		m_lChild[m_lChild.size()] = this;

		// Recursively call the creation of an octant
		MyOctant::MyOctant(a_nMaxLevel, a_nIdealEntityCount);
		for (uint i = 0; i < m_uChildren; ++i) {
			
		}
	}

}

Simplex::MyOctant::MyOctant(vector3 a_v3Center, float a_fSize)
{



}

Simplex::MyOctant::MyOctant(MyOctant const & other)
{
}

Simplex::MyOctant::~MyOctant(void)
{
	SafeDelete(m_lChild[m_uID]);
}

void Simplex::MyOctant::Swap(MyOctant & other)
{
}

float Simplex::MyOctant::GetSize(void)
{
	return 0.0f;
}

// Finds the center of this octant
Simplex::vector3 Simplex::MyOctant::GetCenterGlobal(void)
{
	return m_v3Center;
}

// Finds the min point of this octant
Simplex::vector3 Simplex::MyOctant::GetMinGlobal(void)
{
	return m_v3Min;
}

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


