#ifndef CONTEXT_H
#define CONTEXT_H

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
    bool addPrefixAndSuffix(const std::string& prefix, const std::string& suffix);
    bool addSuffix(const std::string& prefix, const std::string& suffix);
    bool findSuffix(const std::string& prefix, const std::string& suffix);
    bool findPrefixString(const std::string& prefix);
    unsigned int size();
    void checkExceptions(std::string& prefix, std::string& suffix, std::vector<std::string> exceptions);
    double getSuffixProbability( const std::string& prefix, 
                                 const std::string& suffix, 
                                 std::vector<std::string>& exceptions, 
                                 std::vector<int>& char_list);

    bool incrementSuffixCount(const std::string& prefix, const std::string& suffix);
    bool needToPrintEscape(const std::string& prefix, const std::string& suffix, std::vector<std::string>& exceptions);
    double getEscapeProbability( const std::string& prefix, 
                                const std::string& suffix);

    void printVector(std::string prefix);

  private:
    std::unordered_map<std::string, std::vector<tuple> > map;

};

#endif
