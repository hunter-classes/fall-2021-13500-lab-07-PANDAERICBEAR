#include <iostream>
#include <cctype>
#include <fstream>

std::string removeLeadingSpaces(std::string str);
int countChar(std::string line, char c);

int main(){
  std::ifstream file("bad-code.cpp");
  std::string line = "";
  while(getline(file, line)){
      std::cout << removeLeadingSpaces(line) << std::endl;
  }
  file.close();
  return 0;
}

std::string removeLeadingSpaces(std::string str){
  bool doneWithSpaces = false;
  std::string result;
  for (int i = 0; i < str.length(); i++){
    if (!isspace(str[i]) && !doneWithSpaces){
      doneWithSpaces = true;
    }
    if (doneWithSpaces){
      result += str[i];
    }
  }
  return result;
}

int countChar(std::string line, char c){
  int counter = 0;
  for(int i = 0; i < line.length(); i++){
    if (line[i] == c){
      counter += 1;
    }
  }
  return counter;
}
