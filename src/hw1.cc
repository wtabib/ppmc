#include <Context.h>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <assert.h>
#include <iomanip>

typedef std::tuple<std::string, unsigned int> tuple;

void printTable(std::vector<Context> cs)
{
  for (int i = 0; i < cs.size(); i++)
  {
    std::cout << "ORDER " << i << std::endl;
    cs[i].printOrder();
  }
}

int main(int argc, char* argv[])
{

  /*if (argc != 2)
    std::cerr << "Input: <k>" << std::endl;

  float arg_k = atof(argv[1]);*/

  double total_probability = 0;
  std::cout << std::setprecision(5) << std::fixed;

  //unsigned int k = arg_k;
  unsigned int k = 3;

  //read file
  std::ifstream file;
  file.open("/Users/wtabib/Documents/classes/15-853/hw1/data/test-input.txt");
  if (file.is_open()) {
    std::cout << "file is open" << std::endl;
  }

  //convert file into string buffer
  std::stringstream buffer;
  buffer << file.rdbuf();

  //copy buffer into string
  std::string file_contents = buffer.str();

  std::cout << "contents of the file " << std::endl;
  std::cout << file_contents << std::endl;

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

      unsigned int idx = j-1;

      //begin string is too small for the order
      if (prefix.length() != idx)
        continue;

      //check if prefix string exists in the context
      bool prefix_str_found = cs[idx].findPrefixString(prefix);

      if (prefix_str_found == false)  {
        //std::cout << "here" << std::endl;
        if (idx == 0) {
          double suffix_probability = cs[idx].getSuffixProbability(prefix, 
              suffix, exceptions, char_vec);
          std::cout << suffix << ", " << suffix_probability << std::endl;
          total_probability += log2(1/suffix_probability);
        }
        cs[idx].checkExceptions(prefix, suffix, exceptions);
        cs[idx].addPrefixAndSuffix(prefix,suffix);
      }
      else {
        //std::cout << "here2" << std::endl;
        //is the suffix there?
        bool suffix_found = cs[idx].findSuffix(prefix,suffix);
        if (suffix_found)
        {
          //std::cout << "here3" << std::endl;
          if (idx == 0) {
            double suffix_probability = cs[idx].getSuffixProbability(prefix, 
                suffix, exceptions, char_vec);
            std::cout << suffix << ", " << suffix_probability << std::endl;
            total_probability += log2(1/suffix_probability);
          }

          cs[idx].checkExceptions(prefix, suffix, exceptions);
          bool increment_success = cs[idx].incrementSuffixCount(prefix, suffix);
          assert(increment_success);
        }
        else {
          //std::cout << "here4" << std::endl;
          double probability = cs[idx].getEscapeProbability(prefix, suffix, 
              exceptions);
          if (probability == probability)
          std::cout << "<$>, " << probability << std::endl;
          total_probability += log2(1/probability);

          if (idx == 0) {
            double suffix_probability = cs[idx].getSuffixProbability(prefix, 
                suffix, exceptions, char_vec);
            std::cout << suffix << ", " << suffix_probability << std::endl;
            total_probability += log2(1/suffix_probability);
          }

          cs[idx].checkExceptions(prefix, suffix, exceptions);
          cs[idx].addSuffix(prefix, suffix);
        }
      }

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
    //std::cout << "curr_string = " << curr_string << std::endl;
    exceptions.clear();

  }

  std::cout << "total probability = " << total_probability << std::endl;

  return 0;
}
