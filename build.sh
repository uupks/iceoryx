#!/usr/bin/env bash

TARGET_PLATFORM=Android
BUILD_TYPE=Release

SCRIPT_DIR=$(cd $(dirname ${BASH_SOURCE[0]}); pwd)
WORKSPACE=$SCRIPT_DIR

INSTALL_DIR=${WORKSPACE}/out/${TARGET_PLATFORM}_install
BUILD_DIR=${WORKSPACE}/out/${TARGET_PLATFORM}_build
LOG_DIR=${WORKSPACE}/out/${TARGET_PLATFORM}_log

# export NDK_HOME=/opt/ndk/android-ndk-r23c
export TOOLCHAIN_FILE=${SCRIPT_DIR}/cmake/android.toolchain.cmake

PACKAGE_UP_TO="--packages-up-to iceoryx_posh"

colcon --log-base ${LOG_DIR} build \
       --base-paths  ${WORKSPACE} \
       --build-base ${BUILD_DIR} \
       --install-base  ${INSTALL_DIR} \
       --merge-install \
       ${PACKAGE_UP_TO} \
       --cmake-force-configure \
       --cmake-args \
       --no-warn-unused-cli \
       -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
       -DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE} \
       -DCMAKE_FIND_ROOT_PATH=${INSTALL_DIR} \
       -DBUILD_TESTING=OFF \
       -DOpenCV_DIR=${ROS_HUMBLE}/sdk/native/jni \
       -DTARGET_PLATFORM=${TARGET_PLATFORM}
