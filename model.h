#ifndef MODEL_H_
#define MODEL_H_

#include <cstdint>
#include <string>

using std::string;

class cube {
private:
  uint8_t pos[6][3][3];

public:
  cube();
  cube(uint8_t* pos);
  cube(string file);

  void save(string file);
};

#endif
