/******************************************************************************/
/*!
\file   Argle.cpp
\author Jake Ryan
\date   4/13/2018
\brief  
    Program that converts a user-inputted string to Argle-speak.
      
    Functions include:
    
       + split
       + add_yargle
       + strip_word
       + yargle_phrase
       + main
  
*/
/******************************************************************************/

#include <iostream> // cout, endl
#include <iomanip>  // setw
#include <string>   // string
#include <vector>   // vector

#define nDEBUG

//tokenizes a string and stores it in a vector of strings
std::vector<std::string> split(const char *str, char c = ' ')
{
  std::vector<std::string> result;

  do
  {
    const char *begin = str;

    while(*str != c && *str)
      str++;

    result.push_back(std::string(begin, str));
  } 
  while (0 != *str++);

  return result;
}

//appends 'argle' to the end of a word in a vector of words
void add_yargle(std::vector<std::string>& words, unsigned index)
{
    #ifdef DEBUG
    std::cout << "Append." << std::endl;
    #endif
  words[index].append("argle");
}

//strips rest of a word past index
void strip_word(std::string& word, int index)
{
  for (int i = word.size(); i >= index; i--)
  {
    #ifdef DEBUG
    std::cout << "Pop_back." << std::endl;
    #endif
    word.pop_back();
  }
}

//finds point in phrase to begin yargle-ing
std::vector<std::string> yargle_phrase(std::string& phrase)
{
  std::string vowels = "aeiouAEIOU";
  std::string letter_s = "sS";
  
  std::vector<std::string> words = split(phrase.data());
  bool flag = false; //true if a consonant has been found
  
  //for each word in the phrase
  for (int j = 0; j < words.size(); j++)
  {
    int lastVowel = 0;
    bool last_s = false; //true if last letter is 's'
    if (letter_s.find(words[j][words[j].size() - 1]) != std::string::npos)
      last_s = true;
    
    //for each letter in a word
    for (int i = 0; i < words[j].size(); i++) //start at FIRST character
    {
      //check for consonant
      if (vowels.find(words[j][i]) == std::string::npos)
      {
        #ifdef DEBUG
        std::cout << "Consonant." << std::endl;
        #endif
        flag = true;
        //continue;
      }
      
      
      //only check after a consonant is found
      if (flag)
      {
        //first 'qu' in word
        if (i == 1 && words[j].find("qu") != std::string::npos)
        {
          #ifdef DEBUG
          std::cout << "Yargle 'qu'." << std::endl;
          #endif
          strip_word(words[j], i + 2);
          add_yargle(words, j);
          
          if (last_s)
            words[j].append("s");
          break;
        }
        
        //determine last vowel with a consonant before it
        //also cannot be the last character of a word
        if (i > 0 && !(i == words[j].size() - 1))
          if (vowels.find(words[j][i]) != std::string::npos)
            if (vowels.find(words[j][i -1]) == std::string::npos)
            {
              #ifdef DEBUG
              std::cout << "Update last vowel." << std::endl;
              #endif
              lastVowel = i;
            }
        
        //...or last vowel after a consonant
        if (i + 1 == words[j].size() && lastVowel > 0)
        {
          #ifdef DEBUG
          std::cout << "Yargle vowel." << std::endl;
          #endif
          
          strip_word(words[j], lastVowel + 1);
          add_yargle(words, j);
          
          if (last_s)
            words[j].append("s");
          break;
        }
      }
    }
  }
  return words;
}

int main()
{
  bool flag = false;
  
  while(!flag)
  {
    std::string input;
    
    std::cout << "Phrargle to Yargle, 'q' to quargle: ";
    std::getline(std::cin, input);
    
    if (!input.compare("q"))
      return 0;
    
    std::vector<std::string> input_yargle = yargle_phrase(input);
    
    std::cout << std::endl << "Yargle phrargle, in Yargle: ";
    
    for (int i = 0; i < input_yargle.size(); i++)
      std::cout << input_yargle[i] << " ";
      
    std::cout << std::endl << std::endl << std::endl;
  }
  
  return 0;
}