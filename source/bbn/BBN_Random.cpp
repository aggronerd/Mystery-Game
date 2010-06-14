#include "BBN_Random.h"
#include <ClanLib/core.h>
#include <string.h>

dlib::rand_float_1<dlib::rand_kernel_1>* BBN_Random::_rand = 0x0;

float BBN_Random::get_next_float()
{
  if(_rand == 0x0)
  {
    _rand = new dlib::rand_float_1<dlib::rand_kernel_1>();
	CL_String seed = CL_StringHelp::uint_to_text(CL_System::get_time());
	//Need to convert to std::string to satisfy fussy compilers.
	std::string seed_std((char*)seed.c_str());
	_rand->set_seed(seed_std);
  }
  return(BBN_Random::_rand->get_random_float());
}

/**
 * Destroys current rand generator used. Should be called when finished generating random floats.
 */
void BBN_Random::reset()
{
  if(_rand != 0x0)
    delete(_rand);
  _rand = 0x0;
}
