# Judecoin

Copyright (c) 2014-2026 The Judecoin Project.  
Portions Copyright (c) The Cryptonote developers.

## Table of Contents

- [Development Resources](#development-resources)
- [Documentation](#documentation)
- [Vulnerability Response](#vulnerability-response)
- [Research](#research)
- [Announcements](#announcements)
- [Translations](#translations)
- [Coverage](#coverage)
- [Introduction](#introduction)
- [About This Project](#about-this-project)
- [Supporting the Project](#supporting-the-project)
- [License](#license)
- [Contributing](#contributing)
- [Scheduled Software Upgrades](#scheduled-software-upgrades)
- [Release Staging Schedule and Protocol](#release-staging-schedule-and-protocol)
- [Compiling Judecoin from Source](#compiling-judecoin-from-source)
- [Running Judecoind](#running-judecoind)
- [Wallet Tools](#wallet-tools)
- [Service Node Operation](#service-node-operation)
- [Internationalization](#internationalization)
- [Using Tor](#using-tor)
- [Pruning](#pruning)
- [Debugging](#debugging)
- [Known Issues](#known-issues)

## Development Resources

- Web: [judecoin.io](https://www.judecoin.io/)
- Blog / Updates: [judecoin.io/blog](https://www.judecoin.io/blog)
- GitHub: [github.com/Judecoin/judecoin](https://github.com/Judecoin/judecoin)
- Block Explorer: [judeblock.org](https://www.judeblock.org/)

## Documentation

- [CLI Wallet Documentation](https://github.com/Judecoin/wallet/tree/main/CLI-Wallet-Doc)
- [PoS Evolution and Service Node Documentation](https://github.com/Judecoin/pos-evolution)

## Vulnerability Response

Responsible disclosure is encouraged.

If you discover a security issue, please report it through the official Judecoin communication channels or the official repository issue process when appropriate.

Please do not publicly disclose sensitive vulnerabilities before they have been reviewed.

## Research

Judecoin research and development may include work related to privacy, cryptography, protocols, fungibility, network behavior, wallet tools, and service node operation.

For roadmap-related research and development directions, please refer to the [Judecoin Roadmap](https://www.judecoin.io/roadmap).

Researchers, developers, and contributors are welcome to review the codebase, discuss technical improvements, and submit relevant contributions.

## Announcements

Important announcements, software updates, release notes, and upgrade information should be checked through official Judecoin resources.

For updates, please refer to the [Judecoin Blog / Updates](https://www.judecoin.io/blog).

Users, wallet operators, node operators, and service providers should keep their software updated according to official release guidance.

## Translations

Judecoin wallet tools may support multiple languages depending on the release version.

Translation support and localization behavior may vary by wallet type and software release.

## Coverage

Coverage and testing status may vary by repository configuration, release branch, and development stage.

Please refer to the current repository status, release notes, and available CI/test results where applicable.

| Type | Status |
|------|--------|
| License | [![License](https://img.shields.io/badge/license-BSD3-blue.svg)](https://opensource.org/licenses/BSD-3-Clause) |

## Introduction

Judecoin is a private, secure, untraceable, decentralized digital currency.

You are your bank. You control your funds, and transactions are designed to preserve privacy unless you choose to disclose relevant information.

**Privacy:** Judecoin uses privacy-oriented cryptographic mechanisms to help protect transaction details on the blockchain.

**Security:** Using the power of a distributed peer-to-peer consensus network, transactions are cryptographically secured. Wallets should be protected with strong passwords, and wallet seed phrases should be stored safely offline.

**Untraceability:** Judecoin uses privacy-focused cryptographic design to reduce the ability to link transactions directly to individual users.

**Decentralization:** Judecoin depends on a decentralized peer-to-peer network where participants can run software, validate blockchain data, and support network operation.

## About This Project

This repository contains the core implementation of Judecoin.

It includes source code, daemon software, wallet tools, build files, and technical documentation.

As with many development projects, this repository may contain ongoing updates. Users running production systems should follow official release guidance and use stable release versions when available.

Contributions to Judecoin’s codebase and documentation are welcome when they are clear, accurate, and relevant to the project.

## Supporting the Project

Judecoin is a community-supported project.

If you would like to support the project, you may do so through the official donation address.

The Judecoin donation address is:

`J6GX4gh7ix1ft9xVvUci45cTPFPjaRihnNQ7Y8kRvAxCNGVh6Fw8Hw83aJ8hFZyYtvB2CBaBfNKK3gSr4zJkqox1Jm2TiLF`

## License

See [LICENSE](LICENSE).

## Contributing

If you want to help out, see [CONTRIBUTING](docs/CONTRIBUTING.md) for contribution guidelines.

You may contribute by improving documentation, reporting issues, testing releases, submitting code, or helping improve user guides.

Before submitting changes, please make sure your contribution is clear, accurate, and relevant to the Judecoin project.

## Scheduled Software Upgrades

Judecoin may use scheduled software upgrades to introduce protocol changes, network improvements, and new features.

Users, node operators, wallet users, and service providers should keep their software updated according to official release guidance.

Please check the official repository, release notes, and documentation before each upgrade.

## Release Staging Schedule and Protocol

Release branches, tags, and update procedures may vary depending on the development stage and release cycle.

Users running production systems should use stable release versions when available.

Developers and contributors should follow the repository’s contribution and release guidance before submitting changes.

## Compiling Judecoin from Source

Judecoin can be compiled from source on supported operating systems.

Before compiling, please make sure all required dependencies are installed for your operating system.

Build requirements may vary depending on release version and platform.

Users running production systems should use stable release versions when available.

### Dependencies

Dependencies may vary depending on operating system, release version, and build target.

General build dependencies may include:

- C++ compiler
- CMake
- pkg-config
- Boost
- OpenSSL
- ZeroMQ
- libsodium
- libunbound
- readline
- protobuf
- optional documentation and test tools

Please refer to the latest release notes and build instructions before compiling.

### Cloning the Repository

Clone recursively to pull in needed submodules:

```bash
git clone --recursive https://github.com/Judecoin/judecoin.git
cd judecoin
```

If you already have a repository cloned, initialize and update submodules:

```bash
git submodule init
git submodule update
```

### Build Instructions

Build commands may vary depending on operating system and release version.

General example:

```bash
make
```

For platform-specific build options, please follow the latest official build documentation and release guidance.

## Running Judecoind

After building or downloading the official release package, the daemon can usually be started with:

```bash
./judecoind
```

To list available options, run:

```bash
./judecoind --help
```

To run the daemon in the background, use the appropriate daemon option for your operating system and release version.

For service node operation, please refer to the relevant service node documentation.

## Wallet Tools

Judecoin provides wallet tools for users who need to create, recover, manage, or operate wallets.

For CLI wallet setup and recovery instructions, please refer to:

- [CLI Wallet Documentation](https://github.com/Judecoin/wallet/tree/main/CLI-Wallet-Doc)

## Service Node Operation

Service node operation may require additional setup, registration, maintenance, monitoring, and version upgrade procedures.

For service node documentation, please refer to:

- [PoS Evolution and Service Node Documentation](https://github.com/Judecoin/pos-evolution)

## Internationalization

Judecoin wallet tools may support multiple languages depending on the release version.

Language availability and translation behavior may vary by wallet type and software release.

## Using Tor

Judecoin may be used with privacy network tools depending on configuration and release support.

Users should review the relevant technical documentation before using Tor or other anonymity networks with Judecoin.

## Pruning

Blockchain pruning may reduce local storage requirements while keeping the node functional for normal use.

Pruning behavior and disk requirements may vary by release version.

Before enabling pruning, users should understand the difference between full blockchain storage and pruned blockchain storage.

## Debugging

If a build, daemon, or wallet process fails, users should first confirm they are using the latest official release or the correct source branch.

Useful debugging information may include:

- Operating system
- Judecoin version
- Error messages
- Daemon logs
- Wallet logs
- Recent configuration changes
- Steps to reproduce the issue

## Security and Debugging Notes

Never include the following information in public issue reports or discussions:

- Wallet seed phrases
- Wallet passwords
- Private spend keys
- Private view keys
- Wallet files
- Sensitive server credentials
- Private configuration files

If logs are shared for debugging, review and remove sensitive information before posting.

## Known Issues

Known issues may vary by release version.

Please check official release notes, open issues, and current documentation for the latest status.
