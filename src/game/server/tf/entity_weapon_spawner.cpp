//====== Copyright � 1996-2005, Valve Corporation, All rights reserved. =======//
//
// Purpose: CTF AmmoPack.
//
//=============================================================================//

#include "cbase.h"
#include "items.h"
#include "tf_gamerules.h"
#include "tf_shareddefs.h"
#include "tf_player.h"
#include "tf_team.h"
#include "engine/IEngineSound.h"
#include "entity_weapon_spawner.h"
#include "takedamageinfo.h"

//=============================================================================
//
// CTF AmmoPack defines.
//

#define TF_WEAPON_PICKUP_SOUND		"AmmoPack.Touch"
#define TF_WEAPON_MODEL				"models/weapons/w_models/w_scattergun.mdl"
#define TF_WEAPON_NAME				"tf_weapon_scattergun"

//-----------------------------------------------------------------------------
// Purpose: Spawn function for the ammopack
//-----------------------------------------------------------------------------


BEGIN_DATADESC( CWeaponSpawner )

// Inputs.
DEFINE_KEYFIELD( m_iszWeaponName, FIELD_STRING, "weaponname" ),
DEFINE_KEYFIELD( m_iszWeaponModel, FIELD_STRING, "weaponmodel" ),

END_DATADESC()

LINK_ENTITY_TO_CLASS( dm_weapon_spawner, CWeaponSpawner );

void CWeaponSpawner::Spawn( void )
{
	Precache();
	SetModel( STRING(m_iszWeaponModel) );

	BaseClass::Spawn();
}
//-----------------------------------------------------------------------------
// Purpose: Precache function for the ammopack
//-----------------------------------------------------------------------------
void CWeaponSpawner::Precache( void )
{
	PrecacheModel( STRING(m_iszWeaponModel) );
	PrecacheScriptSound( TF_WEAPON_PICKUP_SOUND );
}

//-----------------------------------------------------------------------------
// Purpose: MyTouch function for the ammopack
//-----------------------------------------------------------------------------
bool CWeaponSpawner::MyTouch( CBasePlayer *pPlayer )
{
	bool bSuccess = false;

	if ( ValidTouch( pPlayer ) )
	{
		CTFPlayer *pTFPlayer = ToTFPlayer( pPlayer );
		if ( !pTFPlayer )
			return false;
//		CTFWeaponBase *pWeapon = ToTFPlayer( pPlayer )->GetActiveTFWeapon();
		bSuccess = true;

		// did we give them anything?
		if ( bSuccess )
		{
		
			CSingleUserRecipientFilter filter( pPlayer );
			EmitSound( filter, entindex(), TF_WEAPON_PICKUP_SOUND );

			pPlayer->GiveNamedItem( STRING(m_iszWeaponName) );
		}
	}
	return bSuccess;

}