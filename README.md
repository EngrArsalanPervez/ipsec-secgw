# LEFT

```bash
./build/ipsec-secgw -c 0xf -n 4 --socket-mem 1024,0 --vdev "crypto_openssl" -- -p 0x3 -P -u 0x2 --config="(0,0,0),(1,0,1)" -d LEFT -f ./IPE_LEFT.cfg --transfer-mode poll -t 1
```

# RIGHT

```bash
./build/ipsec-secgw -c 0xf -n 4 --socket-mem 1024,0 --vdev "crypto_openssl" -- -p 0x3 -P -u 0x2 --config="(0,0,0),(1,0,1)" -d RIGHT -f ./IPE_RIGHT.cfg --transfer-mode poll -t 1
```
