// Copyright (c) 2013 - Cody Cutrer

#include <mordor/predef.h>

#include "pghottub/client.h"

#include <map>

#include <mordor/endian.h>
#include <mordor/log.h>
#include <mordor/streams/buffer.h>
#include <mordor/streams/stream.h>

using namespace Mordor;

static Logger::ptr g_log = Log::lookup("pghottub:client");

namespace PgHotTub {

Client::Client(Stream::ptr stream)
    : Connection(stream)
{}

void
Client::run()
{
    try {
        startup();
    } catch(UnexpectedEofException &) {
        // TODO: disconnect, and notify the HotTub
    }
}

void
Client::startup()
{
    V2MessageType type;
    Buffer message;

    readV2Message(type, message);

    if (type == SSL_REQUEST) {
        if (message.readAvailable() != 0)
            MORDOR_THROW_EXCEPTION(InvalidProtocolException());

        // TODO: wrap in SSL
        m_stream->write("N", 1u);
        m_stream->flush();
        readV2Message(type, message);
    }

    if (type != STARTUP_REQUEST_V3)
        MORDOR_THROW_EXCEPTION(InvalidProtocolException());

    std::map<std::string, std::string> parameters;
    while (true) {
        std::string name = message.getDelimited('\0');
        if (name.length() == 1)
            break;
        name.resize(name.size() - 1);
        std::string value = message.getDelimited('\0', false, false);

        parameters[name] = value;
    }

    if (message.readAvailable() != 0)
        MORDOR_THROW_EXCEPTION(InvalidProtocolException());
}

}
