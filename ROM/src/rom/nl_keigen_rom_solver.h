// SPDX-FileCopyrightText: 2026 The OpenSn Authors <https://open-sn.github.io/opensn/>
// SPDX-License-Identifier: MIT

#pragma once

#include "modules/solver.h"
#include "modules/linear_boltzmann_solvers/discrete_ordinates_problem/discrete_ordinates_problem.h"
#include "modules/linear_boltzmann_solvers/discrete_ordinates_problem/solvers/nl_keigen_solver.h"
#include "rom_problem.h"

namespace opensn
{

class NLKEigenROMSolver : public Solver
{
protected:
  std::shared_ptr<DiscreteOrdinatesProblem> lbs_problem_;
  std::shared_ptr<ROMProblem> rom_problem_;
  NonLinearKEigenSolver nl_solver_;
  double k_eff_ = 1.0;

public:
  /** Constructs a nonlinear k-eigenvalue ROM solver. */
  explicit NLKEigenROMSolver(const InputParameters& params);

  /** Returns the most recently computed eigenvalue. */
  double GetEigenvalue() const;

  /** Returns the input-parameter schema for NLKEigenROMSolver. */
  static InputParameters GetInputParameters();

protected:
  /** Checks that the transport and ROM problems are set; nl_solver_ validates itself. */
  void ValidateState() const override;
  /** Initializes the underlying nonlinear k-eigenvalue solver. */
  void InitializeSolver() override;
  /** Executes the selected offline, merge, systems, MI-POD, or online ROM phase. */
  void ExecuteSolver() override;
};

} // namespace opensn
