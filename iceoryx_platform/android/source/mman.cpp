// Copyright (c) 2021 by Apex.AI Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#include "iceoryx_platform/mman.hpp"
#include "iceoryx_platform/platform_settings.hpp"
#include <linux/ashmem.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define ASHMEM_DEVICE   "/dev/ashmem"

// NOLINTNEXTLINE(readability-identifier-naming)
int iox_shm_open(const char* name, int oflag, mode_t mode)
{
    int fd, ret;
    fd = open(ASHMEM_DEVICE, O_RDWR);
    if (fd < 0) {
        return fd;
    }

    if (name) {
        char buf[ASHMEM_NAME_LEN] = {0};

        strlcpy(buf, name, sizeof(buf));
        ret = ioctl(fd, ASHMEM_SET_NAME, buf);
        if (ret < 0) {
            goto error;
        }
    }

    return fd;

error:
    close(fd);
    return ret;
}

// NOLINTNEXTLINE(readability-identifier-naming)
int iox_shm_unlink(const char* name)
{
    return 0;
}

int iox_shm_close(int fd)
{
    return close(fd);
}
