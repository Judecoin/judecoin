// Copyright (c) 2024, The Judecoin Project
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

#include "gtest/gtest.h"
#include "cryptonote_basic/cryptonote_format_utils.h"
#include "cryptonote_basic/cryptonote_basic_impl.h"
#include "common/varint.h"

using namespace cryptonote;

TEST(cn_format_utils, add_extra_nonce_to_tx_extra)
{
  for (size_t nonce_size = 0; nonce_size <= TX_EXTRA_NONCE_MAX_COUNT + 1; ++nonce_size)
  {
    for (int with_pub_key = 0; with_pub_key < 2; ++with_pub_key)
    {
      std::vector<uint8_t> tx_extra;
      if (with_pub_key)
      {
        tx_extra.resize(1 + sizeof(crypto::public_key));
        tx_extra[0] = TX_EXTRA_TAG_PUBKEY;
      }

      std::string extra_nonce(nonce_size, 'A');
      bool r = add_extra_nonce_to_tx_extra(tx_extra, extra_nonce);
      if (nonce_size > TX_EXTRA_NONCE_MAX_COUNT)
      {
        ASSERT_FALSE(r);
        continue;
      }
      ASSERT_TRUE(r);

      // Check tag
      size_t pos = with_pub_key ? 1 + sizeof(crypto::public_key) : 0;
      ASSERT_EQ(tx_extra[pos], TX_EXTRA_NONCE);
      ++pos;

      // Read varint length
      uint64_t stored_len;
      std::string::const_iterator it = reinterpret_cast<const char*>(tx_extra.data()) + pos;
      int bytes = tools::read_varint(it, reinterpret_cast<const char*>(tx_extra.data()) + tx_extra.size(), stored_len);
      ASSERT_GT(bytes, 0);
      ASSERT_EQ(stored_len, extra_nonce.size());
      pos += bytes;

      // Check data
      ASSERT_EQ(tx_extra.size() - pos, extra_nonce.size());
      ASSERT_EQ(memcmp(tx_extra.data() + pos, extra_nonce.data(), extra_nonce.size()), 0);
    }
  }
}

TEST(cn_format_utils, add_mm_merkle_root_to_tx_extra)
{
  // Test merkle tree depths: 0 through 10, and some boundary values
  const std::vector<uint64_t> depths = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 63, 64, 127, 128, 16383, 16384};
  for (uint64_t depth : depths)
  {
    crypto::hash merkle_root = crypto::rand<crypto::hash>();
    std::vector<uint8_t> tx_extra;
    bool r = add_mm_merkle_root_to_tx_extra(tx_extra, merkle_root, depth);
    ASSERT_TRUE(r);

    // Verify tag
    ASSERT_EQ(tx_extra[0], TX_EXTRA_MERGE_MINING_TAG);

    // Verify merkle root
    ASSERT_EQ(memcmp(tx_extra.data() + 1, &merkle_root, 32), 0);

    // Verify varint encoded depth
    uint64_t stored_depth;
    std::string::const_iterator it = reinterpret_cast<const char*>(tx_extra.data()) + 1 + 32;
    int bytes = tools::read_varint(it, reinterpret_cast<const char*>(tx_extra.data()) + tx_extra.size(), stored_depth);
    ASSERT_GT(bytes, 0);
    ASSERT_EQ(stored_depth, depth);
  }
}

TEST(cn_format_utils, tx_extra_merge_mining_tag_store_load)
{
  crypto::hash mm_merkle_root = crypto::rand<crypto::hash>();
  uint64_t mm_merkle_tree_depth = 128;

  std::vector<uint8_t> tx_extra;
  bool r = add_mm_merkle_root_to_tx_extra(tx_extra, mm_merkle_root, mm_merkle_tree_depth);
  ASSERT_TRUE(r);

  // Serialize and deserialize to verify round-trip
  std::string serialized;
  serialized.assign(reinterpret_cast<const char*>(tx_extra.data()), tx_extra.size());

  // Parse back
  crypto::hash parsed_root;
  uint64_t parsed_depth;
  size_t pos = 1; // skip tag
  memcpy(&parsed_root, serialized.data() + pos, 32);
  pos += 32;
  std::string::const_iterator it = serialized.begin() + pos;
  int bytes = tools::read_varint(it, serialized.end(), parsed_depth);
  ASSERT_GT(bytes, 0);

  ASSERT_EQ(parsed_root, mm_merkle_root);
  ASSERT_EQ(parsed_depth, mm_merkle_tree_depth);
}
