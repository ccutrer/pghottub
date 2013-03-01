// Copyright (c) 2013 - Cody Cutrer

#include <mordor/predef.h>

#include "pghottub/connection.h"

#include <mordor/assert.h>
#include <mordor/streams/buffered.h>
#include <mordor/endian.h>

using namespace Mordor;

namespace PgHotTub {

Connection::Connection(HotTub &hotTub, Stream::ptr stream)
    : m_hotTub(hotTub)
{
    MORDOR_ASSERT(stream->supportsRead());
    MORDOR_ASSERT(stream->supportsWrite());
    MORDOR_ASSERT(!stream->supportsSeek());
    m_stream.reset(new BufferedStream(stream));
}

void
Connection::readV2Message(V2MessageType &type, Buffer &message)
{
    unsigned int length;
    m_stream->read(&length, 4u);
    length = byteswap(length);
    if (length < 8)
        MORDOR_THROW_EXCEPTION(MessageTooShort());

    m_stream->read(&type, 4u);
    type = byteswap(type);

    if (length > 8)
        m_stream->read(message, length - 8);
}

}
