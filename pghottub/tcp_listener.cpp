// Copyright (c) 2013 - Cody Cutrer

#include <mordor/predef.h>

#include "pghottub/tcp_listener.h"

#include <mordor/iomanager.h>
#include <mordor/socket.h>
#include <mordor/streams/socket.h>

#include "pghottub/hot_tub.h"

using namespace Mordor;

namespace PgHotTub {

TcpListener::TcpListener(IOManager &ioManager, const std::string &interface,
    unsigned short port, HotTub &hotTub)
    : Listener(hotTub),
      m_hotTub(hotTub)
{
    std::vector<std::pair<Address::ptr, unsigned int> > addresses =
        Address::getInterfaceAddresses(interface);
    for (std::vector<std::pair<Address::ptr, unsigned int> >::iterator it =
        addresses.begin();
        it != addresses.end();
        ++it) {
        if (it->first->family() == AF_INET || it->first->family() == AF_INET6) {
            boost::static_pointer_cast<IPAddress>(it->first)->port(port);
            Socket::ptr s = it->first->createSocket(ioManager, SOCK_STREAM);
            s->setOption(SOL_SOCKET, SO_REUSEADDR, 1);
            s->bind(it->first);
            s->listen();
            m_sockets.push_back(s);
        }
    }
    for (std::vector<Socket::ptr>::iterator it = m_sockets.begin();
        it != m_sockets.end();
        ++it)
        ioManager.schedule(boost::bind(&TcpListener::acceptConnections, this, *it));
}

void
TcpListener::stop()
{
    for (std::vector<Socket::ptr>::iterator it = m_sockets.begin();
        it != m_sockets.end();
        ++it)
        (*it)->cancelAccept();
}

void
TcpListener::acceptConnections(Socket::ptr listenSocket)
{
        while (true) {
        Socket::ptr socket;
        try {
            socket = listenSocket->accept();
        } catch (OperationAbortedException &) {
            return;
        }
        Stream::ptr stream(new SocketStream(socket));
        m_hotTub.acceptConnection(stream);
    }
}

}
