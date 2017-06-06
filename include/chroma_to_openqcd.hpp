
/*
 * Created: 02-06-2017
 * Modified: Tue 06 Jun 2017 13:42:54 BST
 * Author: Jonas R. Glesaaen (jonas@glesaaen.com)
 */

#ifndef CHROMA_TO_OPENQCD_HPP
#define CHROMA_TO_OPENQCD_HPP

extern "C" {
#include "global.h"
}

#include <iostream>
#include <mpi.h>
#include <qdp.h>
#include <qdp_instance_wrapper.hpp>
#include <openqcd_utilities.hpp>

using QDP_Gauge_Field = QDP::multi1d<QDP::LatticeColorMatrixD>;

void init_qdp_lattice_geometry();
void read_qdp_gauge_field(QDP_Gauge_Field &gauge_field, std::string filename);
void check_input_geometry(QDP::XMLReader &lime_xml_header);

#endif /* CHROMA_TO_OPENQCD_HPP */
