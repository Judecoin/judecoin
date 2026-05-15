# Judecoin Blockchain Utilities

Copyright (c) 2014-2026, The Judecoin Project

## Introduction

The blockchain utilities allow users to import and export the blockchain.

## Usage

See each utility's `--help` option for additional details.

### Export an existing blockchain database

```bash
jude-blockchain-export
```

This loads the existing blockchain and exports it to:

```text
$JUDE_DATA_DIR/export/blockchain.raw
```

### Import the exported file

```bash
jude-blockchain-import
```

This imports blocks from:

```text
$JUDE_DATA_DIR/export/blockchain.raw
```

The file should be exported using the `jude-blockchain-export` tool described above.

Defaults:

```text
--batch on
--batch-size 20000
--verify on
```

Batch size refers to the number of blocks and can be adjusted for performance
based on available RAM.

Verification should only be turned off when importing from a trusted blockchain
source.

If you encounter an error such as:

```text
resizing not supported in batch mode
```

you can re-run the `jude-blockchain-import` command. It will restart from where
it left off.

```bash
# Use default settings to import blockchain.raw into the database
jude-blockchain-import

# Fast import with a large batch size, database mode "fastest", and verification off
jude-blockchain-import --batch-size 20000 --database lmdb#fastest --verify off
```

### Import and export options

`--input-file`

Specifies the input file path for importing.

Default:

```text
<data-dir>/export/blockchain.raw
```

`--output-file`

Specifies the output file path for exporting.

Default:

```text
<data-dir>/export/blockchain.raw
```

`--block-stop`

Stops at the specified block number.

`--database <database type>`

Specifies the database type.

`--database <database type>#<flag(s)>`

Specifies the database type with one or more database flags.

Supported database types:

```text
lmdb
memory
```

Flags:

The flag after `#` is interpreted as a composite mode or flag if there is only
one flag and no comma-separated arguments are provided.

The composite mode represents multiple database flags and supports different
database types:

```text
safe
fast
fastest
```

Database-specific flags can be set instead.

LMDB flags. More than one may be specified:

```text
nosync
nometasync
writemap
mapasync
nordahead
```

## Examples

```bash
jude-blockchain-import --database lmdb#fastest

jude-blockchain-import --database lmdb#nosync

jude-blockchain-import --database lmdb#nosync,nometasync
```
