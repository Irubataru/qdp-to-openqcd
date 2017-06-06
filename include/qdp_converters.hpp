
/*
 * Created: 05-06-2017
 * Modified: Tue 06 Jun 2017 13:39:25 BST
 * Author: Jonas R. Glesaaen (jonas@glesaaen.com)
 */

#ifndef QDP_CONVERTERS_HPP
#define QDP_CONVERTERS_HPP

#include <qdp.h>

extern "C" {
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "global.h"
#include "su3.h"
}

namespace fastsum {

using QDP_Gauge_Field = QDP::multi1d<QDP::LatticeColorMatrixD>;
using OpenQCD_Gauge_Field = su3_dble*;

void copy(QDP::ColorMatrixD const&from, su3_dble &to);
void copy(QDP_Gauge_Field const& from, OpenQCD_Gauge_Field &to);

} // namespace fastsum 

#endif /* QDP_CONVERTERS_HPP */
