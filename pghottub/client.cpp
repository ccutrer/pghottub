// Copyright (c) 2013 - Cody Cutrer

#include <mordor/predef.h>

#include "pghottub/client.h"

#include <map>

#include <mordor/assert.h>
#include <mordor/endian.h>
#include <mordor/log.h>
#include <mordor/streams/buffered.h>
#include <mordor/streams/limited.h>
#include <mordor/streams/stream.h>

#include "postgres.h"

using namespace Mordor;

static Logger::ptr g_log = Log::lookup("pghottub:client");

namespace PgHotTub {

Client::Client(Stream::ptr stream)
{
    MORDOR_ASSERT(stream->supportsRead());
    MORDOR_ASSERT(stream->supportsWrite());
    MORDOR_ASSERT(!stream->supportsSeek());
    m_stream.reset(new BufferedStream(stream));
}

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
    unsigned int length;
    m_stream->read(&length, 4u);
    length = byteswap(length);
    // TODO: disconnect unless length >= 8

    unsigned int protocolVersion;
    m_stream->read(&protocolVersion, 4u);
    protocolVersion = byteswap(protocolVersion);

    if (protocolVersion == SSL_REQUEST) {
        // TODO: wrap in SSL
        m_stream->write("N", 1u);
        m_stream->flush();
        startup();
        return;
    }
    if (protocolVersion != 0x00030000) {
        // TODO: disconnect unless version 3
    }

    std::map<std::string, std::string> parameters;
    while (true) {
        std::string name = m_stream->getDelimited('\0');
        if (name.length() == 1)
            break;
        name.resize(name.size() - 1);
        std::string value = m_stream->getDelimited('\0', false, false);

        parameters[name] = value;
    }

    // TODO: check stream is at EOF
}

}
