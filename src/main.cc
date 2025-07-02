// SPDX-FileCopyrightText: 2025 The OpenSn Authors <https://open-sn.github.io/opensn/>
// SPDX-License-Identifier: MIT

#include "diff_py_app.h"
#include "opensn/python/lib/py_app.h"
#include "mpicpp-lite/mpicpp-lite.h"

int main(int argc, char** argv)
{
    mpi::Environment env(argc, argv);
    py::scoped_interpreter guard{};
    diffpy::DiffApp app(MPI_COMM_WORLD);
    int error_code = app.Run(argc, argv);
    return error_code;
}