
// Dependencies - If you don't have these libraries, grab
// them from https://github.com/DCurrent.

#include "data/scripts/dc_kanga/main.c"

// From old bind0010
#include "data/scripts/vars/anims.h"
#include "data/scripts/vars/entity.h"
#include "data/scripts/vars/frames.h"
// -From old bind0010

#ifndef DC_GRAPPLE

#define DC_GRAPPLE 1

#define DC_GRAPPLE_RESET_DROP	100			// Knockdown applied to entites auto released from bind.
#define DC_GRAPPLE_RESET_FORCE	0			// Damage force applied to entites auto released from bind.


// Function macros.

// Offsets.
#define dc_grapple_get_offset_x getlocalvar("dcgrap_0")
#define dc_grapple_get_offset_y getlocalvar("dcgrap_1")
#define dc_grapple_get_offset_z getlocalvar("dcgrap_2")

#define dc_grapple_set_offset_x(value) setlocalvar("dcgrap_0", value)
#define dc_grapple_set_offset_y(value) setlocalvar("dcgrap_1", value)
#define dc_grapple_set_offset_z(value) setlocalvar("dcgrap_2", value)

// Base entity. Usually the one executing script.
#define dc_grapple_get_base getlocalvar("dcgrap_3")
#define dc_grapple_set_base(value) setlocalvar("dcgrap_3", value)

// Entity to bind, sync, etc. with base.
#define dc_grapple_get_target getlocalvar("dcgrap_4")
#define dc_grapple_set_target(value) setlocalvar("dcgrap_4", value)


#endif // !DC_GRAPPLE



