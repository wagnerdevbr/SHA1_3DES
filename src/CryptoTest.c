
#include <stdio.h>
#include <stdlib.h>
#include <sha1.h>
#include <DES.h>

Boolean testSHA1(
		uint16 dataLength,
		uint8* plainSource,
		uint8* hashTarget){

    SHA1Context tmpSHA1Context;
    SHA1Reset( &tmpSHA1Context );
    SHA1Input( &tmpSHA1Context, plainSource, dataLength );
    SHA1Result( &tmpSHA1Context, (uint8*) hashTarget );

    return True;

}

Boolean test3DES2KeysEncrypt(
		uint8 *keys1,
		uint8 *keys2,
		uint8 *plainSource,
		uint8 *cipherTarget){

	gl_3des_ctx context;

	gl_3des_set2keys(&context, keys1, keys2);

	gl_3des_ecb_encrypt(&context, plainSource, cipherTarget);

    return True;


}

Boolean test3DES2KeysDecrypt(
		uint8 *keys1,
		uint8 *keys2,
		uint8 *cipherTarget,
		uint8 *plainSource) {

	gl_3des_ctx context;

	gl_3des_set2keys(&context, keys1, keys2);

	gl_3des_ecb_decrypt(&context, cipherTarget, plainSource);

	return True;
}

Boolean test3DES3KeysDecrypt(
		uint8 *keys1,
		uint8 *keys2,
		uint8 *keys3,
		uint8 *cipherTarget,
		uint8 *plainSource) {

	gl_3des_ctx context;

	gl_3des_set3keys(&context,keys1, keys2, keys3);

	gl_3des_ecb_decrypt(&context, cipherTarget, plainSource);

	return True;
}

void print(uint8 hash[], uint8 size){
	for (int i = 0; i < size; i++) {
		printf("%02X ", hash[i]);
	}
	printf("\n");
}



int main(void) {

	/**
	 * SHA-1
	 */
	uint8 plainSource[16]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	uint8 hash[20];

	printf("Entrada para SHA-1\n");
	print(plainSource,sizeof(plainSource));

	testSHA1(sizeof(plainSource),plainSource,hash);

	printf("HASH obtido no SHA-1\n");
	print(hash,sizeof(hash));

	/**
	 * 3DES
	 */

	uint8 tmpSystemKey1[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	uint8 tmpSystemKey2[8]={0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA};
	printf("Chaves para 3DES\n");
	print(tmpSystemKey1,sizeof(tmpSystemKey1));
	print(tmpSystemKey2,sizeof(tmpSystemKey2));

	uint8 plainSourceBefore[8]={0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF};
	printf("Entrada para 3DES\n");
	print(plainSourceBefore,sizeof(plainSourceBefore));

	uint8 cipherTarget[8];

	test3DES2KeysEncrypt(
				tmpSystemKey1,
    			tmpSystemKey2,
				plainSourceBefore,
				cipherTarget);

	printf("Cifra obtida no 3DES\n");
	print(cipherTarget,sizeof(cipherTarget));

	uint8 plainSourceAfter[8];

	test3DES2KeysDecrypt(
				tmpSystemKey1,
    			tmpSystemKey2,
				cipherTarget,
				plainSourceAfter);
	printf("Descriptografando com 2 chaves\n");
	print(plainSourceAfter,sizeof(plainSourceAfter));

	test3DES3KeysDecrypt(
				tmpSystemKey1,
    			tmpSystemKey2,
				tmpSystemKey1,
				cipherTarget,
				plainSourceAfter);

	printf("Descriptografando com 3 chaves\n");
	print(plainSourceAfter,sizeof(plainSourceAfter));

	return EXIT_SUCCESS;
}
