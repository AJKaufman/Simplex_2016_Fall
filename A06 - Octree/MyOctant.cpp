#include "MyOctant.h"

Simplex::MyOctant::MyOctant(uint a_nMaxLevel, uint a_nIdealEntityCount)
{
	if (a_nMaxLevel - 1 > 0) {
		MyOctant::MyOctant(a_nMaxLevel - 1, a_nIdealEntityCount);
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
	//SafeDelete(m_uID&);
}

void Simplex::MyOctant::Swap(MyOctant & other)
{
}

float Simplex::MyOctant::GetSize(void)
{
	return 0.0f;
}

vector3 Simplex::MyOctant::GetCenterGlobal(void)
{
	return vector3();
}

vector3 Simplex::MyOctant::GetMinGlobal(void)
{
	return vector3();
}

vector3 Simplex::MyOctant::GetMaxGlobal(void)
{
	return vector3();
}

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
	m_pChild[0] = Simplex::MyOctant::MyOctant(m_v3Center / vector3(2.0f, 2.0f, 2.0f), m_v3Max.x - m_v3Min.x / 2.0f);
	m_pChild[1] = Simplex::MyOctant::MyOctant(m_v3Center / vector3(2.0f, 2.0f, 2.0f), m_v3Max.x - m_v3Min.x / 2.0f);
	m_pChild[2] = Simplex::MyOctant::MyOctant(m_v3Center / vector3(2.0f, 2.0f, 2.0f), m_v3Max.x - m_v3Min.x / 2.0f);
	m_pChild[3] = Simplex::MyOctant::MyOctant(m_v3Center / vector3(2.0f, 2.0f, 2.0f), m_v3Max.x - m_v3Min.x / 2.0f);

	m_pChild[4] = Simplex::MyOctant::MyOctant(m_v3Center / vector3(2.0f, 2.0f, 2.0f), m_v3Max.x - m_v3Min.x / 2.0f);
	m_pChild[5] = Simplex::MyOctant::MyOctant(m_v3Center / vector3(2.0f, 2.0f, 2.0f), m_v3Max.x - m_v3Min.x / 2.0f);
	m_pChild[6] = Simplex::MyOctant::MyOctant(m_v3Center / vector3(2.0f, 2.0f, 2.0f), m_v3Max.x - m_v3Min.x / 2.0f);
	m_pChild[7] = Simplex::MyOctant::MyOctant(m_v3Center / vector3(2.0f, 2.0f, 2.0f), m_v3Max.x - m_v3Min.x / 2.0f);

}

MyOctant * Simplex::MyOctant::GetChild(uint a_nChild)
{
	return nullptr;
}

MyOctant * Simplex::MyOctant::GetParent(void)
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

uint Simplex::MyOctant::GetOctantCount(void)
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


