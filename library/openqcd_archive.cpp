
/*
 * Created: 06-06-2017
 * Modified: Tue 06 Jun 2017 17:03:33 BST
 * Author: Jonas R. Glesaaen (jonas@glesaaen.com)
 */

#include <openqcd_archive.hpp>
#include <stdexcept>

extern "C" {
#include "archive.h"
}

namespace fastsum {

void export_openqcd_config(std::string filename)
{
  if (!check_bc(0.0) or chs_ubnd(1))
    throw std::runtime_error {"Unexpeced boundary values for OpenQCD config"};

  // export_cnfg does not change the string, but it is not declared const
  export_cnfg(const_cast<char*>(filename.c_str()));
}

} // namespace fastsum 
