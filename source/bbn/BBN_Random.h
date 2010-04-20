#ifndef __BBN_Random_h__
#define __BBN_Random_h__

#include "../dlib/rand.h"

class BBN_Random
{

public:
  static float get_next_float(void);
  static void reset(void);

private:
  static dlib::rand_float_1<dlib::rand_kernel_1>* _rand;

};

#endif
