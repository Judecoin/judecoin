# Judecoin hard fork release checklist

- [ ] Security audit
- [ ] Code audit

- [ ] Ledger integration
  - [ ] Ledger notified
  - [ ] Pull request made against the Judecoin codebase, if needed
  - [ ] Pull request merged into the Judecoin codebase, if needed
  - [ ] Ledger app integration coded
  - [ ] Ledger Judecoin app update available

- [ ] Trezor integration
  - [ ] Trezor notified
  - [ ] Pull request made against the Judecoin codebase, if needed
  - [ ] Pull request merged into the Judecoin codebase, if needed
  - [ ] Trezor firmware update coded
  - [ ] Trezor firmware update available

- [ ] Fork height set
  - [ ] Official website announcement
  - [ ] Official community announcement
  - [ ] Social media announcement, if applicable

- [ ] Notify wallets
  - [ ] Official Judecoin wallet users
  - [ ] Supported third-party wallet providers, if applicable
  - [ ] Hardware wallet providers, if applicable
  - [ ] Ecosystem wallet partners, if applicable

- [ ] Notify exchanges and service providers
  - [ ] Supported exchanges, if applicable
  - [ ] Supported swap or liquidity providers, if applicable
  - [ ] Supported payment processors, if applicable
  - [ ] Other ecosystem service providers, if applicable

- [ ] Notify mining pools, if still relevant
  - [ ] Supported mining pools, if applicable
  - [ ] Mining pool operators, if applicable

- [ ] Release branch created
  - [ ] Update `src/version.cpp.in` with the new version and new release name, if necessary
  - [ ] Update `README.md` with the new fork table entry, or at least update the recommended Judecoin version
  - [ ] Update `src/checkpoints/checkpoints.cpp` with a recent hardcoded checkpoint
  - [ ] Update `src/blocks/checkpoints.dat` with:

```bash
./jude-blockchain-export --output-file checkpoints.dat --block-stop <recent block height> --blocksdat
```

  - [ ] Update `expected_block_hashes_hash` in `src/cryptonote_core/blockchain.cpp` with the SHA-256 hash of `checkpoints.dat`

- [ ] Testnet forked
- [ ] Testnet testing and verification
  - [ ] Ledger testing
  - [ ] Trezor testing
  - [ ] Release-specific testing
  - [ ] RPC testing
  - [ ] RPC documentation reviewed and updated, if needed

- [ ] Stagenet forked
- [ ] Stagenet testing and verification
  - [ ] Ledger testing
  - [ ] Trezor testing
  - [ ] Release-specific testing

- [ ] CLI reproducible builds validated

- [ ] CLI released
  - [ ] Official downloads page updated
  - [ ] `hashes.txt` updated on the website
  - [ ] `downloads.yml` updated on the website
  - [ ] Auto-update DNS records updated, if applicable
  - [ ] Redirects updated on the downloads server, if applicable
  - [ ] Seed nodes updated, if applicable

- [ ] GUI released
  - [ ] Official downloads page updated
  - [ ] `hashes.txt` updated on the website
  - [ ] `hashes.txt.sig` updated on the website
  - [ ] `downloads.yml` updated on the website
  - [ ] Auto-update DNS records updated, if applicable
  - [ ] Redirects updated on the downloads server, if applicable

- [ ] Release announcements
  - [ ] Official announcement channel notice
  - [ ] Official website announcement
  - [ ] Official community announcement
  - [ ] Social media announcement, if applicable
