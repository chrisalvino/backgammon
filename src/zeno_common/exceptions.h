
#ifndef EXCEPTIONS_H__
#define EXCEPTIONS_H__

#include <exception>

namespace zeno {

  class IllegalMoveException : public std::exception {
      
  };

}

#endif // EXCEPTIONS_H__
