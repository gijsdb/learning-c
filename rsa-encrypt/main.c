#include <stdio.h>
#include <string.h>
#include "./internal/usecase/file.h"
#include "./internal/usecase/encrypter.h"

int main() {
    myFile f = newFile("encryptme.txt");
    encrypter e = newEncrypter();

    int i;
    for (i = 0; f.content[i] != '\0'; i++) {
        e.message[i] = f.content[i];
    }

    e.calculate_public_key(&e);
   
    e.encrypt(&e, f);
    e.decrypt(&e);

    return 0;
}
