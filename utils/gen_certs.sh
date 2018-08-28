#!/usr/bin/env sh

function gen_cert() {
    mkdir -p assets/certs
    openssl genrsa -out assets/certs/${1}_priv.key $2
    openssl rsa -in assets/certs/${1}_priv.key -pubout -outform PEM -out assets/certs/${1}_pub.key
}

gen_cert 256 2048
gen_cert 384 4096
gen_cert 512 8192
