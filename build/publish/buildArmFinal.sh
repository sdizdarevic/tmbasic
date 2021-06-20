set -euxo pipefail
export PUBLISHDIR=/tmp/tmbasic-publish

cd $PUBLISHDIR/tmbasic/build
mkdir -p $PUBLISHDIR/tmbasic/obj/resources/runners
mkdir -p $PUBLISHDIR/tmbasic/bin

export DOCKER_FLAGS="--entrypoint /bin/bash"
export TTY_FLAG=" "

export CLEAN_CMD="source /etc/profile.d/tmbasic.sh && make clean && mkdir obj"
export BUILD_CMD="source /etc/profile.d/tmbasic.sh && make release"

./linux-arm64.sh -c "$CLEAN_CMD"
pushd $PUBLISHDIR/tmbasic/obj/resources/runners && tar xf $PUBLISHDIR/runners.tar && popd
./linux-arm64.sh -c "$BUILD_CMD"
pushd $PUBLISHDIR/tmbasic/bin && tar zcf $PUBLISHDIR/tmbasic-linux-arm64.tar.gz tmbasic LICENSE.txt && popd

./linux-arm32.sh -c "$CLEAN_CMD"
pushd $PUBLISHDIR/tmbasic/obj/resources/runners && tar xf $PUBLISHDIR/runners.tar && popd
./linux-arm32.sh -c "$BUILD_CMD"
pushd $PUBLISHDIR/tmbasic/bin && tar zcf $PUBLISHDIR/tmbasic-linux-arm32.tar.gz tmbasic LICENSE.txt && popd
