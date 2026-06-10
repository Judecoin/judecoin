# Multistage docker build, requires docker 17.05

# builder stage
FROM ubuntu:20.04 AS builder

RUN set -ex && \
    apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get --no-install-recommends --yes install \
        build-essential \
        ca-certificates \
        cmake \
        curl \
        git \
        pkg-config

WORKDIR /src
COPY . .

ARG NPROC
RUN set -ex && \
    git submodule init && git submodule update && \
    rm -rf build && \
    if [ -z "$NPROC" ] ; \
    then make -j$(nproc) depends target=x86_64-linux-gnu ; \
    else make -j$NPROC depends target=x86_64-linux-gnu ; \
    fi

# runtime stage
FROM ubuntu:20.04

RUN set -ex && \
    apt-get update && \
    apt-get --no-install-recommends --yes install ca-certificates && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY --from=builder /src/build/x86_64-linux-gnu/release/bin /usr/local/bin/

# Create judecoin user and runtime directories
RUN adduser --system --group --disabled-password --home /home/judecoin judecoin && \
    mkdir -p /wallet /home/judecoin/.bitjudecoin /root/.bitjudecoin && \
    chown -R judecoin:judecoin /home/judecoin/.bitjudecoin && \
    chown -R judecoin:judecoin /wallet

# Default data directory for the non-root container user
VOLUME /home/judecoin/.bitjudecoin

# Generate your wallet via accessing the container and run:
# cd /wallet
# judecoin-wallet-cli
VOLUME /wallet

EXPOSE 16060
EXPOSE 16063

ENV HOME=/home/judecoin

# Switch to non-root user by default
USER judecoin

ENTRYPOINT ["judecoind"]

CMD ["--data-dir=/home/judecoin/.bitjudecoin", "--p2p-bind-ip=0.0.0.0", "--p2p-bind-port=16060", "--rpc-bind-ip=0.0.0.0", "--rpc-bind-port=16063", "--non-interactive", "--confirm-external-bind"]