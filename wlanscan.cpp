#include <string>
#include <vector>
#include <unistd.h>
#include <sstream>
#include <regex>
#include <ctime>

#include "includes/DBasicClass.hpp"
#include "includes/Application.hpp"
#include "includes/BasicException.hpp"
#include "includes/Interactor.hpp"
#include "includes/json.hpp"
#include "includes/Command.hpp"
#include "includes/Option.hpp"
#include "includes/Config.hpp"

class WlanScanApp : public DAF::Application {

    private:

    struct Wlan {
        Wlan(std::string ssid, std::string bssid, std::string signal, std::string channel, std::string security, std::string timestamp) :
            ssid{ssid}, bssid{bssid}, signal{signal}, channel{channel}, security{security}, timestamp{timestamp} {};
        std::string ssid;
        std::string bssid;
        std::string signal;
        std::string channel;
        std::string security;
        std::string timestamp;
        friend std::ostream& operator<<(std::ostream& os, const Wlan& a) {
            os << a.ssid << ";" << a.bssid << ";" << a.signal << ";" << a.channel << ";" << a.security << ";" << a.timestamp;
            return os;
        };
    };

    struct WlanscanException : public DAF::BasicException {
        enum REASONS {
            CANNOT_OPEN_PIPES = 0,
            CANNOT_READ_UNTIL_EOF,
            CANNOT_PARSE_LINE,
            UKNOWN_FACILITY
        };
        //static REASONS Reason;
        
        static const inline std::vector<std::string> _messages = {
            "Pipes to scanner child process failed to open (scanner=%info%",
            "Could not read result of scanner until the EOF",
            "Cannot parse scanner line (%info%)",
            "Cannot find facility (%info%) in config"
        };
        
        WlanscanException(int reason) : DAF::BasicException{_messages.at(reason), ""} {};
        WlanscanException(int reason, std::string info) : DAF::BasicException{_messages.at(reason), info} {};
    };

    struct Scanner {

        static std::vector<Wlan> scan() {
            std::string prefix = "Scanner::scan";
            TRACE(prefix);
            #ifdef __APPLE__
            std::string cmd = "/System/Library/PrivateFrameworks/Apple80211.framework/Versions/A/Resources/airport -s";
            const std::regex re("^\\s*(.*)\\s(\\w{2}:\\w{2}:\\w{2}:\\w{2}:\\w{2}:\\w{2})\\s+([-+]?[0-9]*)\\s+([0-9]+)\\s+(\\w*)\\s+([-\\w]+)\\s+(.*)$");
            #endif
            #ifdef __linux__
            #define __LINUX___ true
            std::string cmd = "LANG=C nmcli --terse --fields active,ssid,bssid,mode,chan,freq,signal,security,wpa-flags,rsn-flags device wifi list";
            #endif
            #if defined(_WIN32)|| defined(_WIN64)
            #define __WINDOWS__ true
            std::string cmd = "netsh wlan show networks mode=Bssid";
            #endif
            #if !defined(__APPLE__) && !defined(__linux__) && !defined(_WIN32) && !defined(_WIN64)
            #error You are compiling this programm for an unknown plattform. Please supply your own scanning command above.
            #endif
            std::vector<Wlan> wlans;
            // scan
            FILE *p = popen(cmd.c_str(), "r");
            if(p == NULL) {
                TRACE("failed to open pipes to cmd=" + cmd);
                throw WlanscanException(WlanscanException::REASONS::CANNOT_OPEN_PIPES, cmd);
            }
            char buffer[PIPE_BUF * 2];
            std::stringstream response;
            while(fgets(buffer, PIPE_BUF * 2, p) != NULL) {
                response << buffer;
            }
            int return_code = pclose(p);
            TRACE("return code of scanner = " + std::to_string(return_code));
            // get a timestamp
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);
            std::stringstream ss;
            ss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
            std::string timestamp = ss.str();
            // parse result into lines
            std::vector<std::string> lines;
            for(std::string line; std::getline(response, line, '\n');) {
                lines.push_back(line);
            }
            // parse lines
            for(int c = 1; c < lines.size(); c++ ) {
                std::smatch matches;
                if(std::regex_match(lines.at(c), matches, re)) {
                    #ifdef __APPLE__
                    wlans.push_back(Wlan(matches[1], matches[2], matches[3], matches[4], matches[7], timestamp));
                    #endif
                } else {
                    throw WlanscanException(WlanscanException::REASONS::CANNOT_PARSE_LINE, lines.at(c));
                }
            }
            return wlans;
        };
        
    };

    class Spot : public DBasicClass {
        private:
        std::string _name;
        std::vector<Wlan> _wlans;
        public:
        Spot(std::string name) : _name{name} {};
        void scan();
        std::string name() { return _name; };
        void wlans(std::vector<Wlan> wlans) { _wlans = wlans; };
        std::vector<Wlan> wlans() { return _wlans; };
        friend std::ostream& operator<<(std::ostream& os, const Spot& a) {
            os << a._name << ";;;;;" << std::endl;
            for(const auto w: a._wlans) {
                os << w << std::endl;
            }
            return os;
        };
    };

    class Facility : public DBasicClass {
        
        private:
        std::string _name;
        std::vector<Spot> _spots;

        public:
        void name(std::string name) { _name = name; };
        std::string name() { return _name; };
        void spot(std::string spot) { _spots.push_back(Spot(spot)); }
        std::vector<Spot> spots() { return _spots; }
        friend std::ostream& operator<<(std::ostream& os, const Facility& a) {
            os << a._name << ";;;;;" << std::endl;
            for(const auto s: a._spots) {
                os << s << std::endl;
            }
            return os;
        };
    };

    class WlanScanConfig : public DAF::Config {
        public:

        WlanScanConfig(std::string config_file) : Config{config_file} {};
        
        std::vector<Facility> facilities() {
            std::vector<Facility> facilities;
            for(const auto &facility: _config["facilities"]) {
                Facility f;
                f.name(facility["name"]);
                for(const auto &spot: facility["spots"]) {
                    f.spot(spot);
                }
                facilities.push_back(f);
            }
            return facilities;
        };

        std::vector<std::string> facilityNames() {
            std::vector<std::string> names;
            for(const auto &facility: _config["facilities"]) {
                names.push_back(facility["name"]);
            }
            return names;
        };

        Facility facility(std::string name) {
            Facility f;
            for(const auto &facility: _config["facilities"]) {
                f.name(facility["name"]);
                for(const auto &spot: facility["spots"]) {
                    f.spot(spot);
                }
                return f;
            }
            throw WlanscanException(WlanscanException::REASONS::UKNOWN_FACILITY, name);
        };

    };

    void scan() {
        std::string prefix = "WlanScanApp::scan";
        TRACE("");
        DAF::Command cmd = getCommand(_command);
        TRACE("");
        DAF::Option opt = cmd.option("c");
        TRACE("opt.short_name()=" + opt.short_name());
        std::string config_file = opt.value();
        TRACE("config_file=" + config_file);
        WlanScanConfig config(config_file);
        // ask for facility
        std::vector<std::string> facility_names = config.facilityNames();

        int answer = Interactor::choose("Choose a facility to scan", facility_names);
        Facility facility = config.facility(facility_names.at(answer));
        std::vector<std::string> headers{"SSID", "BBSID", "Channel", "Signal", "Security", "Timestamp"};
        for(auto &spot: facility.spots()) {
            if(Interactor::confirm("Are you on spot: " + spot.name())) {
                std::vector<Wlan> wlans;
                std::vector<std::vector<std::string>> data;
                do {
                    wlans = Scanner::scan();
                    data.erase(data.begin(), data.end());
                    for(const auto &w: wlans) {
                        data.push_back(std::vector<std::string>{w.ssid, w.bssid, w.channel, w.signal, w.security, w.timestamp});
                    }
                    Interactor::table(data, headers);
                } while(! Interactor::confirm("Move to next spot?"));
                spot.wlans(wlans);
            }
        }
    };

    public:
    void config() override {
        _useDefaultCommands = true;
        _useDefaultOptions = true;
        DAF::Command cmdScan("scan", "Scan a facility for WLANs");
        DAF::Option optConfigFile("c", "config", "Specify an alternative config");
        optConfigFile.takeValue();
        DAF::Option optFacilityName("f", "facility", "Specify the facility to scan");
        optFacilityName.takeValue();
        cmdScan.need(optConfigFile);
        cmdScan.need(optFacilityName);
        cmdScan.callback(CALLBACK(WlanScanApp::scan));
        addCommand(cmdScan);
    };
    void run() override {
        /*
        std::string prefix = "WlanScanApp::run";
        TRACE("");
        std::vector<Wlan> wlans = Scanner::scan();
        */
    };

};

LETS_TRACE_IT(WlanScanApp);