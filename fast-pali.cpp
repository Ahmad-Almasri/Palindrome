
/*

  Ahmad Almasri -- 30114233

  ****

  This code finds out if there is a palindrome or not in a text file.
  If there is more than one word then the result is going to be the longest one.
  If both words are equal in size, then the result is the first word found in the text.

  ****

  This code was not done form scratch. I modified the code from the slow-pali.cpp.
  Besides, the concept of reading the data into 1 MB file was mentioned in long-int example as well.
  All of these examples were provided to us by the prof. Pavol Federl.

  ****

  Inputs of size 2GB is done by less than 30s.

  ****

*/

//==================================================

#include <unistd.h>
#include <stdio.h>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <vector>

//==================================================

char buffer[1025*1025]; // 1MB sotrage to hold results of read()
int buff_size = 0;      // stores how many characters are stored in buffer
int buff_pos = 0;       // position in bufffer[] where we extract next char

//==================================================

// return list of words (type : vector)
// if isspace() return true then push curr_word to the vecto (res)

std::vector<std::string>
split( const std::string & p_line)
{
  auto line = p_line + " ";
  std::vector<std::string> res;
  bool in_str = false;
  std::string curr_word = "";
  for( auto c : line) {
    if( isspace(c)) {
      if( in_str)
      res.push_back(curr_word);
      in_str = false;
      curr_word = "";
    }
    else {
      curr_word.push_back(c);
      in_str = true;
    }
  }
  return res;
}

//==================================================

// return int each time the function is being called
// return -1 means EOF (STOP)
// else return any int != -1
int
stdin_readChar(){
  // check if buffer[] is empty
  if( buff_pos >= buff_size) {
    // buffer is empty, let's replenish it
    buff_size = read( STDIN_FILENO, buffer, sizeof(buffer));
    // detect EOF
    if(buff_size <= 0) return -1;
    // reset position from where we'll return characters
    buff_pos = 0;
  }
  // return the next character from the buffer and update position
  return buffer[buff_pos++];
}

//==================================================

// return bool
// false : is NO a palindrome
// true : is a palindrome

bool
is_palindrome( const std::string & s)
{
  for( size_t i = 0 ; i < s.size() / 2 ; i ++)
    if( tolower(s[i]) != tolower(s[s.size()-i-1]))
      return false;
  return true;
}

//==================================================

// return line (type : string)

std::string
stdin_readline(){
  std::string result;
  // this loop stops if:
  // EOF || newLine
  while( true) {
    // start filling the string char by char
    int c = stdin_readChar();
    // if the val. of char = -1 then stop (is EOF)
    if( c == -1) break;
    // if c is the end of the line (ASCII val. of '\n' = 10)
    if( c == 10) {
      // if a new line and sizeof the string > 0 then return
      // because it is the end of the word 
      if( result.size() > 0) break;
    }
    else {
      // if it is not EOF
      // if it is not \n then add the char into the result
      result.push_back(c);
    }
  }
  return result;
}

//==================================================

// return longest palindrome (if found).

std::string
get_longest_palindrome()
{
  std::string max_pali;
  while(1) {
    std::string line = stdin_readline();
    if( line.size() == 0) break;
    auto words = split(line);
    for( auto word : words) {
      if( word.size() <= max_pali.size()) continue;
      if( is_palindrome(word))
        max_pali = word;
    }
  }
  return max_pali;
}

//==================================================

// main thread of this program

int
main()
{
  std::string max_pali = get_longest_palindrome();
  printf("Longest palindrome: %s\n", max_pali.c_str());
  return 0;
}

//==================================================
