#include <Context.h>

bool Context::addPrefixAndSuffix(const std::string& prefix, const std::string& suffix)
{
  std::vector<tuple> t;
  t.push_back(std::make_pair(suffix, 1));
  map.emplace(prefix, t);
  return true;
}

bool Context::addSuffix(const std::string& prefix, const std::string& suffix)
{
  //std::cerr << "size of map before add suffix" << map.size() << std::endl;
  std::vector<tuple> t = map[prefix];
  t.push_back(std::make_pair(suffix, 1));
  std::unordered_map<std::string, std::vector<tuple> >::const_iterator it = map.find(prefix);
  map.erase(it);
  map.emplace(prefix, t);
  //std::cerr << "size of map after add suffix" << map.size() << std::endl;
  //std::cerr << "suffix = " << suffix << std::endl;
  //std::cerr << std::endl;
  //printVector(prefix);
  //std::cerr << std::endl;
  return true;
}

bool Context::findSuffix(const std::string& prefix, const std::string& suffix)
{
  if (map.find(prefix) != map.end())
  {
    std::vector<tuple> t = map[prefix];
    for(std::vector<tuple>::iterator it = t.begin();
        it != t.end(); ++it)
    {
      if (suffix == "i") {
        std::cerr << "size of map = " << map.size() << std::endl;
        std::cerr << "in findSuffix: " << std::get<0>(*it) << std::endl;
        std::cerr << "suffix = " << suffix << std::endl;
      }
      if (std::get<0>(*it) == suffix)
        return true;
    }
  }
  return false;
}


bool Context::findPrefixString(const std::string& prefix)
{
  if (map.find(prefix) != map.end())
  {
    return true;
  }
  return false;
}

double Context::getSuffixProbability( const std::string& prefix, 
                                      const std::string& suffix, 
                                      std::vector<std::string>& exceptions, 
                                      std::vector<int>& char_list)
{
  //check to see if the character has ever been added before
  std::string to_ascii = suffix;
  const char *ascii;
  int numeric;
  ascii = to_ascii.c_str();
  numeric = *ascii;

  std::vector<int>::iterator it = std::find(char_list.begin(), char_list.end(), numeric);
  if (it != char_list.end())
  {
    double probability = 1./char_list.size();
    char_list.erase(it);
    return probability;
  }

  std::vector<tuple> t = map[prefix];
  double num_escapes = 0;
  double num_chars = 0;
  double char_count = 0;
  for (std::vector<tuple>::iterator it = t.begin(); it != t.end(); ++it)
  {
    std::vector<std::string>::iterator its = find(exceptions.begin(), exceptions.end(), std::get<0>(*it));
    if (its == exceptions.end())
    {
      num_escapes++;
      num_chars += std::get<1>(*it);
    }

    if (std::get<0>(*it) == suffix)
      char_count += std::get<1>(*it);
  }
  
  if (suffix == "i")
    std::cerr << "num_chars = " << num_chars << ", num_escapes = " << num_escapes << std::endl;
  double probability = char_count/(num_chars+num_escapes);
  return probability;
}

double Context::getEscapeProbability( const std::string& prefix, 
                                      const std::string& suffix)
{
  std::vector<tuple> t = map[prefix];
  double num_escapes = 0;
  double num_chars = 0;
  for (std::vector<tuple>::iterator it = t.begin(); it != t.end(); ++it)
  {
    num_escapes++;
    num_chars += std::get<1>(*it);
  }
  double probability = num_chars/(num_chars+num_escapes);
  return probability;
}

unsigned int Context::size()
{
  return map.size();
}

bool Context::incrementSuffixCount(const std::string& prefix, const std::string& suffix)
{
  std::vector<tuple> t = map[prefix];
  for (int i = 0; i < t.size(); ++i)
  {
    if (std::get<0>(t[i]) == suffix) {
      std::get<1>(t[i])++;

      std::unordered_map<std::string, std::vector<tuple> >::const_iterator it = map.find(prefix);
      map.erase(it);
      map.emplace(prefix, t);

      return true;
    }
  }
  return false;
}

bool Context::needToPrintEscape(const std::string& prefix, const std::string& suffix, std::vector<std::string>& exceptions)
{
  std::vector<tuple> t = map[prefix];
  double num_escapes = 0;
  double num_chars = 0;
  for (std::vector<tuple>::iterator it = t.begin(); it != t.end(); ++it)
  {

    if (std::get<0>(*it) == suffix)
      continue;

    std::vector<std::string>::iterator its = find(exceptions.begin(), exceptions.end(), std::get<0>(*it));
    if (its == exceptions.end())
    {
      num_escapes++;
      num_chars += std::get<1>(*it);
    }
  }

  if (num_escapes > 0)
    return true;

  return false;
}

void Context::printVector(std::string prefix)
{

  std::vector<tuple> t = map[prefix];

  for (int i = 0; i < t.size(); i++)
  {
    std::cerr << "<" << std::get<0>(t[i]) << ", " << std::get<1>(t[i]) << ">" << "\t";
  }
  std::cerr << std::endl;

}

void Context::checkExceptions(std::string& prefix, std::string& suffix, std::vector<std::string> exceptions)
{
  std::cerr << "GOT HERE" << std::endl;
  if (suffix == "i")
    printVector(suffix);

  exceptions.clear();

  if (map.find(suffix) != map.end())
  {
    std::vector<tuple> t = map[suffix];
    for (int i = 0; i < t.size(); i++)
    {
      if (std::get<0>(t[i]) != suffix)
        exceptions.push_back(std::get<0>(t[i]));
    }
  }
}
