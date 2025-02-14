#!/bin/bash
# checks for the current version of dependencies
set -euo pipefail

function checkGnu {
    local prefix=$1
    local varname=$2
    local url=$3
    local version=$(curl --silent $url \
        | grep "\.tar\.gz" \
        | grep -o "$prefix[0-9\.]\+.tar.gz\".\+" \
        | sed 's/"[^"]\+align=\"right\">/,/g; s/ /,/g' \
        | awk -F, '{ print $2 "," $3 "," $1 }' \
        | sort \
        | awk -F, '{ print $3 }' \
        | tail -n 1 \
        | grep -o '[0-9][0-9\.]\+[0-9]')
    echo "${varname}_VERSION=$version"
}

function checkJfrog {
    local varname=$1
    local url=$2
    local version=$(curl --silent $url \
        | grep '<a ' \
        | grep -v '\.\./' \
        | sort \
        | tail -n 1 \
        | awk -F\" '{ print $2 }' \
        | sed 's:/::')
    echo "${varname}_VERSION=$version"
}

function checkGitHubRelease {
    local varname=$1
    local url=$2
    local version=$(curl --silent $url \
        | grep '<title>' \
        | grep -v '\-rc' \
        | grep -v 'cldr' \
        | head -n 2 \
        | tail -n 1 \
        | grep -o '[0-9.]\+')
    echo "${varname}_VERSION=$version"
}

function checkGitHubCommit {
    local varname=$1
    local url=$2
    local version=$(curl --silent $url \
        | grep '/commit/' \
        | head -n 1 \
        | grep -o 'commit/[a-z0-9]\+' \
        | sed 's:commit/::')
    echo "${varname}_VERSION=$version"
}

function checkMpdecimal {
    local varname=$1
    local url=$2
    local version=$(curl --silent $url \
        | grep \.tar\.gz \
        | head -n 1 \
        | grep -o 'mpdecimal-[0-9\.]\+\.tar\.gz' \
        | sed 's/mpdecimal-//; s/\.tar\.gz//' \
        | head -n 1)
    echo "${varname}_VERSION=$version"
}

function checkNcurses {
    local varname=$1
    local url=$2
    local version=$(curl --silent $url \
        | grep '<title>' \
        | grep -o '[0-9.]\+')
    echo "${varname}_VERSION=$version"
}

function checkZlib {
    local varname=$1
    local url=$2
    local version=$(curl --silent $url \
        | grep -o 'zlib [0-9\.]\+' \
        | sed 's/zlib //')
    echo "${varname}_VERSION=$version"
}

function checkMingw {
    local varname=$1
    local url=$2
    local version=$(curl --silent $url \
        | grep '<link>' \
        | grep '\.tar\.bz2/' \
        | head -n 1 \
        | grep -o '[0-9\.]\+\.tar' \
        | sed 's/\.tar//')
    echo "${varname}_VERSION=$version"
}

function checkGcc {
    local varname=$1
    local url=$2
    local version=$(curl --silent $url \
        | grep gcc- \
        | grep '/">' \
        | tail -n 1 \
        | grep -o 'gcc-[0-9\.]\+' \
        | head -n 1 \
        | sed 's/gcc-//')
    echo "${varname}_VERSION=$version"
}

echo
echo '# depsDownload.sh'
checkGnu "binutils-" "BINUTILS" "https://ftp.gnu.org/gnu/binutils/"
checkJfrog "BOOST" "https://boostorg.jfrog.io/artifactory/main/release/"
checkGitHubRelease "CMAKE" "https://github.com/Kitware/CMake/releases.atom"
checkGitHubRelease "FMT" "https://github.com/fmtlib/fmt/releases.atom"
checkGitHubRelease "GOOGLETEST" "https://github.com/google/googletest/releases.atom"
checkGitHubRelease "ICU" "https://github.com/unicode-org/icu/releases.atom"
checkGitHubCommit "IMMER" "https://github.com/arximboldi/immer/commits.atom"
checkGitHubRelease "LIBCLIPBOARD" "https://github.com/jtanx/libclipboard/releases.atom"
checkGnu "libXau-" "LIBXAU" "https://xorg.freedesktop.org/archive/individual/lib/"
checkGnu "libxcb-" "LIBXCB" "https://xorg.freedesktop.org/archive/individual/lib/"
checkGitHubRelease "LIBZIP" "https://github.com/nih-at/libzip/releases.atom"
checkGitHubCommit "MICROTAR" "https://github.com/rxi/microtar/commits.atom"
checkMpdecimal "MPDECIMAL" "https://www.bytereef.org/mpdecimal/download.html"
checkGitHubRelease "NAMEOF" "https://github.com/Neargye/nameof/releases.atom"
checkNcurses "NCURSES" "https://invisible-mirror.net/ncurses/announce.html"
checkGitHubCommit "TURBO" "https://github.com/magiblot/turbo/commits.atom"
checkGitHubCommit "TVISION" "https://github.com/magiblot/tvision/commits.atom"
checkGitHubCommit "XCBPROTO" "https://gitlab.freedesktop.org/xorg/proto/xcbproto/-/commits/master?format=atom"
checkGnu "xorgproto-" "XORGPROTO" "https://xorg.freedesktop.org/archive/individual/proto/"
checkZlib "ZLIB" "https://zlib.net/"

echo
echo '# mingw.sh'
checkGnu "pkg-config-" "PKG_CONFIG" "https://pkg-config.freedesktop.org/releases/"
checkGnu "binutils-" "BINUTILS" "https://ftp.gnu.org/gnu/binutils/"
checkMingw "MINGW" "https://sourceforge.net/projects/mingw-w64/rss?path=/mingw-w64/mingw-w64-release"
checkGcc "GCC" "https://ftp.gnu.org/gnu/gcc/"
