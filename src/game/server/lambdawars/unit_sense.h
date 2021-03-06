//====== Copyright � Sandern Corporation, All rights reserved. ===========//
//
// Purpose:	
//
//=============================================================================//

#ifndef UNITSENSE_H
#define UNITSENSE_H

#ifdef _WIN32
#pragma once
#endif

#include "unit_component.h"

class CFuncUnit;

// Sensing class
class UnitBaseSense : public UnitComponent
{
public:
	friend class CUnitBase;

#ifdef ENABLE_PYTHON
	UnitBaseSense( boost::python::object outer );
#endif // ENABLE_PYTHON

	void Enable();
	void Disable();
	bool IsEnabled();

	void PerformSensing();
	void ForcePerformSensing();
	void Look( int iDistance );

	bool TestEntity( CBaseEntity *pEntity );
	bool TestUnit( CUnitBase *pUnit );
	bool TestFuncUnit( CFuncUnit *pUnit );

	void SetUseLimitedViewCone( bool bUseCone );
	void SetViewCone( float fCone );

	void SetTestLOS( bool bTestLOS );
	bool GetTestLOS();

	int CountSeen();
	int CountSeenEnemy();
	int CountSeenOther();
	CBaseEntity *GetEnemy( int idx );
	CBaseEntity *GetOther( int idx );
	bool HasEnemy( CBaseEntity *pEnemy );
	bool HasOther( CBaseEntity *pOther );

#ifdef ENABLE_PYTHON
	boost::python::object PyGetEnemy( int idx );
	boost::python::object PyGetOther( int idx );

	boost::python::list PyGetEnemies( const char *unittype = NULL );
	boost::python::list PyGetOthers( const char *unittype = NULL );

	bool AddEnemyInRangeCallback( boost::python::object callback, int range, float frequency );
	bool RemoveEnemyInRangeCallback( boost::python::object callback, int range = -1 );
#endif // ENABLE_PYTHON

	int CountEnemiesInRange( float range );
	int CountOthersInRange( float range );

	CBaseEntity *GetNearestOther();
	CBaseEntity *GetNearestEnemy();
	CBaseEntity *GetNearestFriendly();
	CBaseEntity *GetNearestAttackedFriendly();

private:
	int 			LookForUnits( int iDistance );
	void			UpdateRememberedSeen();

public:
	float m_fSenseDistance;
	float m_fSenseRate;

private:
	bool m_bEnabled;

	struct SeenObject_t {
		EHANDLE entity;
		float distancesqr;
	};
	CUtlVector<SeenObject_t> m_SeenEnemies;
	CUtlVector<SeenObject_t> m_SeenOther;

	// Cache info about some units while sensing
	EHANDLE m_hNearestEnemy;
	EHANDLE m_hNearestFriendly;
	EHANDLE m_hNearestAttackedFriendly;

	bool m_bUseLimitedViewCone;
	float m_fViewCone;
	float m_fNextSenseTime;
	bool m_bTestLOS;

#ifdef ENABLE_PYTHON
	struct RangeCallback_t {
		boost::python::object callback;
		int range; 
		float frequency;
		float nextchecktime;
	};
	CUtlVector<RangeCallback_t> m_Callbacks;
#endif // ENABLE_PYTHON
};

// Inlines
inline void UnitBaseSense::Enable()
{
	m_bEnabled = true;
}

inline void UnitBaseSense::Disable()
{
	m_bEnabled = false;
}

inline bool UnitBaseSense::IsEnabled()
{
	return m_bEnabled;
}

inline void UnitBaseSense::SetUseLimitedViewCone( bool bUseCone )
{
	m_bUseLimitedViewCone = bUseCone;
}

inline void UnitBaseSense::SetViewCone( float fCone )
{
	m_fViewCone = fCone;
}

inline void UnitBaseSense::SetTestLOS( bool bTestLOS )
{
	m_bTestLOS = bTestLOS;
}

inline bool UnitBaseSense::GetTestLOS()
{
	return m_bTestLOS;
}


inline int UnitBaseSense::CountSeen()
{
	return m_SeenEnemies.Count() + m_SeenOther.Count();
}

inline int UnitBaseSense::CountSeenEnemy()
{
	return m_SeenEnemies.Count();
}

inline int UnitBaseSense::CountSeenOther()
{
	return m_SeenOther.Count();
}

inline CBaseEntity *UnitBaseSense::GetEnemy( int idx )
{
	if( !m_SeenEnemies.IsValidIndex(idx) )
		return NULL;
	return m_SeenEnemies.Element(idx).entity;
}

inline bool UnitBaseSense::HasEnemy( CBaseEntity *pEnemy )
{
	for( int i = 0; i < m_SeenEnemies.Count(); i++ ) 
	{
		if( m_SeenEnemies.Element(i).entity == pEnemy )
			return true;
	}
	return false;
}

inline bool UnitBaseSense::HasOther( CBaseEntity *pOther )
{
	for( int i = 0; i < m_SeenOther.Count(); i++ ) 
	{
		if( m_SeenOther.Element(i).entity == pOther )
			return true;
	}
	return false;
}

inline CBaseEntity *UnitBaseSense::GetNearestEnemy()
{
	return m_hNearestEnemy;
}

inline CBaseEntity *UnitBaseSense::GetNearestFriendly()
{
	return m_hNearestFriendly;
}

inline CBaseEntity *UnitBaseSense::GetNearestAttackedFriendly()
{
	return m_hNearestAttackedFriendly;
}

inline CBaseEntity *UnitBaseSense::GetOther( int idx )
{
	if( !m_SeenOther.IsValidIndex(idx) )
		return NULL;
	return m_SeenOther.Element(idx).entity;
}

#ifdef ENABLE_PYTHON
inline boost::python::object UnitBaseSense::PyGetEnemy( int idx )
{
	CBaseEntity *pEnt = GetEnemy(idx);
	return pEnt ? pEnt->GetPyHandle() : boost::python::object();
}

inline boost::python::object UnitBaseSense::PyGetOther( int idx )
{
	CBaseEntity *pEnt = GetOther(idx);
	return pEnt ? pEnt->GetPyHandle() : boost::python::object();
}
#endif // ENABLE_PYTHON

#endif // UNITSENSE_H
