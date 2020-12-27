// Copyright (c) 2020 by Apex.AI Inc. All rights reserved.
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

#include "iceoryx_utils/internal/cxx/function.hpp"
#include "test.hpp"

#include <iostream>

using namespace ::testing;
using namespace iox::cxx;

namespace
{
using std::cout;
using std::endl;

using signature = int32_t(int32_t);
template <typename T>
using fixed_size_function = iox::cxx::function<T, 128>;
using test_function = fixed_size_function<signature>;

class Functor
{
  public:
    Functor(int32_t state)
        : m_state(state)
    {
    }

    int32_t operator()(int32_t n)
    {
        m_state += n;
        return m_state;
    }

    int32_t m_state{0};
};

int32_t freeFunction(int32_t n)
{
    return n + 1;
};


class function_test : public Test
{
  public:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    static int32_t staticFunction(int32_t n)
    {
        return n + 1;
    }
};

TEST_F(function_test, DefaultConstructionCreatesNoCallable)
{
    test_function sut;

    EXPECT_FALSE(sut.operator bool());
}

TEST_F(function_test, ConstructionFromFunctorIsCallable)
{
    Functor f(73);
    test_function sut(f);

    ASSERT_TRUE(sut.operator bool());
    EXPECT_EQ(sut(1), f(1));
}

TEST_F(function_test, ConstructionFromLambdaIsCallable)
{
    int32_t capture = 37;
    auto lambda = [state = capture](int32_t n) { return state + n; };
    test_function sut(lambda);

    ASSERT_TRUE(sut.operator bool());
    EXPECT_EQ(sut(1), lambda(1));
}

TEST_F(function_test, ConstructionFromFreeFunctionIsCallable)
{
    test_function sut(freeFunction);

    ASSERT_TRUE(sut.operator bool());
    EXPECT_EQ(sut(1), freeFunction(1));
}

TEST_F(function_test, ConstructionFromStaticFunctionIsCallable)
{
    // is essentially also a free function but we test the case to be sure
    test_function sut(staticFunction);

    ASSERT_TRUE(sut.operator bool());
    EXPECT_EQ(sut(1), staticFunction(1));
}

TEST_F(function_test, FunctionStateIsIndependentOfSource)
{
    constexpr uint32_t INITIAL_STATE = 73U;
    static_storage<1024> storage;
    auto p = storage.allocate<Functor>();
    auto f = new (p) Functor(INITIAL_STATE);
    auto& functor = *f;

    // test whether the function really owns the functor
    // (no dependency or side effects)
    test_function sut(functor);

    ASSERT_TRUE(sut.operator bool());

    // both increment their state independently
    EXPECT_EQ(sut(1U), functor(1U));

    // clear original (set to 0)
    f->~Functor();
    storage.clear();

    EXPECT_EQ(sut(1U), INITIAL_STATE + 2U);
}

} // namespace