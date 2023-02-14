/* Copyright 2023 The TensorFlow Authors. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include <memory>

#include "mlir/IR/BuiltinOps.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"  // from @llvm-project
#include "mlir/IR/PatternMatch.h"  // from @llvm-project
#include "mlir/IR/Visitors.h"  // from @llvm-project
#include "mlir/Support/LogicalResult.h"  // from @llvm-project
#include "tensorflow/compiler/mlir/tensorflow/ir/tf_ops.h"
#include "tensorflow/compiler/mlir/xla/transforms/passes.h"

namespace mlir {
namespace mhlo {

namespace {

#define GEN_PASS_DEF_TFXLADEVICESPECIFICTRANSFORMS
#include "tensorflow/compiler/mlir/xla/transforms/xla_legalize_tf_passes.h.inc"

class TFXLADeviceSpecificTransforms
    : public impl::TFXLADeviceSpecificTransformsBase<
          TFXLADeviceSpecificTransforms> {
 public:
  explicit TFXLADeviceSpecificTransforms(
      llvm::Optional<StringRef> device_type) {
    if (device_type.has_value()) {
      device_type_ = device_type.value().str();
    }
  }
  void runOnOperation() override;

 private:
};

void TFXLADeviceSpecificTransforms::runOnOperation() {}

}  // namespace

std::unique_ptr<mlir::OperationPass<mlir::func::FuncOp>>
CreateTFXLADeviceSpecificTransformsPass(llvm::Optional<StringRef> device_type) {
  return std::make_unique<TFXLADeviceSpecificTransforms>(device_type);
}

}  // namespace mhlo
}  // namespace mlir
