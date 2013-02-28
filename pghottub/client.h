// Copyright (c) 2013 - Cody Cutrer

#include <boost/shared_ptr.hpp>

namespace Mordor {
class Stream;
}

namespace PgHotTub {

class Client
{
public:
    typedef boost::shared_ptr<Client> ptr;

public:
    Client(boost::shared_ptr<Mordor::Stream> stream);

    void run();

private:
    void startup();

private:
    boost::shared_ptr<Mordor::Stream> m_stream;
};

}
