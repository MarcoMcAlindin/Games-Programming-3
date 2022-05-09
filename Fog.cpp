#include "Fog.h"

Fog::Fog()
{

}

Fog* Fog::m_fogInstance = nullptr;

Fog* Fog::GetInstance()
{
	if (m_fogInstance == nullptr) 
	{
		m_fogInstance = new Fog();
	}
	return m_fogInstance;
}