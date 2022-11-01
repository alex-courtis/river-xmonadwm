#ifndef LISTENERS_H
#define LISTENERS_H

// registration
const struct wl_registry_listener *registry_listener(void);

// events
const struct river_layout_v3_listener *river_layout_listener(void);

#endif // LISTENERS_H

