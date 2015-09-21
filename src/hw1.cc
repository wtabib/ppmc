#include <Context.h>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <assert.h>
#include <iomanip>

typedef std::tuple<std::string, unsigned int> tuple;

int main()
{

  std::cerr << std::setprecision(5) << std::fixed;

  unsigned int k = 3;

  //read file
  std::ifstream file;
  file.open("/Users/wtabib/Documents/classes/15-853/hw1/data/test-input.txt");
  if (file.is_open()) 
  {
    std::cout << "file is open" << std::endl;
  }

  //convert file into string buffer
  std::stringstream buffer;
  buffer << file.rdbuf();

  //copy buffer into string
  std::string file_contents = buffer.str();

  std::cerr << "contents of the file " << std::endl;
  std::cerr << file_contents << std::endl;

  std::string curr_string = "";

  std::vector<int> char_vec;
  for (int i = 0; i < 256; i++)
  {
    char_vec.push_back(i);
  }

  std::vector<Context> cs;
  for (int i = 0; i < k; ++i)
  {
    Context c;
    cs.push_back(c);
  }
  //go through the string character by character
  for (unsigned int i = 0; i < file_contents.length(); ++i)
  {

    if (file_contents[i] == EOF)
      break;

    std::stringstream ss;
    std::string prefix = curr_string;
    std::string suffix;
    ss << file_contents[i];
    ss >> suffix;

    std::vector<std::string> exceptions;

    //iterate through each context
    for (unsigned int j = k; j > 0; --j)
    {
      std::cerr << "CONTEXT = " << j-1 << ", prefix = " << prefix << std::endl;

      unsigned int idx = j-1;

      //begin string is too small for the order
      if (prefix.length() != idx)
        continue;

      //check if prefix string exists in the context
      bool prefix_str_found = cs[idx].findPrefixString(prefix);

      if (prefix_str_found == false)  
      {
        if (idx == 0) 
        {
          double suffix_probability = cs[idx].getSuffixProbability(prefix, suffix, exceptions, char_vec);
          std::cerr << suffix << ", " << suffix_probability << std::endl;
        }
        cs[idx].checkExceptions(prefix, suffix, exceptions);
        cs[idx].addPrefixAndSuffix(prefix,suffix);
      }
      else 
      {
        //is the suffix there?
        bool suffix_found = cs[idx].findSuffix(prefix,suffix);
        std::cerr << "suffix_found = " << suffix_found << " , for suffix " << suffix << std::endl;
        if (suffix_found)
        {
          //////
          std::cerr << "printing exceptions " << std::endl;
          for (int i = 0; i < exceptions.size(); i++)
          {
            std::cerr << "exception: " << exceptions[i] << std::endl;
          }
          /////
          if (idx == 0) 
          {
            double suffix_probability = cs[idx].getSuffixProbability(prefix, suffix, exceptions, char_vec);
            std::cerr << suffix << ", " << suffix_probability << std::endl;
          }

          cs[idx].checkExceptions(prefix, suffix, exceptions);
          bool increment_success = cs[idx].incrementSuffixCount(prefix, suffix);
          assert(increment_success);
        }
        else 
        {
          if (idx == 0) 
          {
            double suffix_probability = cs[idx].getSuffixProbability(prefix, suffix, exceptions, char_vec);
            std::cerr << suffix << ", " << suffix_probability << std::endl;
          }

          cs[idx].checkExceptions(prefix, suffix, exceptions);
          cs[idx].addSuffix(prefix, suffix);
        }
        /*else 
        {
          //now we have to deal with escape bullshit
          bool do_we_escape = cs[idx].needToPrintEscape(prefix, suffix, exceptions);
          // if we need to escape, we print out the escape and then update the
          // contents
          if (do_we_escape) {
            double probability = cs[idx].getEscapeProbability(prefix, suffix);
            std::cerr << "<$>, " << probability << std::endl;
          }

          //if we're on the 0th context then we should emit a probability
          if (idx == 0) 
          {
            double suffix_probability = cs[idx].getSuffixProbability(prefix, suffix, exceptions, char_vec);
            std::cerr << suffix << ", " << suffix_probability << std::endl;
          }
          cs[idx].addSuffix(prefix, suffix);
        }*/
      }


      //std::cerr << "order = " << idx << " vector: ";
      //cs[idx].printVector(prefix);

      //std::cerr << "prefix = " << prefix << std::endl;

      if (idx > 1)
        prefix = prefix.substr(1,prefix.size()-1);
      else
        prefix = "";

    }
    //create substring
    curr_string.push_back(file_contents[i]);
    if (i > k-2)
    {
      curr_string = curr_string.substr(1,k);
    }
    //std::cerr << "curr_string = " << curr_string << std::endl;
  }

  for (int i = 0; i < k; i++)
  {
    std::cerr << "context = " << i << ", size = " << cs[i].size() << std::endl;
  }

  return 0;
}
