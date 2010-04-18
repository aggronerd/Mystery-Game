#include "BBN_Random.h"

dlib::rand_float_1<dlib::rand_kernel_1>* BBN_Random::_rand = 0x0;

float BBN_Random::get_next_float()
{
  if(_rand == 0x0)
    _rand = new dlib::rand_float_1<dlib::rand_kernel_1>();

  return(BBN_Random::_rand->get_random_float());
}

