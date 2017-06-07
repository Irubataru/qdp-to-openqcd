
/*
 * Created: 07-06-2017
 * Modified: Wed 07 Jun 2017 16:05:33 BST
 * Author: Jonas R. Glesaaen (jonas@glesaaen.com)
 */

#ifndef TYPES_HPP
#define TYPES_HPP

#include <qdp.h>
extern "C" {
#include "su3.h"
}

namespace fastsum {

using QDP_Gauge_Field = QDP::multi1d<QDP::LatticeColorMatrixD>;
using OpenQCD_Gauge_Field = su3_dble*;

} // namespace fastsum 


#endif /* TYPES_HPP */
