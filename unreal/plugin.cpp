#include "common/data_format.hpp"
#include "common/error_util.hpp"
#include "common/global_module_defs.hpp"
#include "common/switchboard.hpp"
#include "common/threadloop.hpp"

#include <iostream>

#include "ipc_server.cpp"

using namespace ILLIXR;

class unreal_ar : public threadloop {
public:
    unreal_ar(std::string name_, phonebook* pb_)
        : threadloop{name_, pb_}
    {
        std::cout << "SERVER CONSTRUCTOR" << std::endl;
    }

private:
    IPCServer* _m_ipcServer;

public:
    virtual void _p_thread_setup() override {
        std::cout << "SERVER THREAD SETUP" << std::endl;
        _m_ipcServer = new IPCServer;
        _m_ipcServer->setupServer();
        std::cout << "SERVER THREAD SETUP COMPLETE" << std::endl;
    }

    virtual skip_option _p_should_skip() override {
        std::cout << "SERVER SHOULD SKIP" << std::endl;
        // Ideally, we check if the buffer has any meaningful information first.
        // Otherwise, we can just skip.

        // if (strcmp(_m_buffer, "close") == 0) {
        //     return skip_option::stop;
        // } else {
        //     return skip_option::run;
        // }
    }

    virtual void _p_one_iteration() override {
        std::cout << "SERVER ONE ITERATION" << std::endl;
        _m_ipcServer->handleConnection();
    }

    virtual void stop() override {        
        delete _m_ipcServer;
    }
};

PLUGIN_MAIN(unreal_ar)