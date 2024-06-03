OUT_DIR=out

encryptor:
	gcc ./encryptor.c -o $(OUT_DIR)/encrypt

decryptor:
	gcc ./decryptor.c -o $(OUT_DIR)/decrypt

all: encryptor decryptor