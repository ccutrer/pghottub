// Copyright (c) 2013 - Cody Cutrer

#include <set>
#include <vector>

#include <boost/shared_ptr.hpp>

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
    HotTub(Mordor::Scheduler &scheduler);

    void stop();

    void addListener(Listener &listener);

    void acceptConnection(boost::shared_ptr<Mordor::Stream> stream);
private:
    Mordor::Scheduler &m_scheduler;
    std::vector<Listener *> m_listeners;
    std::set<boost::shared_ptr<Client> > m_clients;
};

}
