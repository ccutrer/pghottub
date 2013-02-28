// Copyright (c) 2013 - Cody Cutrer

#include <mordor/predef.h>

#include "pghottub/hot_tub.h"

#include <mordor/streams/stream.h>

#include "pghottub/listener.h"

using namespace Mordor;

namespace PgHotTub {

void
HotTub::stop()
{
    for(std::vector<Listener *>::iterator it = m_listeners.begin();
        it != m_listeners.end();
        ++it)
        (*it)->stop();
}

void
HotTub::addListener(Listener &listener)
{
    m_listeners.push_back(&listener);
}

void
HotTub::acceptConnection(Stream::ptr stream)
{
}

}
