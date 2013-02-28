// Copyright (c) 2013 - Cody Cutrer

#include <mordor/predef.h>

#include "pghottub/listener.h"

#include "pghottub/hot_tub.h"

namespace PgHotTub {

Listener::Listener(HotTub &hotTub)
    : m_hotTub(hotTub)
{
    hotTub.addListener(*this);
}

}
