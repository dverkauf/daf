#include <string>
#include <vector>

#include "includes/DBasicClass.hpp"
#include "includes/Application.hpp"
#include "includes/Exception.hpp"
#include "includes/Interactor.hpp"
#include "json.hpp"

class WlanScanApp : public DAF::Application {

    private:

    struct Wlan {

    };

    struct Scanner {
        static std::vector<Wlan> scan();
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
    void config() override {};
    void run() override {};

};

LETS_DO_IT(WlanScanApp);