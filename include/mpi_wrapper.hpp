
/*
 * Created: 05-06-2017
 * Modified: Mon 05 Jun 2017 16:26:52 BST
 * Author: Jonas R. Glesaaen (jonas@glesaaen.com)
 */

#ifndef MPI_WRAPPER_HPP
#define MPI_WRAPPER_HPP

#include <mpi.h>

namespace fastsum {

class Mpi_Wrapper
{
public:
  Mpi_Wrapper(int argc, char **argv) noexcept { /*MPI_Init(&argc, &argv);*/ }

  static int comm_size() noexcept
  {
    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    return comm_size;
  }

  static int my_rank() noexcept
  {
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    return my_rank;
  }

  ~Mpi_Wrapper() noexcept { /*MPI_Finalize();*/ }

private:
};

} // namespace fastsum

#endif /* MPI_WRAPPER_HPP */
