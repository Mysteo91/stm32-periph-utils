// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// A sample program demonstrating using Google C++ testing framework.

// This sample shows how to write a simple unit test for a function,
// using Google C++ testing framework.
//
// Writing a unit test using Google C++ testing framework is easy as 1-2-3:

// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include <iostream>
#include <string>
#include <limits.h>
#include "serial.h"
#include "gtest/gtest.h"
#include <random>

ceSerial serial;

namespace {


// Step 2. Use the TEST macro to define your tests.
//
// TEST has two parameters: the test case name and the test name.
// After using the macro, you should define your test logic between a
// pair of braces.  You can use a bunch of macros to indicate the
// success or failure of a test.  EXPECT_TRUE and EXPECT_EQ are
// examples of such macros.  For a complete list, see gtest.h.
//
// <TechnicalDetails>
//
// In Google Test, tests are grouped into test cases.  This is how we
// keep test code organized.  You should put logically related tests
// into the same test case.
//
// The test case name and the test name should both be valid C++
// identifiers.  And you should not use underscore (_) in the names.
//
// Google Test guarantees that each test you define is run exactly
// once, but it makes no guarantee on the order the tests are
// executed.  Therefore, you should write your tests in such a way
// that their results don't depend on their order.
//
// </TechnicalDetails>

// Tests Factorial().

// Tests factorial of negative numbers.

TEST(UartTest, RandomByte) {
  std::random_device engine;
  char symbolTx = 0;
  char symbolRx;
  bool success;
  for (uint32_t i = 0; i < BYTES_COUNT_FOR_TRANSMIT; i++) {
    while ((symbolTx = engine() ) == 0) {

    }
    if (serial.Write(&symbolTx)) {
      symbolRx = serial.ReadChar(success);
      if (success) {
        ASSERT_EQ(symbolTx, symbolRx);
      }
      else
        ASSERT_EQ(success, true);
    }
    else
      FAIL();
  }
}

}  // namespace

using namespace std;




int main(int argc, char **argv) {
  std::string serialName ;
  if (argc <= 2) {
    cout << "Please run tests with serialport name i.e COM2" << endl;
    return -1;
  }
  serialName.append(argv[1]);
  size_t npos = serialName.find("COM",0);
  if ( npos == std::string::npos || npos != 0) {
    cout << "You run tests with" << serialName << "it is not corresponding to COMx" << endl;
    return -1;
  }
  serial = ceSerial("\\\\.\\" + serialName,921600,8,'N',1);
  cout << "Trying to open " << serialName << "...";
  if (serial.Open() == 0 ) {
    cout << "OK" << endl;
  }
  else {
    cout << "Cant Open" << serialName << endl;
    return -1;
  }
  testing::InitGoogleTest();
  RUN_ALL_TESTS();
}



// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
//
// This runs all the tests you've defined, prints the result, and
// returns 0 if successful, or 1 otherwise.
//
// Did you notice that we didn't register the tests?  The
// RUN_ALL_TESTS() macro magically knows about all the tests we
// defined.  Isn't this convenient?