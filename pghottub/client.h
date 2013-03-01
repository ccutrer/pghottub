// Copyright (c) 2013 - Cody Cutrer

#include <boost/shared_ptr.hpp>

#include "pghottub/connection.h"

namespace Mordor {
class Stream;
}

namespace PgHotTub {

class Client : public Connection
{
public:
    typedef boost::shared_ptr<Client> ptr;
    struct InvalidProtocolException : virtual Mordor::Exception {};

public:
    Client(HotTub &hotTub, boost::shared_ptr<Mordor::Stream> stream);

    void run();

private:
    void startup();
};

}
