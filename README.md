binder on Ubuntu
================
Test pass on Ubuntu 16.04/18.04 at 2020-12-25

(1) Build in command line:

    make
    ./project.sh insmod

(2) Compile and debug projects in Eclipse (option)

    a. ~\binderubuntu\driver\ashmem
    b. ~\binderubuntu\driver\binder
    c. ~\binderubuntu\libs
    d. ~\binderubuntu\servicemanager
    e. ~\binderubuntu\test_client
    f. ~\binderubuntu\test_server
    ./project.sh insmod

(3) Install Anbox can substitute driver/ashmem and driver/binder (option)

https://computingforgeeks.com/how-to-run-android-applications-on-linux-with-anbox

(4) Run

    ~/binderubuntu/servicemanager/servicemanager
    ~/binderubuntu/test_server/test_server
    ~/binderubuntu/test_client/test_client

(5) Note
    
    (b) When compile error: passing argument 1 of ‘security_binder_transaction’
           because /usr/src/linux-headers-5.4.0-132-generic/include/linux/security.h
           int security_binder_transfer_binder(const struct cred *from, const struct cred *to);
           modify binder.c
           #if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 0, 0) -> #if 0
    
    (a) After insmod show follows
          binder_linux.ko: Required key not availabel
          ashmem_linux.ko: Required key not availabel
          go to BIOS setting and disable [Secure Boot] of UEFI
          
(6) build libs and servicemanager run in x86_64 or arm64 embedded system

    If have your own embedded system driver, you can build & run libs, servicemanager, test_client, test_server. Modify defconfig as follows.
    CONFIG_ANDROID=y
    CONFIG_ANDROID_BINDER_IPC=y
    CONFIG_ANDROID_BINDER_IPC_32BIT=n
    CONFIG_ANDROID_BINDERFS=n
    CONFIG_ANDROID_BINDER_DEVICES="binder,hwbinder,vndbinder"
    CONFIG_ANDROID_BINDER_IPC_SELFTEST=n
    CONFIG_ASHMEM=y

Refer to
1. https://github.com/hungys/binder-for-linux
2. https://github.com/anbox/anbox-modules
