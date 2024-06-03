## Simple encryptor

[Hack the box Challenge](https://app.hackthebox.com/challenges/Simple%2520Encryptor)

### Build

Makefile:

```sh
make all
```

Compile files:

```sh
gcc ./encryptor.c -o out/encrypt

gcc ./decryptor.c -o out/decrypt
```

### Usage

```sh 
./encrypt <SEED> <INPUT_FILE>

./decrypt <ENCRYPTED_FILE>
```

