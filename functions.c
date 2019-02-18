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

	void  ent = getlocalvar("self");                // Calling entity.
	void  target = grapple_target(vTar, ent);       // Target entity.

	if (target)
	{
		// If caller's drawmethod is on, then
		// adjust offsets to caller's current scale.
		if (getdrawmethod(ent, "enabled") == 1)
		{
			offset_x = dc_kanga_adjust_to_scale_x(ent, offset_x);
			offset_y = dc_kanga_adjust_to_scale_y(ent, offset_y);
		}

		// Get binding property for spawn.
		void bind = get_entity_property(target, "bind");

		// Enable binding on each axis.
		set_bind_property(bind, "mode_x", openborconstant("BIND_MODE_TARGET"));
		set_bind_property(bind, "mode_y", openborconstant("BIND_MODE_TARGET"));
		set_bind_property(bind, "mode_z", openborconstant("BIND_MODE_TARGET"));

		// Set the binding offset.
		set_bind_property(bind, "offset_x", offset_x);
		set_bind_property(bind, "offset_y", offset_y);
		set_bind_property(bind, "offset_z", offset_z);

		// Set other binding properties.
		//set_bind_property(binding, "matching", openborconstant("BINDING_MATCHING_NONE"));
		set_bind_property(bind, "direction", iDir);
		set_bind_property(bind, "target", ent);

		set_bind_property(bind,"tag", 24);

		// Update bound entity's auto scaling.
		dc_kanga_z_position_autoscale(target);

		performattack(target, DEFPOSE, 1);
		changeentityproperty(target, "animpos", iFrame);

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