#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "encrypter.h"


int prime(int n)
{
	if (n < 2) {
        return 1;
    }

    int i;
    for (i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return 1;
        }
    }

    return 0;
}


long int calculate_private_key(struct encrypter *this, long int x) {
    long int k = 1;

    while (1) {
        k = k + this->totient;
        if (k % x == 0)
            return (k / x);
    }
}

void calculate_public_key(struct encrypter *this) {
    int k = 0;
    int i = 0;
    for (i = 2; i < this->totient; i++) {
        if (this->totient % i == 0)
            continue;
        int flag = prime(i);
        if (flag == 1 || i == this->prime_one || i == this->prime_two)
            continue;
        this->public_key[k] = i;
        flag = calculate_private_key(this, this->public_key[k]);
        if (flag > 0) {
            this->private_key[k] = flag;
            k++;
        }
        if (k >= 99)
            break;
        if (k > 0 && this->private_key[k-1] == this->public_key[k] && this->private_key[k-1] == this->private_key[k])
            break;
    }
}

void encrypt(struct encrypter *this, myFile f) {
    long int pt, ct, key = this->public_key[0], k, len;
    int i = 0;
    len = strlen(f.content);
    
    while (i != len) {
        pt = this->message[i];
        pt = pt - 96;
        k = 1;
        int j;
        for (j = 0; j < key; j++) {
            k = k * pt;
            k = k % this->modulus;
        }

        this->temp[i] = k;
        ct = k + 96;
        this->encrypted_ascii[i] = ct;
        i++;
    }

    this->encrypted_ascii[i] = -1;

    printf("\nTHE ENCRYPTED MESSAGE IS\n");

    for (i = 0; this->encrypted_ascii[i] != -1; i++)
        printf("%c", this->encrypted_ascii[i]);
}

void decrypt(struct encrypter *this) {
    long int pt, ct, key = this->private_key[0], k;
    int i = 0;

    while (this->encrypted_ascii[i] != -1) {
        ct = this->temp[i];

        k = 1;
        int j;
        for (j = 0; j < key; j++) {
            k = k * ct;
            k = k % this->modulus;
        }

        pt = k + 96;
        this->message[i] = pt;
        i++;
    }

    this->message[i] = -1;

    printf("\nTHE DECRYPTED MESSAGE IS\n");

    for (i = 0; this->message[i] != -1; i++)
        printf("%c", this->message[i]);
}

encrypter newEncrypter() {
    int flag;
    encrypter myEncrypter;


    printf("\nENTER FIRST PRIME NUMBER\n");

    scanf("%d", &myEncrypter.prime_one);

    flag = prime(myEncrypter.prime_one);

    if (flag == 1) {
        printf("\nWRONG INPUT, NOT PRIME\n");
        exit(1);
    }

    printf("\nENTER ANOTHER PRIME NUMBER\n");

    scanf("%d", &myEncrypter.prime_two);

    flag = prime(myEncrypter.prime_two);

    if (flag == 1 ||  &myEncrypter.prime_one ==  &myEncrypter.prime_two) {
        printf("\nWRONG INPUT, NOT PRIME OR SAME INPUT\n");
        exit(1);
    }

    myEncrypter.modulus = myEncrypter.prime_one * myEncrypter.prime_two;
    myEncrypter.totient = (myEncrypter.prime_one - 1) * (myEncrypter.prime_two - 1);
    myEncrypter.calculate_private_key = calculate_private_key;
    myEncrypter.calculate_public_key = calculate_public_key;
    myEncrypter.encrypt = encrypt;
    myEncrypter.decrypt = decrypt;

    return myEncrypter;
}

