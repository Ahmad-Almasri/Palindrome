#include <unistd.h>
#include <stdio.h>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <vector>

char buffer[1024*1024]; // 1MB sotrage to hold results of read()
int buff_size = 0;      // stores how many characters are stored in buffer
int buff_pos = 0;       // position in bufffer[] where we extract next char

//==================================================

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

// return char each time the function is being called
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

bool
is_palindrome( const std::string & s)
{
  for( size_t i = 0 ; i < s.size() / 2 ; i ++)
    if( tolower(s[i]) != tolower(s[s.size()-i-1]))
      return false;
  return true;
}

//==================================================

std::string
stdin_readline(){
  std::string result;
  while( true) {
    int c = stdin_readChar();
    if( c == -1) break;
    // if c is the end of the line
    if( c == 10) {
      if( result.size() > 0) break;
    }
    else {
      // if it is not \n then add the char into the result
      result.push_back((char)c);
    }
  }
  return result;
}

//==================================================

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

int
main()
{
  std::string max_pali = get_longest_palindrome();
  printf("Longest palindrome: %s\n", max_pali.c_str());
  return 0;
}

