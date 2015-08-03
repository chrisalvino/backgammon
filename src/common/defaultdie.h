
#ifndef DEFAULT_H__
#define DEFAULT_H__

#include "die.h"

namespace zeno {

	class DefaultDie : public Die {

	public:
		DefaultDie();

		virtual ~DefaultDie();

		virtual int getDieRoll();

	};

}


#endif // DEFAULT_H__