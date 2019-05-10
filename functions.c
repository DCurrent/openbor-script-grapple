#include "data/scripts/dc_grapple/config.h"


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