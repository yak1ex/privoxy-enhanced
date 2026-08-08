#!/bin/sh

extract_var() {
  target=$1
  strip=$2
  if [ -n "$strip" ]; then
    opt='-e s,\",,g'
  fi
  value=$(grep -E "\b${target}\b" config.h | sed -e s,.*${target}\s*,, $opt)
  echo $value
}

# clean

git restore .
rm config.txt default.action

# build

autoheader
autoconf
env CC=i686-w64-mingw32-gcc ./configure --enable-mingw32 --disable-pthread --enable-static-linking --enable-extended-statistics --enable-pcre-host-patterns --enable-strptime-sanity-checks --with-mbedtls --with-brotli --enable-compression --with-zstd
make inifiles
make

# extract configuration

version=$(extract_var DOC_VERSION strip)
patchlevel=$(extract_var PATCHLEVEL)
status=$(extract_var CODE_STATUS strip)
pkg_version="privoxy-$version-${status}_y$patchlevel"
echo $pkg_version

# install to temporary location

destdir=desttemp-$pkg_version
rm -rf $destdir
DESTDIR=$destdir make install

rm -rf $pkg_version
mkdir -p $pkg_version/doc
for i in developer-manual faq user-manual p_doc.css; do
  cp -R $destdir/usr/local/share/doc/privoxy/$i $pkg_version/doc/$i
done
for i in AUTHORS LICENSE README; do
  cp -R $destdir/usr/local/share/doc/privoxy/$i $pkg_version/$i.txt
done
cp -R $destdir/usr/local/etc/privoxy/* $pkg_version/
rm $pkg_version/{config,trust}
sed -e 's,^logfile logfile,logfile privoxy.log,;s,#trustfile trust,#trustfile trust.txt,' config.txt > $pkg_version/config.txt
cp trust.txt $pkg_version/
find $pkg_version -type f \! -iname '*.jpg' \! -iname 'default.*' | xargs u2d
cp privoxy.exe $pkg_version/
strip $pkg_version/privoxy.exe
