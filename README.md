# UDP Multicast Sender 

A simple UDP sender with multicast addressing.

This code just send multicast packets with test message 'Hello, everybody!'

This mechanism based on the Simple Service Discovery Protocol (SSDP).

Reference:  https://tools.ietf.org/html/draft-cai-ssdp-v1-00

Andrejs Tihomirovs (c) 2019

armtech@its.lv

## Compile

Compile this code using the standard GNU C or C++ compiler:


    git clone https://github.com/armtech/sendudp.git
    cd sendudp/
    cc -o sendudp sendudp.c
    
## Run

From within the `sendudp` directory just issue:

    ./sendudp 239.255.255.250 1900
