#include "Util.hpp"

namespace DAF {

std::string Util::replace(std::string subject, const std::string &from, const std::string &to) {

    // find first occurrence
    std::size_t pos = subject.find(from);
    // replce and repeat until the end
    while(pos != std::string::npos) {
        subject.replace(pos, from.size(), to);
        pos = subject.find(from, pos + to.size());
    }
    return subject;
};

std::string Util::vector2string(std::vector<std::string> vec) {
    return Util::vector2string(vec, " ");
};

std::string Util::vector2string(std::vector<std::string> vec, std::string separator) {
    std::string retval;
    for(std::string &s: vec) {
        retval += s + separator;
    }
    return retval;
};

bool Util::fileIsReadable(const std::string &file) {
    return access(file.c_str(), R_OK) == 0;
};

std::string Util::baseName(const std::string &path) {
    return std::filesystem::path(path).filename();
};

bool Util::fileIsValidJson(const std::string &file) {
    return nlohmann::json::accept(std::ifstream(file));
};

std::string Util::trim(const std::string &s) {
   auto  wsfront=std::find_if_not(s.begin(),s.end(),[](int c){return std::isspace(c);});
   return std::string(wsfront,std::find_if_not(s.rbegin(),std::string::const_reverse_iterator(wsfront),[](int c){return std::isspace(c);}).base());
}

}