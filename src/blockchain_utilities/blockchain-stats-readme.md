# Judecoin Blockchain Stats

The Judecoin Blockchain Stats utility exports daily statistics for the Judecoin
blockchain from genesis through the current state.

## Usage

See the utility's help option for additional details:

```bash
jude-blockchain-stats --help
```

From the command line, run:

```bash
jude-blockchain-stats
```

This loads the existing blockchain and prints the results to the terminal.

By default, the printed data includes:

- Blocks per day
- Total blocks
- Transactions per day
- Total transactions
- Bytes per day
- Total bytes

The output format is tab-delimited CSV printed to the console. Redirecting or
piping the command output allows the data to be saved to a CSV file or passed to
another script.

Examples:

```bash
jude-blockchain-stats > stats-$(date +'%Y-%m-%d').csv

jude-blockchain-stats | save-to-database.sh
```

## Options

`--data-dir arg`

Specifies the location of blockchain storage.

`--testnet`

Runs on testnet.

`--stagenet`

Runs on stagenet.

`--log-level arg`

Sets the log level from `0` to `4`, or by category.

`--block-start arg (=0)`

Starts at the specified block number.

`--block-stop arg (=0)`

Stops at the specified block number.

`--with-inputs`

Includes input statistics.

`--with-outputs`

Includes output statistics.

`--with-ringsize`

Includes ring size statistics.

`--with-hours`

Includes transactions per hour.

`--with-emission`

Includes coin emission.

`--with-fees`

Includes transaction fees.

`--with-diff`

Includes difficulty statistics.
