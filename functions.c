#include "data/scripts/dc_grapple/config.h"


// Temp replacement for targ0001
void grapple_target(void vTarget, void vSelf)
{
	if (!vTarget) { return vSelf; }   //Return "self".	
	else if (vTarget == 1) { return getentityproperty(vSelf, "opponent"); }   //Last entity vSelf interacted with.
	else if (vTarget == 2) { return getentityproperty(vSelf, "grabbing"); }   //Entity vSelf is holding.
	else if (vTarget == 3) { return findtarget(vSelf); }   //vSelf's Nearest opponent.		
	else if (vTarget == 4) { return getentityproperty(vSelf, "parent"); }   //vSelf's parrent.
	else if (vTarget == 5) { return getentityvar(vSelf, BIND); }   //Bound entity.
	else if (vTarget == 6) { return getentityvar(vSelf, BINDHE); }   //Bound hit effect entity.
	else { return vTarget; }   //Target was passed directly, return variable.
}

void bbbbind0002(float fX, float fY, float fZ) {

	/*
	bind0002
	Damon Vaughn Caskey
	06/20/2007
	Syncronizes target with caller's location without binding.

	iSync:      Sync target setting (see targ0001 function).
	fX, fY, fZ: Distance adjustment (from caller).
	iDirection: Direction adjustment (see loc001 function).
	*/

	void  vSelf = getlocalvar("self");                     //Calling entity.
	void  vTarget = getentityproperty(vSelf, "opponent");    //Current opponent.
	int   iDir = getentityproperty(vTarget, "direction"); //Current direction.
	float fRatio = getentityvar(vSelf, ADSCALER);         //Caller's current scale ratio.

	//If any incoming values are NULL(), set to 0.
	if (!fX) fX = 0;
	if (!fY) fY = 0;
	if (!fZ) fZ = 0;

	if (iDir == 1) { fX = -fX; }   //Reverse horizontal adjustment if facing left.

	fX = (fX * fRatio) + getentityproperty(vSelf, "x"); //Apply requested X offset to X location and apply zoom scale.
	fY = (fY * fRatio) + getentityproperty(vSelf, "a"); //Apply requested Y offset to Y location and apply zoom scale.
	fZ = fZ + getentityproperty(vSelf, "z");            //Apply requested Z offset.

	changeentityproperty(vTarget, "position", fX, fZ, fY);
}

// Caskey, Damon V.
// 2018-08-28
//
// If localvars are not defined, insert defaults.
void dc_grapple_set_defaults()
{
	void base;
	void target;

	int offset_x;
	int offset_y;
	int offset_z;

	// Base.
	base = dc_grapple_get_base();

	if (base)
	{
		base = getlocalvar("self");
	}

	// Target.
	target = dc_grapple_get_target();

	if (!target)
	{
		target = get_entity_property(base, "opponent");

		// Still no target? Better exit.
		if (!target)
		{
			shutdown(0, "dc_grapple_set_defaults: Target is empty, unable to find opponent. Make sure you set up a target.");
		}

		dc_grapple_set_target(target);
	}

	// Offsets.
	offset_x = dc_grapple_get_offset_x();

	if (!offset_x)
	{
		dc_grapple_set_offset_x(0);
	}

	offset_y = dc_grapple_get_offset_y();

	if (!offset_y)
	{
		dc_grapple_set_offset_y(0);
	}

	offset_z = dc_grapple_get_offset_z();

	if (!offset_z)
	{
		dc_grapple_set_offset_z(0);
	}
}

void old_bind0002(float fX, float fY, float fZ) {
	   
	/*
	bind0002
	Damon Vaughn Caskey
	06/20/2007
	Syncronizes target with caller's location without binding.

	iSync:      Sync target setting (see targ0001 function).
	fX, fY, fZ: Distance adjustment (from caller).
	iDirection: Direction adjustment (see loc001 function).
	*/

	void  vSelf = getlocalvar("self");                     //Calling entity.
	void  vTarget = getentityproperty(vSelf, "opponent");    //Current opponent.
	int   iDir = getentityproperty(vTarget, "direction"); //Current direction.
	float fRatio = getentityvar(vSelf, ADSCALER);         //Caller's current scale ratio.

	//If any incoming values are NULL(), set to 0.
	if (!fX) fX = 0;
	if (!fY) fY = 0;
	if (!fZ) fZ = 0;

	if (iDir == 1) { fX = -fX; }   //Reverse horizontal adjustment if facing left.

	fX = (fX * fRatio) + getentityproperty(vSelf, "x"); //Apply requested X offset to X location and apply zoom scale.
	fY = (fY * fRatio) + getentityproperty(vSelf, "a"); //Apply requested Y offset to Y location and apply zoom scale.
	fZ = fZ + getentityproperty(vSelf, "z");            //Apply requested Z offset.

	changeentityproperty(vTarget, "position", fX, fZ, fY);
}

void bind0010(void vTar, int offset_x, int offset_y, int offset_z, int iDir, int iFrame) {

	/*
	bind0010
	Damon Vaughn Caskey
	12/31/2008
	Bind target to caller and set bound entity's animation frame.

	vTar:       Target entity. See targ0001 function.
	offset_x, offset_y, offset_z: Location offsets.
	iDir:       Direction - 0 = no change, 1 = same target, -1 = opposite of target,  2 = right, -2 = left.
	vAni:       Animation for bound entity.
	*/

	void  vSelf = getlocalvar("self");                //Calling entity.
	void  vTarget = grapple_target(vTar, vSelf);               //Target entity.

	if (vTarget)
	{
		// If caller's drawmethod is on, then
		// adjust offsets to caller's current scale.
		if (getdrawmethod(vSelf, "enabled") == 1)
		{
			offset_x = dc_kanga_adjust_to_scale_x(vSelf, offset_x);
			offset_y = dc_kanga_adjust_to_scale_y(vSelf, offset_y);
		}

		// Get binding property for spawn.
		void binding = get_entity_property(vTarget, "binding");

		// Get binding toggle and enable flags.
		void binding_enable = get_binding_property(binding, "positioning");
		void binding_axis = get_binding_property(binding, "offset");

		// Enable binding on each axis.
		set_axis_principal_int_property(binding_enable, "x", openborconstant("BINDING_POSITIONING_TARGET"));
		set_axis_principal_int_property(binding_enable, "y", openborconstant("BINDING_POSITIONING_TARGET"));
		set_axis_principal_int_property(binding_enable, "z", openborconstant("BINDING_POSITIONING_TARGET"));

		// Set the binding offset.
		set_axis_principal_int_property(binding_axis, "x", offset_x);
		set_axis_principal_int_property(binding_axis, "y", offset_y);
		set_axis_principal_int_property(binding_axis, "z", offset_z);

		// Set other binding properties.
		//set_binding_property(binding, "matching", openborconstant("BINDING_MATCHING_NONE"));
		set_binding_property(binding, "direction", iDir);
		set_binding_property(binding, "target", vSelf);

		set_binding_property(binding,"tag", 24);

		// Update bound entity's auto scaling.
		dc_kanga_z_position_autoscale(vTarget);

		performattack(vTarget, DEFPOSE, 1);
		changeentityproperty(vTarget, "animpos", iFrame);

		/*
		Reset engine's lasthit variants. Otherwise, target will assume sweep values when
		knocked down if last normal attack hit low.
		*/
		changeopenborvariant("lasthitx", 0);
		changeopenborvariant("lasthita", 0);
		changeopenborvariant("lasthitz", 0);
		changeopenborvariant("lasthitt", 0);
	}
}