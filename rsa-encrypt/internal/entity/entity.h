#ifndef ENTITY_H
#define ENTITY_H

typedef struct myFile {
    char path;
    long size; 
    char* content;
} myFile;

typedef struct encrypter {
    int prime_one;
    int prime_two;
    int modulus;
    int totient;
    int temp[100];
    int *public_key[100];
    int *private_key[100];
    int message[100];
    int encrypted_ascii[100];
    long int (*calculate_private_key)(struct encrypter *this, long int x);
    void (*calculate_public_key)(struct encrypter *this);
    void (*encrypt)(struct encrypter *this, myFile f);
    void (*decrypt)(struct encrypter *this);
} encrypter;

#endif 
