#include <Context.h>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

typedef std::tuple<std::string, unsigned int> tuple;


void getEscapeCounts(unsigned int& escape, 
    unsigned int& total_count, 
    const std::vector<tuple>& t, 
    const std::vector<std::string>& exceptions)
{
  escape = 0;
  total_count = 0;

  for (std::vector<tuple>::iterator it = t.begin(); it != t.end(); ++it)
  {

    //check to see if the string is in the exception list
    std::string curr_str = std::get<0>(*it);
    unsigned int curr_count = std::get<1>(*it);

    if (std::find(exceptions.begin(), exceptions.end(), curr_str) 
        != exceptions.end())
    {
      //we found an exception, which means we need to remove it from
      //consideration
      //we can do this by ignoring it
    }
    else
    {
      //tally up the escapes and the counts
      escape++;
      total_count += curr_count;
    }
  }
}



void printCharacterProbability( Context& c, 
    std::vector<std::string>& char_vec, 
    const std::vector<std::string>& exceptions, 
    std::string character) 
{

  //2 cases
  // Case 1) this is the first time we've ever seen the character.
  //        we need to use a special null probability

  //find the character in the list of all characters by ascii value
  char ascii;
  int numeric;

  ascii = character;
  numeric = ascii;

  //check to see if the character is in our vector
  std::vector<int>::iterator it = find(char_vec.begin(), char_vec.end(), numeric);
  if (it != char_vec.end()) 
  {
    char_vec.erase(it);

    //emit the probability
    total_count = 0;
    escape = 0;
    for (std::vector<string>::iterator its = exceptions.begin(); its != exceptions.end(); ++its)
    {

    }
  }
  else 
  {

    // Case 2) this is not the first time we've seen the character,
    //        but we still need to handle exceptions
  }
}


int main()
{

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
  //go through the string character by character
  for (unsigned int i = 0; i <= file_contents.length(); ++i)
  {

    std::string begin = curr_string;
    std::string end = file_contents[i];

    std::vector<std::string> exceptions;

    //iterate through each context
    for (unsigned int j = k; j > 0; --j)
    {

      unsigned int idx = j-1;

      //begin string is too small for the order
      if (begin.length() != idx)
        continue;

      //Step 1) check to see if the context exists and add the context if it
      //does not.  
      if (!cs[idx].find(begin))
      {
        tuple t = std::make_pair(end, 1);
        cs[idx].emplace(begin, t);
      }
      else 
      {
        //Step 2) if the context exists, check to see if the string exists
        bool context_exists = false;
        Context c = cs[idx];
        std::vector<tuple> t = c.map[begin];
        for (std::vector<tuple>::iterator it = t.begin();
            it != t.end(); ++it)
        {
          tuple tup = *it;
          if (std::get<0>(tup) == end) 
          {
            //the string exists so we need to increment the count
            context_exists = true;
            std::get<1>(tup) += 1;
          }
        }

        //if the context does not exist then we:
        //    (a) check the exceptions
        //    (b) optionally print out the probability
        //    (c) create list of new exceptions
        //    (d) output the probability
        if (!context_exists)
        {

          unsigned int escape = 0;
          unsigned int total_count = 0;

          for (std::vector<tuple>::iterator it = t.begin(); it != t.end(); ++it)
          {

            //check to see if the string is in the exception list
            std::string curr_str = std::get<0>(*it);
            unsigned int curr_count = std::get<1>(*it);

            if (std::find(exceptions.begin(), exceptions.end(), curr_str) 
                != exceptions.end())
            {
              //we found an exception, which means we need to remove it from
              //consideration
              //we can do this by ignoring it
            }
            else
            {
              //tally up the escapes and the counts
              escape++;
              total_count += curr_count;
            }
          }

          //need to reset the exceptions here
          exceptions.clear();
          for (std::vector<tuple>::iterator it = t.begin(); it != t.end(); ++it)
          {
            exceptions.push_back(std::get<0>(*it));
          }

          //now we've checked all of the strings in the exception list
          if (escape != 0)
          {
            //we have to output an escape
            std::cout << "<$>, " << (escape*1.)/(escape+total_count) << std::endl;
          }
        }
      }

      //create substring
      curr_string.push_back(file_contents[i]);
      if (i > k-1)
      {
        curr_string = curr_string.substr(1,k);
      }
      std::cerr << curr_string << std::endl;
    }

    return 0;
  }
