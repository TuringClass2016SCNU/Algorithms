#include <iostream>

/* print current var to std::cout
  @param (char) current sum
  @param (char) current first int
  @param (char) current processing bit
  @param (char) current second int
  @param (char) current flag
  @return void
  @note the program will pause in the function
*/
void print(char sum, char a, char b, char bit, char flag){
  std::cout << "SUM :" << std::bitset<8>(sum) << std::endl;
  std::cout << "A   :" << std::bitset<8>(a) << std::endl;
  std::cout << "BIT :" << std::bitset<8>(bit) << std::endl;
  std::cout << "B   :" << std::bitset<8>(b) << std::endl;
  std::cout << "FLAG:" << std::bitset<1>(flag) << std::endl;

  std::getchar();
}

/* add two 1 byte int
  @param (char) the first int
  @param (char) the second int
  @return (char) the result
*/
char add(char a, char b){
  char result = 0;

  unsigned char bit = 1;
  char flag = 0;
  while(bit != 0){
    unsigned char tmp = (bit & a) & (bit & b);

    if(tmp != 0){
      if(flag == 1){
        result |= bit;
        // hold flag
      }
      else{
        flag = 1;
        // hold current bit 0
      }
    }
    else{
      tmp = (bit & a) | (bit & b);

      if(tmp != 0){
        if(flag == 1){
          // hold flag == 1, current bit 0
        }
        else{
          result |= bit;
          // hold flag == 0
        }
      }
      else{
        if(flag == 1){
          result |= bit;
          flag = 0;
        }
        else{
          // hold flag == 0, current bit 0
        }
      }
    }

    print(result, a, b, bit, flag);

    bit <<= 1;
  }

  return result;
}

/* multiply two 1 byte int
  @param (char) the first int
  @param (char) the second int
  @return (char) the result
*/
char multiply(char a, char b){
  char result = 0;

  return result;
}

int main(){
  short result;

  result = add((char)3, (char)5);
  std::cout << "3 + 5 = " << result << std::endl << std::endl;

  result = add((char)76, (char)107);
  std::cout << "100 + 127 = " << result << std::endl << std::endl;
/*
  result = multiply((char)7, (char)3);
  std::cout << "7 * 3 = " << result << std::endl;

  result = multiply((char)13, (char)11);
  std::cout << "13 * 11 = " << result << std::endl;
*/
  return 0;
}
