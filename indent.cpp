#include <iostream>
#include <cctype>
#include <fstream>

int countChar(std::string line, char c);
std::string removeLeadingSpaces(std::string str);

int main(){
  std::ifstream badFile("bad-code.cpp");
  std::string line = "";

  /* Task A */
  std::string taskAUnindentedString;

  /* Task B */
  std::string taskBIndentedString;
  int openBraces = 0;
  int closeBraces = 0;

  std::ofstream file;
  file.open("fixed.cpp");

  while(getline(badFile, line)){
      std::string unindented = removeLeadingSpaces(line);
      taskAUnindentedString += unindented + "\n";
      int remainingBraces = openBraces - closeBraces;

      //adding tabs
      std::string tabs = "";
      for (int i = 0; i < remainingBraces; i++){
        tabs += "\t";
      }

      //open and close braces in current line --> tracking
      //ex: "Complex(): real(0), imag(0){ }" should indent regularly; before was checking if a "}" was in the string and then indent one tab directly.
      //                                                              but this is {} is an exception case.
      //ex: "} else {" should indent with one less tab because only a {} (opening brace before a closing brace can cancel out a tab)
      //code: checks if there is a closing brace before an opening brace --> means 1 less tab is needed. if {}, regular tabbing
      int localClose = 0;
      bool foundOpenFirst = false;
      for(int i = 0; i < unindented.length(); i++){
        if(unindented[i] == '{'){
          foundOpenFirst = true;
        }
        if (unindented[i] == '}' && !foundOpenFirst){
          localClose += 1;
        }
      }

      //printing of output
      //std::cout << tabs.length() << "  ";
      if (localClose > 0){ //--> if there is } before a {, 1 less tab is needed
        taskBIndentedString += tabs.substr(0, tabs.length()-1) + unindented + "\n"; //substring to take 1 less tab
        file << tabs.substr(0, tabs.length()-1) + unindented << std::endl;
      } else {
        taskBIndentedString +=  tabs + unindented + "\n"; //--> indent normally
        file << tabs + unindented << std::endl;
      }

      //checking for open braces
      openBraces += countChar(unindented, '{');
      //checking for closing braces
      closeBraces += countChar(unindented, '}');

  }
  file.close();

  //Printing output for Task A
  std::cout << "-------------------Task A (Unindented)---------------" << std::endl;
  std::cout << taskAUnindentedString << std::endl;
  //Printing output for Task B
  std::cout << "-------------------Task B (Indented)---------------" << std::endl;
  std::cout << taskBIndentedString;
  return 0;
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

//Removes all leading spaces one every line
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
