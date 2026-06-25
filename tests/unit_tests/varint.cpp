// Copyright (c) 2014-2026, The Judecoin Project
// 
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// Parts of this file are originally copyright (c) 2012-2013 The Cryptonote developers

#include <cstring>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <vector>
#include <boost/foreach.hpp>
#include "common/varint.h"
#include "cryptonote_basic/cryptonote_basic.h"
#include "cryptonote_basic/cryptonote_basic_impl.h"
#include "serialization/binary_archive.h"
#include "serialization/json_archive.h"
#include "serialization/debug_archive.h"
#include "serialization/variant.h"
#include "serialization/containers.h"
#include "serialization/binary_utils.h"
#include "gtest/gtest.h"
using namespace std;

TEST(varint, equal)
{
  for (uint64_t idx = 0; idx < 65537; ++idx)
  {
    char buf[12];
    char *bufptr = buf;
    tools::write_varint(bufptr, idx);
    uint64_t bytes = bufptr - buf;
    ASSERT_TRUE (bytes > 0 && bytes <= sizeof(buf));

    uint64_t idx2;
    std::string s(buf, bytes);
    int read = tools::read_varint(s.begin(), s.end(), idx2);
    ASSERT_EQ (read, bytes);
    ASSERT_TRUE(idx2 == idx);
  }
}

TEST(varint, max_uint64_t_bytes)
{
  const uint64_t max_val = std::numeric_limits<uint64_t>::max();
  ASSERT_EQ(tools::get_varint_byte_size(max_val), 10);
}

TEST(varint, get_varint_byte_size)
{
  // uint8_t boundary values
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint8_t>(0)), 1);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint8_t>(127)), 1);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint8_t>(128)), 2);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint8_t>(255)), 2);

  // uint16_t boundary values
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint16_t>(0)), 1);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint16_t>(127)), 1);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint16_t>(128)), 2);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint16_t>(16383)), 2);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint16_t>(16384)), 3);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint16_t>(65535)), 3);

  // uint32_t boundary values
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint32_t>(0)), 1);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint32_t>(127)), 1);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint32_t>(16383)), 2);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint32_t>(2097151)), 3);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint32_t>(2097152)), 4);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint32_t>(268435455)), 4);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint32_t>(268435456)), 5);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint32_t>(4294967295)), 5);

  // uint64_t boundary values
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint64_t>(0)), 1);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint64_t>(127)), 1);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint64_t>(16383)), 2);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint64_t>(2097151)), 3);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint64_t>(268435455)), 4);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint64_t>(34359738367ULL)), 5);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint64_t>(34359738368ULL)), 6);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint64_t>(4398046511103ULL)), 6);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint64_t>(4398046511104ULL)), 7);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint64_t>(562949953421311ULL)), 7);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint64_t>(562949953421312ULL)), 8);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint64_t>(72057594037927935ULL)), 8);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint64_t>(72057594037927936ULL)), 9);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint64_t>(9223372036854775807ULL)), 9);
  ASSERT_EQ(tools::get_varint_byte_size(static_cast<uint64_t>(9223372036854775808ULL)), 10);
}
