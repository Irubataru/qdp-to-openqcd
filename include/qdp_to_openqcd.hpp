
/*
 * Created: 02-06-2017
 * Modified: Wed 07 Jun 2017 14:50:30 BST
 * Author: Jonas R. Glesaaen (jonas@glesaaen.com)
 */

#ifndef QDP_TO_OPENQCD_HPP
#define QDP_TO_OPENQCD_HPP

#include <openqcd_utilities.hpp>

extern "C" {
#include "uflds.h"
}

#include <iostream>
#include <mpi.h>
#include <qdp.h>
#include <qdp_converters.hpp>
#include <qdp_instance_wrapper.hpp>
#include <openqcd_archive.hpp>

namespace fastsum {

struct Program_Parameters
{
  std::string input_file;
  std::string output_file;
};

void init_qdp_lattice_geometry();
void read_qdp_gauge_field(QDP_Gauge_Field &gauge_field, std::string filename);
void check_input_geometry(QDP::XMLReader &lime_xml_header);
void print_help_message();
Program_Parameters parse_input_arguments(int arc, char **argv);

} // namespace fastsum

#endif /* QDP_TO_OPENQCD_HPP */
