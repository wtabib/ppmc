
bool Context::insert( const std::string& key,
                      const std::vector<tuple>& t)
{

}

bool Context::find(const std::string& key, const std::string& count)
{
  if (map.find(key) != map.end())
  {
    return true;
  }
  return false;
}
