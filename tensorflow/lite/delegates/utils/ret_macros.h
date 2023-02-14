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
#ifndef TENSORFLOW_LITE_DELEGATES_UTILS_RET_MACROS_H_
#define TENSORFLOW_LITE_DELEGATES_UTILS_RET_MACROS_H_

#include "absl/log/log.h"
#include "tensorflow/lite/core/c/c_api_types.h"

// Evaluate an expression whose type is std::optional<T>. If it returns an
// instance that contains a value, then initialize the declaration with that
// value; otherwise, return the specified error value.
#define TFLITE_ASSIGN_OR_RETURN(declaration, expr, err)                \
  TFLITE_ASSIGN_OR_RETURN_IMPL(                                        \
      TFLITE_ASSIGN_OR_RETURN_MACROS_CONCAT_NAME(_maybe, __COUNTER__), \
      declaration, expr, err);

#define TFLITE_ASSIGN_OR_RETURN_IMPL(maybe, declaration, expr, err) \
  auto maybe = (expr);                                              \
  if (!maybe.has_value()) return (err);                             \
  declaration = *std::move(maybe)

#define TFLITE_ASSIGN_OR_RETURN_MACROS_CONCAT_NAME(x, y) \
  TFLITE_ASSIGN_OR_RETURN_MACROS_CONCAT_IMPL(x, y)
#define TFLITE_ASSIGN_OR_RETURN_MACROS_CONCAT_IMPL(x, y) x##y

// If the specified condition is false, log the specified message and return the
// specified error value.
#define TFLITE_RET_CHECK(c, m, r) \
  TFLITE_RET_CHECK_IMPL(c, m, r, __FILE__, __LINE__)

#define TFLITE_RET_CHECK_IMPL(c, m, r, file, line)                      \
  do {                                                                  \
    if (!(c)) {                                                         \
      LOG(ERROR) << "TFLITE_RET_CHECK failure (" << file << ":" << line \
                 << ") " #c " \"" << m << "\"";                         \
      return (r);                                                       \
    }                                                                   \
  } while (false)

// If the specified condition is false, log the specified message and return
// kTfLiteDelegateError.
#define TFLITE_RET_CHECK_STATUS(c, m) \
  TFLITE_RET_CHECK(c, m, kTfLiteDelegateError)

#endif  // TENSORFLOW_LITE_DELEGATES_UTILS_RET_MACROS_H_
