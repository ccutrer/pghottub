// Copyright (c) 2013 - Cody Cutrer

#include "mordor/predef.h"

#include <iostream>

#include "mordor/config.h"
#include "mordor/daemon.h"
#include "mordor/iomanager.h"
#include "mordor/main.h"

using namespace Mordor;

namespace PgHotTub {

static int daemonMain(int argc, char *argv[])
{
    try {
        IOManager ioManager;
        return 0;
    } catch (...) {
        std::cerr << boost::current_exception_diagnostic_information() << std::endl;
        return -1;
    }
}

}

MORDOR_MAIN(int argc, char *argv[])
{
    try {
        Config::loadFromEnvironment();
        return Daemon::run(argc, argv, &PgHotTub::daemonMain);
    } catch (...) {
        std::cerr << boost::current_exception_diagnostic_information() << std::endl;
        return -1;
    }
}
