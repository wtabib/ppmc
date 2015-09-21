#include <boost/shared_ptr.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

/*class Counts {

  public:
    //typedef boost::shared_ptr<Counts> Ptr;
    //typedef boost::shared_ptr<const Counts> ConstPtr;

    Counts(std::string str) : str_(str) 
  {
    count_ = 1;
  }

    Counts& operator++()
    {
      // do actual increment
      count_ += 1;
      return *this;
    }
    Counts operator++(int)
    {
      Counts tmp(*this);
      operator++();
      return tmp;
    }

    Counts& operator--()
    {
      // do actual increment
      assert(count_ != 0);
      count_ -= 1;
      return *this;
    }
    Counts operator--(int)
    {
      assert(count_ != 0);
      Counts tmp(*this);
      operator--();
      return tmp;
    }

    Counts operator==()
    {

    }

    inline bool operator==(const Counts& lhs, const Counts& rhs)
    { 
      return (lhs.str_ == rhs.str_);
    }

    unsigned int count_;
    std::string str_;

  private:

};

class Entry {

  public:
    std::string str_;
    std::vector<Counts> counts;

    bool find(std::string s)
    {
      for (unsigned int i = 0; i < counts.size(); ++i)
      {
        if (counts[i].str_ == s)
          return true;
      }
      return false;
    }

    int get(std::string s)
    {
      for (unsigned int i = 0; i < counts.size(); ++i)
      {
        if (counts[i].str_ == s)
          return i;
      }

      return -1;
    }

    void update(unsigned int idx, std::string begin, std::string end)
    {
      for (int i = 0; i < counts.size(); ++i)
      {
        if (counts[i].str_ == end)
        {
          //we got it, so we can just increment the count
          counts[i]++;
          return;
        }
      }
      //if it's not in there then we need to output add it in there
      //and output a <$>
      Count c(end);
      counts.push_back(c);
    }

  private:

};


class Order {

  public:
    //typedef boost::shared_ptr<Order> Ptr;
    //typedef boost::shared_ptr<const Order> ConstPtr;

    std::vector<std::string> context;
    std::vector<Entry> entries;

    bool find(std::string s)
    {
      for (unsigned int i = 0; i < entries.size(); ++i)
      {
        if (entries[i].str_ == s)
          return true;
      }
      return false;
    }

    int get(std::string s)
    {
      for (unsigned int i = 0; i < entries.size(); ++i)
      {
        if (entries[i].str_ == s)
          return i;
      }
      return -1;
    }
  
    void update(std::string s) 
    {
      std::string str = s;
      std::string end = s.at(s.length()-1);
      s.erase(s.end());
      std::string begin = s;

      if (find(begin))
      {
        int idx = get(begin);
        entries.update(idx, begin, end);
      }
      else 
      {
        entries.addEntry(begin, end);
      }
    }

  private:

};

class PPMCTable {

  public:
    //typedef boost::shared_ptr<PPMCTable> Ptr;
    //typedef boost::shared_ptr<const PPMCTable> ConstPtr;

    PPMCTable(unsigned int k) {

      highest_order = k;
      for (unsigned int i = 0; i < k; i++) 
      {
        Order ord;
        order.push_back(ord);
      }
    }

    void addEntry(unsigned int ord_idx, std::string s)
    {
      Counts cnt(s);
      order[ord_idx].counts.push_back(cnt);
    }

    void updateTable(const std::string& s)
    {
      std::string str = s;
      for (size_t i = highest_order; i > 0; --i)
      {
        if (str.length() < i)
          continue;

        unsigned int idx = i-1;
        order[idx].update(str);
        str.erase(str.begin());
      }
    }

    std::vector<Order> order;

  private:
    unsigned int highest_order;
};*/


