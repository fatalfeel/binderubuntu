/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Implementation of the user-space ashmem API for devices, which have our
 * ashmem-enabled kernel. See ashmem-sim.c for the "fake" tmp-based version,
 * used by the simulator.
 */

/*
Refer
https://android.googlesource.com/platform/system/core/+/refs/tags/android-10.0.0_r1/libcutils/ashmem-dev.cpp
https://android.googlesource.com/platform/system/core/+/refs/tags/android-10.0.0_r1/base/include/android-base/unique_fd.h
*/

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <linux/fcntl.h>
#include <linux/memfd.h>
#include <linux/version.h>

typedef unsigned int __u32;

#include <driver/ashmem/uapi/ashmem.h>
#include <cutils/ashmem.h>
#include "strlcpy.h"

#define ASHMEM_DEVICE	"/dev/ashmem"

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,18,1)
static int memfd_create_region(const char* name, size_t size)
{
    //android::base::unique_fd fd(syscall(__NR_memfd_create, name, MFD_ALLOW_SEALING));
    int fd = syscall(__NR_memfd_create, name, MFD_ALLOW_SEALING);

    if (fd == -1) {
        //ALOGE("memfd_create(%s, %zd) failed: %s\n", name, size, strerror(errno));
        return -1;
    }

    if (ftruncate(fd, size) == -1) {
        //ALOGE("ftruncate(%s, %zd) failed for memfd creation: %s\n", name, size, strerror(errno));
        return -1;
    }

    //if (debug_log) {
    //    ALOGE("memfd_create(%s, %zd) success. fd=%d\n", name, size, fd.get());
    //}

    //return fd.release();
    return fd;
}

/*
 * ashmem_create_region - creates a new ashmem region and returns the file
 * descriptor, or <0 on error
 *
 * `name' is an optional label to give the region (visible in /proc/pid/maps)
 * `size' is the size of the region, in page-aligned bytes
 */
int ashmem_create_region(const char *name, size_t size)
{
	int fd;

    //if (has_memfd_support()) {
        return memfd_create_region(name ? name : "none", size);
    //}

	return fd;
}

static int memfd_set_prot_region(int fd, int prot)
{
    /* Only proceed if an fd needs to be write-protected */
    if (prot & PROT_WRITE) {
        return 0;
    }

    if (fcntl(fd, F_ADD_SEALS, F_SEAL_FUTURE_WRITE) == -1) {
        //ALOGE("memfd_set_prot_region(%d, %d): F_SEAL_FUTURE_WRITE seal failed: %s\n", fd, prot, strerror(errno));
        return -1;
    }

    return 0;
}

int ashmem_set_prot_region(int fd, int prot)
{
    //if (has_memfd_support() && !memfd_is_ashmem(fd)) {
        return memfd_set_prot_region(fd, prot);
    //}
}

int ashmem_pin_region(int fd, size_t offset, size_t len)
{
    //if (has_memfd_support() && !memfd_is_ashmem(fd)) {
        return 0;
    //}
}

int ashmem_unpin_region(int fd, size_t offset, size_t len)
{
    //if (has_memfd_support() && !memfd_is_ashmem(fd)) {
        return 0;
    //}
}

int ashmem_get_size_region(int fd)
{
    //if (has_memfd_support() && !memfd_is_ashmem(fd)) {
        struct stat sb;

        if (fstat(fd, &sb) == -1) {
            //ALOGE("ashmem_get_size_region(%d): fstat failed: %s\n", fd, strerror(errno));
            return -1;
        }

        //if (debug_log) {
        //    ALOGD("ashmem_get_size_region(%d): %d\n", fd, static_cast<int>(sb.st_size));
        //}

        return sb.st_size;
    //}
}
#else
/*
 * ashmem_create_region - creates a new ashmem region and returns the file
 * descriptor, or <0 on error
 *
 * `name' is an optional label to give the region (visible in /proc/pid/maps)
 * `size' is the size of the region, in page-aligned bytes
 */
int ashmem_create_region(const char *name, size_t size)
{
    int fd, ret;

    fd = open(ASHMEM_DEVICE, O_RDWR);
    if (fd < 0)
        return fd;

    if (name) {
        char buf[ASHMEM_NAME_LEN] = {0};

        strlcpy(buf, name, sizeof(buf));
        ret = ioctl(fd, ASHMEM_SET_NAME, buf);
        if (ret < 0)
            goto error;
    }

    ret = ioctl(fd, ASHMEM_SET_SIZE, size);
    if (ret < 0)
        goto error;

    return fd;

error:
    close(fd);
    return ret;
}

int ashmem_set_prot_region(int fd, int prot)
{
    return ioctl(fd, ASHMEM_SET_PROT_MASK, prot);
}

int ashmem_pin_region(int fd, size_t offset, size_t len)
{
    struct ashmem_pin pin = { offset, len };
    return ioctl(fd, ASHMEM_PIN, &pin);
}

int ashmem_unpin_region(int fd, size_t offset, size_t len)
{
    struct ashmem_pin pin = { offset, len };
    return ioctl(fd, ASHMEM_UNPIN, &pin);
}

int ashmem_get_size_region(int fd)
{
    return ioctl(fd, ASHMEM_GET_SIZE, NULL);
}
#endif
