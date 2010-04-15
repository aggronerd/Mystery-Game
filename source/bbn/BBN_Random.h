#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BBN_Random_h__
#define __BBN_Random_h__

namespace BBN_Plot
{
	class BBN_Random;
}

namespace BBN_Plot
{
	class BBN_Random
	{

		public: static float get_next_float() {
			throw "Not yet implemented";
		}

		public: static void set_seed(int seed) {
			throw "Not yet implemented";
		}
	};
}

#endif
