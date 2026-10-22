// SPDX-FileCopyrightText: 2024 The OpenSn Authors <https://open-sn.github.io/opensn/>
// SPDX-License-Identifier: MIT

#pragma once

#include "boundary.h"
#include "opensn/framework/parameters/input_parameters.h"
#include "opensn/modules/solver.h"
#include "opensn/framework/math/petsc_utils/petsc_utils.h"
#include "opensn/framework/math/functions/function.h"

namespace opensn
{

class Mesh;
class SpatialDiscretization;

/**
 * Base class for diffusion solvers
 */
class DiffusionSolverBase : public Solver
{
public:
  /** Class for diffusion boundaries */
  class Boundary
  {
  public:
    Boundary();
    Boundary(BoundaryType type, const std::array<double, 3>& values);

    BoundaryType type;
    std::array<double, 3> values;
  };

  explicit DiffusionSolverBase(const std::string& name, std::shared_ptr<Mesh> grid_ptr);
  explicit DiffusionSolverBase(const InputParameters& params);
  ~DiffusionSolverBase() override;

  /**
   * Updates the field functions with the latest data.
   */
  void UpdateFieldFunctions();

  const std::vector<std::shared_ptr<FieldFunctionGridBased>>& GetFieldFunctions() const;

  void SetDCoefFunction(const ScalarSpatialMaterialFunction& function)
  {
    d_coef_function_ = function;
  }
  void SetQExtFunction(const ScalarSpatialMaterialFunction& function)
  {
    q_ext_function_ = function;
  }
  void SetSigmaAFunction(const ScalarSpatialMaterialFunction& function)
  {
    sigma_a_function_ = function;
  }

  void SetOptions(const InputParameters& params);
  virtual void SetBoundaryOptions(const InputParameters& params) = 0;

protected:
  /// Checks that the grid and the material functions are set.
  void ValidateState() const override;

  void InitFieldFunctions();
  void ValidateMaterialFunctions() const;

  using BoundaryInfo = std::pair<BoundaryType, std::vector<double>>;
  using BoundaryPreferences = std::map<std::string, BoundaryInfo>;

  std::shared_ptr<Mesh> grid_ptr_;
  std::shared_ptr<SpatialDiscretization> sdm_ptr_;
  size_t num_local_dofs_;
  size_t num_global_dofs_;
  /// approx solution
  Vec x_;
  /// RHS
  Vec b_;
  /// linear system matrix
  Mat A_;

  std::map<uint64_t, Boundary> boundaries_;
  BoundaryPreferences boundary_preferences_;

  ScalarSpatialMaterialFunction d_coef_function_;
  ScalarSpatialMaterialFunction sigma_a_function_;
  ScalarSpatialMaterialFunction q_ext_function_;

  std::vector<std::shared_ptr<FieldFunctionGridBased>> field_functions_;

  double residual_tolerance_ = 1.0e-2;
  int64_t max_iters_ = 500;

public:
  static InputParameters GetInputParameters();
  static InputParameters GetOptionsBlock();
  static InputParameters GetBoundaryOptionsBlock();
};

} // namespace opensn
