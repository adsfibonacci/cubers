#include "model.h"

cube::cube() {
  for (uint8_t i = 0; i < faces; ++i) {
    memset(m_pos[i], i, dim*dim);
  }
  //testing();  
}
cube::cube(const uint8_t (&pos)[faces][dim][dim]) {
  memcpy(m_pos, pos, sizeof(m_pos));
}

void cube::reset() {
  for (uint8_t i = 0; i < faces; ++i) {
    memset(m_pos[i], i, dim*dim);
  }
  //testing();  
}  

inline void cube::permute(uint8_t f, bool i) {
  uint8_t* s1;
  uint8_t* s2;
  uint8_t* s3;
  uint8_t *s4;
  
  switch (f) {
  case 0:
    s1 = m_pos[1][0];
    s2 = m_pos[2][0];
    s3 = m_pos[3][0];
    s4 = m_pos[4][0];
    break;    
  case 5:
    s1 = m_pos[1][2];
    s2 = m_pos[2][2];
    s3 = m_pos[3][2];
    s4 = m_pos[4][0];
    break;
  case 3:
    s1 = m_pos[0][0];
    s2 = m_pos[2][0];
    s3 = m_pos[5][0];
    s4 = m_pos[4][0];
    break;
  case 1:
    s1 = m_pos[0][0];
    s2 = m_pos[2][0];
    s3 = m_pos[5][0];
    s4 = m_pos[4][0];
    break;
  case 2:
    s1 = m_pos[0][2];
    s2 = m_pos[1][2];
    s3 = m_pos[5][2];
    s4 = m_pos[3][2];
    break;
  case 4:
    s1 = m_pos[0][0];
    s2 = m_pos[1][0];
    s3 = m_pos[5][0];
    s4 = m_pos[3][0];
    break;
  default:
    cerr << "INVALID PERMUTION" << endl;    
  }

  uint8_t tmp[dim];
  if (!i) {
    memcpy(tmp, s1, dim);
    memcpy(s1, s2, dim);
    memcpy(s2, s3, dim);
    memcpy(s3, s4, dim);
    memcpy(s4, tmp, dim);  
  }
  else {
    memcpy(tmp, s4, dim);
    memcpy(s4, s3, dim);
    memcpy(s3, s2, dim);
    memcpy(s2, s1, dim);
    memcpy(s1, tmp, dim);
  }
}

void cube::rotatecw(uint8_t f) {
  uint8_t (*mat)[dim] = m_pos[f];
  for (size_t i = 0; i < dim / 2; ++i) {
    for (size_t j = i; j < dim - i - 1; ++j) {
      uint8_t temp = mat[i][j];
      mat[i][j] = mat[dim - 1 - j][i];
      mat[dim - 1 - j][i] = mat[dim - 1 - i][dim - 1 - j];
      mat[dim - 1 - i][dim - 1 - j] = mat[j][dim - 1 - i];
      mat[j][dim - 1 - i] = temp;
    }
  }
}
void cube::rotateccw(uint8_t f) {
  rotatecw(f);
  rotatecw(f);
  rotatecw(f);  
}

void cube::turn(char c, bool invert) {
  switch (c) {
  case 'r':
    rotateccw(0);
    rotateccw(2);
    rotateccw(5);
    rotatecw(4);
    
    permute(3, invert);
    if(!invert)
      rotatecw(3);
    else
      rotateccw(3);
    
    rotatecw(0);
    rotatecw(2);
    rotatecw(5);
    rotateccw(4);    
    break;
  case 'l':
    rotatecw(0);
    rotatecw(2);
    rotatecw(5);
    rotateccw(4);

    permute(1, !invert);
    if (!invert)
      rotatecw(1);
    else
      rotateccw(1);

    rotateccw(0);
    rotateccw(2);
    rotateccw(5);
    rotatecw(4);    
    break;
  case 'u':  
    permute(0, invert);
    if(!invert)
      rotatecw(0);
    else
      rotateccw(0);
    break;
  case 'd':
    permute(5, !invert);
    if (!invert)
      rotatecw(5);
    else
      rotateccw(5);      
    break;
  case 'f':
    rotateccw(3);
    rotatecw(1);
    rotatecw(5);
    rotatecw(5);        

    permute(2, invert);
    if (!invert)
      rotatecw(2);
    else
      rotateccw(2);
    
    rotatecw(3);
    rotateccw(1);
    rotatecw(5);
    rotatecw(5);        
    break;
  case 'b':
    rotateccw(3);
    rotatecw(1);
    rotatecw(5);
    rotatecw(5);        

    permute(4, !invert);
    if (invert)
      rotatecw(4);
    else
      rotateccw(4);
    
    rotatecw(3);
    rotateccw(1);
    rotatecw(5);
    rotatecw(5);            
    break;    
  default:
    cerr << "IVALID" << endl;
    break;    
  }    
}  

void cube::printCube() {
  constexpr char lut[] = { 'w','r','b','o','g','y' };
  // --- White (top) ---
  for (size_t row = 0; row < dim; ++row) {
    for (size_t s = 0; s < dim; ++s) {
      cout << " ";
    }
    cout << " ";    
    for (size_t col = 0; col < dim; ++col) {
      cout << lut[m_pos[0][row][col]];
    }
    cout << "\n";
  }
  // --- Middle faces: Red, Blue, Orange, Green ---
  for (size_t row = 0; row < dim; ++row) {
    for (size_t face = 1; face <= 4; ++face) {
      for (size_t col = 0; col < dim; ++col) {
        cout << lut[m_pos[face][row][col]];
      }
      cout << " ";
    }
    cout << "\n";
  }

  // --- Yellow (bottom) ---
  for (size_t row = 0; row < dim; ++row) {
    for (size_t s = 0; s < dim; ++s) {
      cout << " ";
    }
    cout << " ";    
    for (size_t col = 0; col < dim; ++col) {
      cout << lut[m_pos[5][row][col]];
    }
    cout << "\n";
  }
  cout << endl;  
}
