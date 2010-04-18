#include "BBN_Random.h"
#include <ClanLib/core.h>

dlib::rand_float_1<dlib::rand_kernel_1>* BBN_Random::_rand = 0x0;

float BBN_Random::get_next_float()
{
  if(_rand == 0x0)
  {
    _rand = new dlib::rand_float_1<dlib::rand_kernel_1>();
    _rand->set_seed(CL_StringHelp::uint_to_text(CL_System::get_time()));
  }
  return(BBN_Random::_rand->get_random_float());
}

