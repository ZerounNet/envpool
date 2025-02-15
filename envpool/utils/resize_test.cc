// Copyright 2021 Garena Online Private Limited
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "envpool/utils/resize.h"

#include <glog/logging.h>
#include <gtest/gtest.h>

#include <vector>

TEST(ResizeTest, Correctness) {
  // shape
  Array a(Spec<uint8_t>({4, 3, 1}));
  Array b(Spec<uint8_t>({6, 7, 1}));
  Resize(a, &b);
  EXPECT_EQ(b.Shape(), std::vector<std::size_t>({6, 7, 1}));
  EXPECT_NE(a.data(), b.data());
  // same shape, no reference
  Array a2(Spec<uint8_t>({4, 3, 2}));
  a2(1, 0, 1) = 6;
  a2(3, 1, 0) = 4;
  Array b2(Spec<uint8_t>({4, 3, 2}));
  Resize(a2, &b2);
  EXPECT_EQ(a2.Shape(), b2.Shape());
  EXPECT_NE(a2.data(), b2.data());
  EXPECT_EQ(6, static_cast<int>(b2(1, 0, 1)));
  EXPECT_EQ(4, static_cast<int>(b2(3, 1, 0)));
}
