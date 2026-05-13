# The Current and Future Status of ZMQ in Judecoin

## ZMQ Pub/Sub

Client `ZMQ_SUB` sockets must subscribe to topics before they receive any data.

This allows filtering on the server side, reducing network traffic. Judecoin
allows filtering by:

1. Format
2. Context
3. Event

- **Format** refers to the wire format, such as JSON, used to send event
  information.
- **Context** allows for a reduction in fields for the event, so the daemon does
  not waste cycles serializing fields that will be ignored.
- **Event** refers to status changes occurring within the daemon, such as a new
  block being added to the main chain.

## Supported Topics

### Formats

- `json`

### Contexts

- `full` - The entire block or transaction is transmitted. The hash can be
  computed remotely.
- `minimal` - The bare minimum needed for a remote client to react to an event
  is sent.

### Events

- `chain_main` - Changes to the primary or main blockchain.
- `txpool_add` - New publicly visible transactions in the mempool. This includes
  previously unseen transactions in a block, but not the `miner_tx`. It does not
  re-publish after a reorg. It includes `do_not_relay` transactions.
- `miner_data` - Provides the necessary data to create a custom block template.
  This is available only in the `full` context.

## Subscription Topic Format

Subscription topics are formatted as:

```text
format-context-event
```

Prefix matching is supported by both Judecoin and ZMQ.

The `format`, `context`, and `event` values will never have hyphens or colons in
their names.

For example, subscribing to:

```text
json-minimal-chain_main
```

will send minimal information in JSON when changes to the main blockchain occur.

Subscribing to:

```text
json-minimal
```

will send minimal information in JSON for all available events supported by the
daemon.

## Event Ordering

The Judecoin daemon ensures that events prefixed by `chain` are sent in
chain order. The `prev_id` hash field will always refer to a previous block.

On rollbacks or reorgs, the event will reference an earlier block in the chain
instead of the last block.

The Judecoin daemon also ensures that `txpool_add` events are sent before
`chain_*` events. The `chain_*` messages will only serialize miner transactions,
since other transactions were previously published through `txpool_add`.

This prevents transactions from being serialized twice, even when the
transaction was first observed in a block.

## Dropped Messages

ZMQ Pub/Sub may drop messages if the network is congested. The ordering rules
above are used to help detect lost messages.

A missing gap in `height` or `prev_id` for `chain_*` events indicates a lost
publish message.

Missing `txpool_add` messages can only be detected at the next `chain_*`
message.

Since blockchain events can be dropped, clients will likely want to use a
timeout against `chain_main` events. The `GetLastBlockHeader` RPC is useful for
checking the current chain state.

Dropped messages should be rare in most conditions.

## Reorg Handling

The Judecoin daemon will send a `txpool_add` publication exactly once for each
transaction, even after a reorg or restart.

Clients should use `GetTransactionPool` after a reorg to retrieve all
transactions that have been put back into the transaction pool or invalidated
because of a double spend.
