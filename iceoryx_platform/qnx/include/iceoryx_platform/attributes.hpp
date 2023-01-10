// Copyright (c) 2021 - 2022 by Apex.AI Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#ifndef IOX_HOOFS_QNX_PLATFORM_ATTRIBUTES_HPP
#define IOX_HOOFS_QNX_PLATFORM_ATTRIBUTES_HPP

/// @todo iox-#638
#define IOX_NO_DISCARD

/// @brief IOX_FALLTHROUGH adds the [[fallthrough]] keyword when it is available for the current compiler.
/// @note
//    [[fallthrough]] supported since gcc 7 (https://gcc.gnu.org/projects/cxx-status.html)
///   [[fallthrough]] supported since clang 3.9 (https://clang.llvm.org/cxx_status.html)

#if __cplusplus >= 201703L
#define IOX_FALLTHROUGH [[fallthrough]]
#else
#define IOX_FALLTHROUGH
#endif

#define IOX_MAYBE_UNUSED [[gnu::unused]]

#endif // IOX_HOOFS_QNX_PLATFORM_ATTRIBUTES_HPP
