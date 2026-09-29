// SPDX-FileCopyrightText: 2025 The OpenSn Authors <https://open-sn.github.io/opensn/>
// SPDX-License-Identifier: MIT

#include "diff_py_app.h"
#include "mpicpp-lite/mpicpp-lite.h"
#include "petsc.h"
#include <cstdlib>
#include <iostream>

int
main(int argc, char** argv)
{
  mpi::Environment env(argc, argv, mpi::ThreadSupport::MULTIPLE);

  PetscCall(PetscInitializeNoArguments()); // NOLINT(bugprone-casting-through-void)

  int retval = EXIT_SUCCESS;
  try
  {
    py::scoped_interpreter guard{};
    diffpy::DiffApp app(MPI_COMM_WORLD); // NOLINT(bugprone-casting-through-void)
    retval = app.Run(argc, argv);
  }
  catch (...)
  {
    std::cerr << "Unknown fatal error\n";
    retval = EXIT_FAILURE;
  }

  PetscFinalize();

  return retval;
}
