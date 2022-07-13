# This script needs to be "source"-d since it sets LD_LIBRARY_PATH and PATH

# Since we don't have root access on netlify, we could only install Python in current user's env
# This script installs Python binary from PPA and Pipenv, with APT prefix
PYTHON_VERSION="3.10"

APT_PACKAGES=(
  "python$PYTHON_VERSION"
  "python$PYTHON_VERSION-distutils"
)

APT_PREFIX="$HOME/.apt_prefix"
APT_PREFIX_MAKE_DIRS=(
  /etc/apt
  /usr/lib
  /var/lib/dpkg
  /var/lib/apt/lists/partial
  /var/cache/apt/archives/partial
  /var/log/apt
)
APT_PREFIX_COPY_DIRS=(
  /etc/apt
  /var/lib/dpkg
)
APT_PREFIX_LD_LIBRARY_PATHS=(
  /lib
  /lib/x86_64-linux-gnu
  /usr/lib
  /usr/lib/x86_64-linux-gnu
)
APT_PREFIX_PATHS=(
  /usr/local/bin
  /usr/bin
  /bin
)

for DIR in "${APT_PREFIX_MAKE_DIRS[@]}"; do mkdir -p "$APT_PREFIX$DIR"; done
for DIR in "${APT_PREFIX_COPY_DIRS[@]}"; do cp -r "$DIR/." "$APT_PREFIX$DIR/" || true; done

# Download packages from PPA deadsnakes/ppa
UBUNTU_CODENAME="$(source /etc/os-release && echo "$UBUNTU_CODENAME")"
echo "deb [trusted=yes] https://ppa.launchpadcontent.net/deadsnakes/ppa/ubuntu $UBUNTU_CODENAME main" > "$APT_PREFIX"/etc/apt/sources.list.d/python.list
apt-get -o "Dir=$APT_PREFIX" -o Debug::NoLocking=1 update
apt-get -o "Dir=$APT_PREFIX" -o Debug::NoLocking=1 install -y --download-only "${APT_PACKAGES[@]}"

# Install (extract) packages
for PACKAGE in "$APT_PREFIX"/var/cache/apt/archives/*.deb; do dpkg -x "$PACKAGE" "$APT_PREFIX"; done

# Append LD_LIBRARY_PATH and PATH (after current)
for LIBPATH in "${APT_PREFIX_LD_LIBRARY_PATHS[@]}"; do export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$APT_PREFIX$LIBPATH"; done
for BINPATH in "${APT_PREFIX_PATHS[@]}"; do export PATH="$PATH:$APT_PREFIX$BINPATH"; done

# Install Pipenv
curl https://raw.githubusercontent.com/pypa/pipenv/master/get-pipenv.py | "python$PYTHON_VERSION"
