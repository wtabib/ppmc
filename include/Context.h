#include <boost/shared_ptr.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <tuple>

typedef std::tuple<std::string, unsigned int> tuple;

class Context {

  public:
    bool insert(const std::string& key, const std::vector<tuple> &t);
    bool find(const std::string& key, const std::string& count);

    std::unordered_map<std::string, std::vector<tuple> > map;
  private:

};
