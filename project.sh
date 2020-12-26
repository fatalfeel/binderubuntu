#!/bin/sh

cmd="${1}" 
case ${cmd} in 
    makeall)
        sh -c 'cd driver/binder && make -j4'
        sh -c 'cd driver/ashmem && make -j4'
        sh -c 'cd libs && make -j4'
        sh -c 'cd servicemanager && make -j4'
        sh -c 'cd test_client && make -j4'
        sh -c 'cd test_server && make -j4'
        ;;  
    clean)
        sh -c 'cd driver/binder && make clean'
        sh -c 'cd driver/ashmem && make clean'
        sh -c 'cd libs && make clean'
        sh -c 'cd servicemanager && make clean'
        sh -c 'cd test_client && make clean'
        sh -c 'cd test_server && make clean'
        ;; 
    insmod)
        sh -c 'sudo insmod driver/binder/binder_linux.ko'
        sh -c 'sudo insmod driver/ashmem/ashmem_linux.ko'
        ;; 
    rmmod)
        sh -c 'sudo rmmod binder_linux'
        sh -c 'sudo rmmod ashmem_linux'
        ;; 
   *)  
      echo "`basename ${0}`:usage: [makeall] | [clean] | [insmod] | [rmmod]" 
      exit 1
      ;; 
esac