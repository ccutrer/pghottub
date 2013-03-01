// Copyright (c) 2013 - Cody Cutrer

#include <mordor/predef.h>

#include "pghottub/hot_tub.h"

#include <mordor/scheduler.h>
#include <mordor/streams/stream.h>

#include "pghottub/client.h"
#include "pghottub/listener.h"

using namespace Mordor;

namespace PgHotTub {

HotTub::HotTub(Scheduler &scheduler, SSL_CTX *sslCtx)
    : m_scheduler(scheduler),
      m_sslCtx(sslCtx)
{}

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
    Client::ptr client(new Client(*this, stream));
    m_clients.insert(client);
    m_scheduler.schedule(boost::bind(&Client::run, client));
}

SSL_CTX *
HotTub::sslCtx()
{
    return m_sslCtx;
}

}
