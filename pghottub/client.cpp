// Copyright (c) 2013 - Cody Cutrer

#include <mordor/predef.h>

#include "pghottub/client.h"

#include <map>

#include <mordor/endian.h>
#include <mordor/log.h>
#include <mordor/streams/buffer.h>
#include <mordor/streams/buffered.h>
#include <mordor/streams/ssl.h>
#include <mordor/streams/stream.h>

#include "pghottub/hot_tub.h"

using namespace Mordor;

static Logger::ptr g_log = Log::lookup("pghottub:client");

namespace PgHotTub {

Client::Client(HotTub &hotTub, Stream::ptr stream)
    : Connection(hotTub, stream)
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

        if (m_hotTub.sslCtx()) {
            m_stream->write("S", 1u);
            m_stream->flush();

            BufferedStream::ptr bufferedStream = boost::dynamic_pointer_cast<BufferedStream>(m_stream);
            // optimize the buffering on top of the socket for SSL packets
            bufferedStream->allowPartialReads(true);
            bufferedStream->flushMultiplesOfBuffer(true);
            bufferedStream->bufferSize(16384);

            SSLStream::ptr sslStream(new SSLStream(m_stream, false, true, m_hotTub.sslCtx()));
            sslStream->accept();
            sslStream->flush();
            m_stream.reset(new BufferedStream(sslStream));
        } else {
            m_stream->write("N", 1u);
            m_stream->flush();
        }

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
