// Copyright (c) 2013 - Cody Cutrer

#include <boost/noncopyable.hpp>

#include <mordor/exception.h>

namespace Mordor {
struct Buffer;
class Stream;
}

namespace PgHotTub {

class Connection : boost::noncopyable
{
public:
    struct MessageTooShort : virtual Mordor::Exception {};

protected:
    enum V2MessageType
    {
        SSL_REQUEST         = 80877103,
        STARTUP_REQUEST_V2  = 0x00020000,
        STARTUP_REQUEST_V3  = 0x00030000
    };

    enum V3MessageType
    {
    };

protected:
    Connection(boost::shared_ptr<Mordor::Stream> stream);

    void readV2Message(V2MessageType &type, Mordor::Buffer &message);
    void readV3Message(V3MessageType &type, Mordor::Buffer &message);

protected:
    boost::shared_ptr<Mordor::Stream> m_stream;
};

}
