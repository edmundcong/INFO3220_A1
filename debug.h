#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

/*
 * If DEBUG_ENABLED is set, DEBUG() statements will be printed to stdout.
 */

#define DEBUG_ENABLED (0)

#if DEBUG_ENABLED
  #define DEBUG(s) std::cout << s << std::endl;
#else
  #define DEBUG(s) // std::cout << s << std::endl;
#endif

#endif // DEBUG_H

