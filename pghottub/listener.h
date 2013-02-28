// Copyright (c) 2013 - Cody Cutrer

namespace PgHotTub {

class HotTub;

class Listener
{
public:
    Listener(HotTub &hotTub);

    virtual void stop() = 0;

protected:
    HotTub &m_hotTub;
};

}
