
/*
 * Created: 02-06-2017
 * Modified: Tue 06 Jun 2017 13:37:31 BST
 * Author: Jonas R. Glesaaen (jonas@glesaaen.com)
 */

// Needed to define all OpenQCD global arrays
#define MAIN_PROGRAM

#include "chroma_to_openqcd.hpp"

using namespace fastsum;

const std::string xml_geometry_tag = "/HMC/ProgramInfo/Setgeom";
const std::string xml_lattice_size_tag = "latt_size";

int main(int argc, char **argv)
{
  QDP_Instance_Wrapper qdp_instance {argc, argv};

  if (QDP_Instance_Wrapper::MPI::comm_size() > 1 or NPROC != 1) {
    std::cerr << "This program only works in serial" << std::endl;
    return 1;
  }

  OpenQCD::Initialise();
  init_qdp_lattice_geometry();

  std::string in_filename{"input_config.lime"};

  QDP_Gauge_Field qdp_gauge_field(4);

  try {
    read_qdp_gauge_field(qdp_gauge_field, in_filename);
  } catch (std::exception &err) {
    std::cerr << err.what() << std::endl;
    return 1;
  }
}

void init_qdp_lattice_geometry()
{
  QDP::multi1d<int> nrow(4);
  nrow[0] = NPROC1 * L1;
  nrow[1] = NPROC2 * L2;
  nrow[2] = NPROC3 * L3;
  nrow[3] = NPROC0 * L0;

  QDP::Layout::setLattSize(nrow);
  QDP::Layout::create();
}

void read_qdp_gauge_field(QDP_Gauge_Field &gauge_field, std::string filename)
{
  QDP::XMLReader lime_xml_header{};
  QDP::QDPFileReader lime_reader{lime_xml_header, filename, QDP::QDPIO_SERIAL};

  check_input_geometry(lime_xml_header);

  QDP::XMLReader lime_xml_record{};
  QDP::read(lime_reader, lime_xml_record, gauge_field);

  if (lime_reader.bad())
    throw std::runtime_error{"Errors reading input config file"};
}

void check_input_geometry(QDP::XMLReader &lime_xml_header)
{
  QDP::XMLReader lime_geom{lime_xml_header, xml_geometry_tag};

  QDP::multi1d<int> lime_rows;
  QDP::read(lime_geom, xml_lattice_size_tag, lime_rows);

  if ((lime_rows[0] != NPROC1 * L1) or (lime_rows[1] != NPROC2 * L2) or
      (lime_rows[2] != NPROC3 * L3) or (lime_rows[3] != NPROC0 * L0))
    throw std::runtime_error{"openqcd and input file geometry mismatch"};
}
