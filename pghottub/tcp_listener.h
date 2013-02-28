// Copyright (c) 2013 - Cody Cutrer

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "pghottub/listener.h"

namespace Mordor {
class IOManager;
class Socket;
}

namespace PgHotTub {

class HotTub;

class TcpListener : public Listener
{
public:
    TcpListener(Mordor::IOManager &ioManager, const std::string &interface,
        unsigned short port, HotTub &hotTub);

    void stop();

private:
    void acceptConnections(boost::shared_ptr<Mordor::Socket> socket);

private:
    HotTub &m_hotTub;
    std::vector<boost::shared_ptr<Mordor::Socket> > m_sockets;
};

}
