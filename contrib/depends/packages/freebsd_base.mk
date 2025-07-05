package=freebsd_base
$(package)_version=11.3
$(package)_download_path=https://archive.freebsd.org/old-releases/amd64/$($(package)_version)-RELEASE/
$(package)_download_file=base.txz
$(package)_file_name=freebsd-base-$($(package)_version).txz
$(package)_sha256_hash=4599023ac136325b86f2fddeec64c1624daa83657e40b00b2ef944c81463a4ff

define $(package)_extract_cmds
  echo $($(package)_sha256_hash) $($(1)_source_dir)/$($(package)_file_name) | sha256sum -c &&\
  tar xf $($(1)_source_dir)/$($(package)_file_name) ./lib/ ./usr/lib/ ./usr/include/
endef

# Prevent clang from including OpenSSL headers from the system base. We
# statically link our own version of OpenSSL.

define $(package)_stage_cmds
  mkdir $($(package)_staging_dir)/$(host_prefix)/native &&\
  rm -rf usr/include/openssl &&\
  mv lib usr $($(package)_staging_dir)/$(host_prefix)/native
endef
