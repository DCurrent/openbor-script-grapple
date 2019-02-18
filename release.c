#include "data/scripts/dc_grapple/config.h"

// Caskey, Damon V.
// 2018-08-27
//
// Release all of the target entity's grappled
// targets. Call this when the target is damaged
// or gets interrupted some way before it can finish
// a grapple move.
int dc_grapple_release_all(void target)
{
	int i;					// Loop cursor.
	int entity_count;		// Entites on screen.
	int entity_exists;		// Entity cursor is not a dangling pointer.
	void entity_cursor;		// Entity in loop.
	int drop;				// Falling state.
	void bind;				// Binding property.
	void bind_target;		// 
	int animation_current;
	int release_count;		// How many entities have been released?

	release_count = 0;
	entity_count = openborvariant("count_entities");

	// Loop through entity collection.
	for (i = 0; i < entity_count; i++)
	{
		// Get entity cursor for this loop increment.
		entity_cursor = getentity(i);

		// Make sure we got a valid target pointer.
		if (!entity_cursor)
		{
			continue;
		}

		// Make sure the entity exists in play. We perform this
		// check because it's possible for an entity to be
		// removed but its pointer is still valid.
		entity_exists = getentityproperty(entity_cursor, "exists");

		if (!entity_exists)
		{
			continue;
		}

		// In a grappled pose?
		animation_current = get_entity_property(entity_cursor, "animation_id");

		if (animation_current != DEFPOSE)
		{
			continue;
		}

		// Bound to function's target?
		bind = get_entity_property(entity_cursor, "bind");
		bind_target = get_bind_property(bind, "target");

		if (bind_target != target)
		{
			continue;
		}

		// Reelase bind and knock entity down to ensure
		// it is "reset".
		set_bind_property(bind, "target", NULL());
		damageentity(entity_cursor, target, DC_GRAPPLE_RESET_FORCE, DC_GRAPPLE_RESET_DROP, openborconstant("ATK_NORMAL"));

		// Increment reelase count;
		release_count++;
	}

	return release_count;
}
