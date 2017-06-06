
/*
 * Created: 06-06-2017
 * Modified: Tue 06 Jun 2017 13:41:20 BST
 * Author: Jonas R. Glesaaen (jonas@glesaaen.com)
 */

#ifndef OPENQCD_UTILITIES_HPP
#define OPENQCD_UTILITIES_HPP

extern "C" {
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "global.h"
#include "su3.h"
#include "flags.h"
#include "lattice.h"
}

namespace fastsum {

namespace OpenQCD {

inline void Initialise()
{
  set_bc_parms(3, 0., 0., 0., 0., nullptr, nullptr);
  geometry();
}

inline bool Is_Initialised()
{
  return iup[0][0] != 0;
}

} // namespace OpenQCD 

} // namespace fastsum 

#endif /* OPENQCD_UTILITIES_HPP */
