// Copyright (c) 2013 - Cody Cutrer

#include <vector>

#include <boost/shared_ptr.hpp>

namespace Mordor {
class Stream;
}

namespace PgHotTub {

class Listener;

class HotTub
{
public:
    void stop();

    void addListener(Listener &listener);

    void acceptConnection(boost::shared_ptr<Mordor::Stream> stream);
private:
    std::vector<Listener *> m_listeners;
};

}
