#!/bin/sh

cmd="${1}" 
case ${cmd} in 
    insmod)
        sh -c 'sudo insmod driver/binder/binder_linux.ko'
        sh -c 'sudo insmod driver/ashmem/ashmem_linux.ko'
        ;; 
    rmmod)
        sh -c 'sudo rmmod binder_linux'
        sh -c 'sudo rmmod ashmem_linux'
        ;; 
   *)  
      echo "`basename ${0}`:usage: [insmod] | [rmmod]" 
      exit 1
      ;; 
esac