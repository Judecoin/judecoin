#!/usr/bin/env python3

# Copyright (c) 2019-2026, The Judecoin Project
# 
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without modification, are
# permitted provided that the following conditions are met:
# 
# 1. Redistributions of source code must retain the above copyright notice, this list of
#    conditions and the following disclaimer.
# 
# 2. Redistributions in binary form must reproduce the above copyright notice, this list
#    of conditions and the following disclaimer in the documentation and/or other
#    materials provided with the distribution.
# 
# 3. Neither the name of the copyright holder nor the names of its contributors may be
#    used to endorse or promote products derived from this software without specific
#    prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
# THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
# THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

"""Test address validation RPC calls
"""

from framework.wallet import Wallet

class AddressValidationTest():
    def run_test(self):
       self.create()
       self.check_bad_addresses()
       self.check_good_addresses()
       self.check_donation_address()

    def create(self):
        print('Creating wallet')
        seed = 'velvet lymph giddy number token physics poetry unquoted nibs useful sabotage limits benches lifestyle eden nitrogen anvil fewest avoid batch vials washing fences goat unquoted'
        self.wallet = Wallet()
        try: self.wallet.close_wallet()
        except: pass
        res = self.wallet.restore_deterministic_wallet(seed = seed)
        self.address = res.address
        assert self.address != ''
        assert res.seed == seed

    def check_bad_addresses(self):
        print('Validating bad addresses')
        bad_addresses = ['', 'a', 'J6GX4gh7ix1ft9xVvUci45cTPFPjaRihnNQ7Y8kRvAxCNGVh6Fw8Hw83aJ8hFZyYtvB2CBaBfNKK3gSr4zJkqox1Jm2TiL', ' ', '@', 'J6GX']
        for address in bad_addresses:
            res = self.wallet.validate_address(address, any_net_type = False)
            assert not res.valid
            res = self.wallet.validate_address(address, any_net_type = True)
            assert not res.valid

    def check_good_addresses(self):
        print('Validating good addresses')
        address = 'J6GX4gh7ix1ft9xVvUci45cTPFPjaRihnNQ7Y8kRvAxCNGVh6Fw8Hw83aJ8hFZyYtvB2CBaBfNKK3gSr4zJkqox1Jm2TiLF'

        for any_net_type in [True, False]:
            res = self.wallet.validate_address(
                address,
                any_net_type = any_net_type
            )
            assert res.valid
            assert not res.integrated
            assert not res.subaddress
            assert res.nettype == 'mainnet'
            assert res.openalias_address == ''

    def check_donation_address(self):
        print('Validating Judecoin donation address')
        address = 'J6GX4gh7ix1ft9xVvUci45cTPFPjaRihnNQ7Y8kRvAxCNGVh6Fw8Hw83aJ8hFZyYtvB2CBaBfNKK3gSr4zJkqox1Jm2TiLF'
        res = self.wallet.validate_address(address)
        assert res.valid
        assert res.nettype == 'mainnet'
        assert res.openalias_address == ''

if __name__ == '__main__':
    AddressValidationTest().run_test()
