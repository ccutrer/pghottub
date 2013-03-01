// Copyright (c) 2013 - Cody Cutrer

#include <set>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <openssl/ssl.h>

namespace Mordor {
class Scheduler;
class Stream;
}

namespace PgHotTub {

class Client;
class Listener;

class HotTub
{
public:
    HotTub(Mordor::Scheduler &scheduler, SSL_CTX *sslCtx = NULL);

    void stop();

    void addListener(Listener &listener);

    void acceptConnection(boost::shared_ptr<Mordor::Stream> stream);

    SSL_CTX *sslCtx();

private:
    Mordor::Scheduler &m_scheduler;
    std::vector<Listener *> m_listeners;
    std::set<boost::shared_ptr<Client> > m_clients;
    SSL_CTX *m_sslCtx;
};

}
