#include <iostream>

/* print current var to std::cout
  @param (char) current sum
  @param (char) current first int
  @param (char) current second int
  @return void
  @note the program will pause in the function
*/
void print(char sum, char a, char b){
  std::cout << "SUM:" << std::bitset<8>(sum) << std::endl;
  std::cout << (sum == 0 ? "A  :" : "A' :") << std::bitset<8>(a) << std::endl;
  std::cout << "           ^" << std::endl;
  std::cout << (sum == 0 ? "B  :" : "B' :") << std::bitset<8>(b) << std::endl;

  std::getchar();
}

/* add two 1 byte int
  @param (char) the first int
  @param (char) the second int
  @return (char) the result
*/
char add(char a, char b){
  int result = 0;

  for(int bit = 0; bit < 8; ++bit){
    // to-go
  }

  return (char)result;
}

/* multiply two 1 byte int
  @param (char) the first int
  @param (char) the second int
  @return (char) the result
*/
char multiply(char a, char b){
  int result = 0

  return (char)result;
}

int main(){
  add((char)3, (char)5);
  add((char)100, (char)200);

  multiply((char)7, (char)3);
  multiply((char)13, (char)11);

  print(1, 2, 3);

  return 0;
}
