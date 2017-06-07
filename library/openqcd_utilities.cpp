
/*
 * Created: 07-06-2017
 * Modified: Wed 07 Jun 2017 16:32:52 BST
 * Author: Jonas R. Glesaaen (jonas@glesaaen.com)
 */

#include <openqcd_utilities.hpp>

extern "C" {
#include "uflds.h"
}

namespace fastsum {

double average_plaquette(OpenQCD_Gauge_Field const &)
{
  static constexpr double normalisation = 18. * VOLUME;
  if (!OpenQCD::Is_Initialised())
    throw std::runtime_error{
        "Cannot measure the plaquette before OpenQCD is initialised"};

  return plaq_wsum_dble(0) / normalisation;
}

} // namespace fastsum
