#include <iostream>

#include "Config.hpp"
#include "Organizer.hpp"

/*
    Windows
    COMPILE WITH:
    -D_WIN32_WINNT=0x0501
    -shared -lboost_system -lboost_thread -lboost_date_time -lwsock32 -lws2_32

    Linux
    -shared -lboost_system -lboost_thread -lboost_date_time -lpthread -m32
*/

using namespace std;

Config config;
Organizer organizer;

#if WIN32
    extern "C" void __stdcall _RVExtension(char *output, int outputSize, const char *function)
#else
    extern "C" void RVExtension(char *output, int outputSize, const char *function)
#endif
{
    /* Format of function should be function name;data*/
    string s_function(function);
    string function_ = s_function.substr(0, s_function.find(';'));
    string data = s_function.substr(s_function.find(';')+1, s_function.length());

    if (function_ == "init") {
        bool result = config.parseConfigFile();

        if (result) {
            std::string hostname = config.getHostname();

            if (hostname != "") {
                organizer.setAuthorization(config.getAuthorization());
                organizer.setHostname(hostname);
                strncpy(output, hostname.c_str(), outputSize);
                return;
            }
        }

        strncpy(output, "ERROR", outputSize);
    } else if (function_ == "mission") {
        /* TODO: Get IP of current machine */
        Organizer::status_response status = organizer.createMission(data);
        if (status == Organizer::OK) {
            cout << "Organizer reports connection OK! ID: " << organizer.getMissionId() << endl;
            snprintf(output, outputSize, "%s", organizer.getMissionId().c_str());
        } else {
            if (status == Organizer::CONNECTION_FAILED) {
                cout << "Organizer reports connection failed. Check config" << endl;
            } else if (status == Organizer::PARSE_ERROR) {
                cout << "Organiser reports parse error when creating mission" << endl;
            } else {
                cout << "Organizer reports unknown error." << endl;
            }
            strncpy(output, "-1", outputSize);
        }
    } else if (function_ == "event") {
        EventManager::event_added result = organizer.addEvent(data);

        if (result == EventManager::EVENT_OK) {
            strncpy(output, "OK", outputSize);
        } else {
            strncpy(output, "ERROR", outputSize);
        }
    }
}
