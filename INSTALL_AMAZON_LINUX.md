# Installing LDMud on Amazon Linux 2023

This guide walks through preparing an Amazon Linux 2023 EC2 instance, building
LDMud from this repository, and running a test instance.

## 1) Prepare the system

Update the system and install required build tools:

```bash
sudo dnf -y update
sudo dnf -y groupinstall "Development Tools"
sudo dnf -y install \
  bison \
  flex \
  autoconf \
  automake \
  libtool \
  pkgconfig \
  git
```

Optional (but commonly useful) libraries:

```bash
sudo dnf -y install \
  openssl-devel \
  libxml2-devel \
  json-c-devel \
  sqlite-devel \
  mariadb-devel \
  postgresql-devel \
  libgcrypt-devel \
  pcre2-devel \
  gnutls-devel
```

> Notes:
> - `bison` is required; `yacc` is not sufficient.
> - If you do not need a library feature, you can skip its `-devel` package.

## 2) Get the source

If you already have this repository on your server, skip this step. Otherwise:

```bash
git clone <your-fork-url> ldmud
cd ldmud
```

## 3) Configure and build

From the repository root:

```bash
cd src
./autogen.sh
./configure --prefix=/opt/ldmud
make
```

If you want the driver and utilities installed into `/opt/ldmud`:

```bash
sudo make install
sudo make install-utils
```

## 4) Install a mudlib

LDMud requires a mudlib to run. A minimal option is included in the repo.
Copy it into your chosen lib directory (matches `--prefix` above):

```bash
sudo mkdir -p /opt/ldmud/lib
sudo cp -a ../mud/lp-245/* /opt/ldmud/lib/
```

The mudlib includes header files expected in `sys/` under the lib directory.
The `cp -a` step keeps the layout intact.

## 5) Run a test instance

From the installed bin directory:

```bash
/opt/ldmud/bin/ldmud 4242
```

If you see `LDMud ready for users`, the driver is accepting connections. You
can test locally with:

```bash
telnet localhost 4242
```

## 6) Firewall / security group considerations

If you want to connect remotely, open the port in the EC2 security group and
any host-based firewall. For example, to allow TCP port 4242 in the security
group, add an inbound rule for your IP address.

## Troubleshooting

- **Missing `configure`**: ensure you ran `./autogen.sh` in `src/` and that
  `autoconf`/`automake` are installed.
- **Missing optional features**: install the relevant `*-devel` package and
  re-run `./configure`.
- **Mudlib not found**: ensure the mudlib was copied into the `lib` directory
  that matches your `--prefix` setting, or set the mudlib directory on the
  `ldmud` command line.
