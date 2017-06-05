
/*
 * Created: 05-06-2017
 * Modified: Mon 05 Jun 2017 17:32:58 BST
 * Author: Jonas R. Glesaaen (jonas@glesaaen.com)
 */

#ifndef QDP_INSTANCE_WRAPPER_HPP
#define QDP_INSTANCE_WRAPPER_HPP

#include <mpi.h>
#include <qdp.h>
#include "qdp_stream_redirect.hpp"

namespace fastsum {

class QDP_Instance_Wrapper
{
public:
  QDP_Instance_Wrapper(int argc, char **argv)
    : stream_redirect_{"/dev/null"}
  {
    QDP::QDP_initialize(&argc, &argv);

    if (!MPI::initialized())
      MPI_Init(&argc, &argv);
  }

  struct MPI
  {
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

    static bool initialized() noexcept
    {
      int initialized_;
      MPI_Initialized(&initialized_);
      return static_cast<bool>(initialized_);
    }

    static bool finalized() noexcept
    {
      int finalized_;
      MPI_Finalized(&finalized_);
      return static_cast<bool>(finalized_);
    }

  };

  ~QDP_Instance_Wrapper()
  {
    QDP::QDP_finalize();

    if (!MPI::finalized())
      MPI_Finalize();
  }

private:
  QDP_Stream_Redirect stream_redirect_;
};

} // namespace fastsum

#endif /* QDP_INSTANCE_WRAPPER_HPP */
