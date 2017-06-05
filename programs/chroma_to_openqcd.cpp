
/*
 * Created: 02-06-2017
 * Modified: Mon 05 Jun 2017 15:05:51 BST
 * Author: Jonas R. Glesaaen (jonas@glesaaen.com)
 */

#include "chroma_to_openqcd.hpp"

const std::string xml_geometry_tag = "/HMC/ProgramInfo/Setgeom";
const std::string xml_lattice_size_tag = "latt_size";

int main(int argc, char **argv)
{
  QDP::QDP_initialize(&argc, &argv);
  fastsum::QDP_stream_redirect redirect {"/dev/null"};

  std::string in_filename {"input_config.lime"};
  QDP::multi1d<int> nrow (4);
  nrow[0] = 8;
  nrow[1] = 8;
  nrow[2] = 8;
  nrow[3] = 8;

  QDP::Layout::setLattSize(nrow);
  QDP::Layout::create();

  QDP::XMLReader lime_xml_header {};
  QDP::QDPFileReader lime_reader {lime_xml_header, in_filename, QDP::QDPIO_SERIAL};

  QDP::XMLReader lime_geom {lime_xml_header, xml_geometry_tag};
  QDP::multi1d<int> lime_rows;
  QDP::read(lime_geom, xml_lattice_size_tag, lime_rows);

  std::cout << "Printing lime geometry:" << std::endl;
  for (auto i = 0ul; i < nrow.size(); ++i)
    std::cout << nrow[i] << " ";

  std::cout << std::endl;

  QDP::QDP_finalize();
}
