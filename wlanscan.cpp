#include <string>
#include <vector>
#include <unistd.h>
#include <sstream>
#include <regex>
#include <ctime>

#include "includes/DBasicClass.hpp"
#include "includes/Application.hpp"
#include "includes/Exception.hpp"
#include "includes/Interactor.hpp"
#include "includes/json.hpp"

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
    };

    struct Scanner {

        struct ScannerException : public DAF::Exception {
            enum REASONS {
                CANNOT_OPEN_PIPES = 0,
                CANNOT_READ_UNTIL_EOF
            };
            static REASONS Reason;

            const std::vector<std::string> Messages {
                "Pipes to scanner child process failed to open (scanner=%info%",
                "Could not read result of scanner until the EOF"
            };
        };

        static std::vector<Wlan> scan() {
            std::string prefix = "Scanner::scan";
            TRACE(prefix);
            #ifdef __APPLE__
            std::string cmd = "/System/Library/PrivateFrameworks/Apple80211.framework/Versions/A/Resources/airport -s";
            const std::regex re("^\\s*(.*)\\s(\\w{2}:\\w{2}:\\w{2}:\\w{2}:\\w{2}:\\w{2})\\s+([-+]?[0-9]*)\\s+([0-9]+)\\s+(\\w*)\\s+([-\\w]+)\\s+(.*)$");
            #endif
            #ifdef __linux__
            std::string cmd = "LANG=C nmcli --terse --fields active,ssid,bssid,mode,chan,freq,signal,security,wpa-flags,rsn-flags device wifi list";
            #endif
            #if defined(_WIN32)|| defined(_WIN64)
            std::string cmd = "netsh wlan show networks mode=Bssid";
            #endif
            #if !defined(__APPLE__) && !defined(__linux__) && !defined(_WIN32) && !defined(_WIN64)
            #error You are compiling this programm for an unknown plattform. Please supply your own scanning command above.
            #endif
            std::vector<Wlan> wlans;
            // scan
            // those arrays will hold the file descriptor for the pipes
            /*
            int stdin_pipe[2];
            int stderr_pipe[2];
            int stdout_pipe[2];
            */
            /*
            if(pipe(stdin_pipe) == -1 || pipe(stderr_pipe) == -1 || pipe(stdout_pipe) == -1) {
                TRACE("failed to open pipes");
                ScannerException::throwMe(ScannerException::REASONS::CANNOT_OPEN_PIPES);
            }
            */
            FILE *p = popen(cmd.c_str(), "r");
            if(p == NULL) {
                TRACE("failed to open pipes to cmd=" + cmd);
                ScannerException::throwMe(ScannerException::REASONS::CANNOT_OPEN_PIPES, cmd);
            }
            char buffer[PIPE_BUF * 2];
            std::stringstream response;
            while(fgets(buffer, PIPE_BUF * 2, p) != NULL) {
                response << buffer;
            }
            int return_code = pclose(p);
            TRACE("return code of scanner = " + std::to_string(return_code));
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);
            std::stringstream ss;
            ss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
            std::string timestamp = ss.str();
            std::vector<std::string> lines;
            for(std::string line; std::getline(response, line, '\n');) {
                lines.push_back(line);
            }
            std::cout << "Result:" << std::endl;
            for(int c = 1; c < lines.size(); c++ ) {
                std::cout << c << ": " << lines.at(c) << std::endl;
                std::smatch matches;
                if(std::regex_match(lines.at(c), matches, re)) {
                    wlans.push_back(Wlan(matches[1], matches[2], matches[3], matches[4], matches[7], timestamp));
                    std::cout << "SSID:\t" << matches[1] << std::endl;
                    std::cout << "BSSID:\t" << matches[2] << std::endl;
                    std::cout << "RSSI:\t" << matches[3] << std::endl;
                    std::cout << "CHANNEL:\t" << matches[4] << std::endl;
                    std::cout << "HT:\t" << matches[5] << std::endl;
                    std::cout << "CC:\t" << matches[6] << std::endl;
                    std::cout << "SECURITY:\t" << matches[7] << std::endl;
                } else {
                    std::cout << "LINE MISMATCHED\n";
                }
            }
            
            

            //std::cout << response << std::endl;
            /*
            int return_code = feof(p);
            if(return_code != 0) {
                TRACE("could read result of wlan scan until the end (return code = " + std::to_string(return_code) + ")");
                ScannerException::throwMe(ScannerException::REASONS::CANNOT_READ_UNTIL_EOF);
            }
            */
            
            // parse results into vector
            
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
    };

    class Facility : public DBasicClass {
        
        private:
        std::string _name;
        std::vector<Spot> _spots;

        public:
        void name(std::string name) { _name = name; };
        std::string name() { return _name; };
        void addSpot(std::string spot) { _spots.push_back(Spot(spot)); }
        std::vector<Spot> spots() { return _spots; }

    };

    public:
    void config() override {
        _useDefaultCommands = false;
        _useCommands = false;
        _useDefaultOptions = true;
    };
    void run() override {
        Scanner::scan();
    };

};

LETS_TRACE_IT(WlanScanApp);