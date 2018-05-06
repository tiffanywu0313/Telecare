/** @file */

#ifndef CAPABILITIES_H
#define CAPABILITIES_H

#include "config.h"

struct otc_capabilities {
    otc_bool_t force_disconnect;
    otc_bool_t force_unpublish;
    otc_bool_t publish;
    otc_bool_t subscribe;
};

#endif // CAPABILITIES_H
