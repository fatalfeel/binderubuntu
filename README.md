binder on Ubuntu
================
Test on Ubuntu 16.04 pass at 2020-12-25

(1) Build in command line:

./project.sh build

./project.sh insmod

#

(2) Compile and debug projects in Eclipse (option)

a. ~\binderubuntu\driver\ashmem

b. ~\binderubuntu\driver\binder

c. ~\binderubuntu\libs

d. ~\binderubuntu\servicemanager

e. ~\binderubuntu\test_client

f. ~\binderubuntu\test_server

./project.sh insmod

#

(3) Install Anbox can substitute driver/ashmem and driver/binder (option)

https://computingforgeeks.com/how-to-run-android-applications-on-linux-with-anbox

#

(4) Run

~/binderubuntu/servicemanager/servicemanager

~/binderubuntu/test_server/test_server

~/binderubuntu/test_client/test_client

#

Refer to
1. https://github.com/hungys/binder-for-linux
2. https://github.com/anbox/anbox-modules
