#pragma once

#include "mpicpp-lite/mpicpp-lite.h"
#include "pybind11/embed.h"
#include <string>

namespace mpi = mpicpp_lite;
namespace py = pybind11;

namespace diffpy
{

class DiffApp
{
public:
  explicit DiffApp(const mpi::Communicator& comm);
  int Run(int argc, char** argv);

private:
  int InitPETSc(int argc, char** argv);
  bool ProcessArguments(int argc, char** argv);

  bool allow_petsc_error_handler_;
};

} // namespace diffpy