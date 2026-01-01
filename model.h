#ifndef MODEL_H_
#define MODEL_H_

#include <cstdint>
#include <array>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

using std::cout, std::endl, std::cerr;
using std::ifstream;
using std::string, std::memcpy, std::memset;


const size_t faces = 6;
const size_t dim = 3;

class cube {
private:
  uint8_t m_pos[faces][dim][dim];  

public:
  cube();
  cube(const uint8_t (&pos)[faces][dim][dim]);
  cube(const string &sequence, bool file);

  void reset();

  void save(string file);

  inline void permute(uint8_t f, bool i);
  void rotatecw(uint8_t f);
  void rotateccw(uint8_t f);
  void turn(char c, bool invert = false);
  void turns(const string &sequence);

  void printCube();

  void testing() {

  m_pos[3][0][0] = (uint8_t)1;
  uint8_t arr[] = {0, 5, 2};
  rotatecw(0);
  memcpy(m_pos[0][2], arr, dim);
  rotateccw(0);
  }  
};

#endif
