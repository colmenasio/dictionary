//
// Created by acolm on 09/09/2024.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"
#include "bucket.h"

int main() {
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    char k1[] = "uno", k2[] = "dos", k3[] = "tres", k4[] = "cuatro", k5[] = "cinco", k6[] = "seis";
    struct BUCKET b1 = make_new_bucket(k1, &a);
    struct BUCKET b2 = make_new_bucket(k2, &b);
    struct BUCKET b3 = make_new_bucket(k3, &c);
    struct BUCKET b4 = make_new_bucket(k4, &d);
    struct BUCKET b5 = make_new_bucket(k5, &e);
    struct BUCKET b6 = make_new_bucket(k6, &f);
    struct DICTIONARY dict = make_new_dict();
    insert_bucket(&dict, &b1);
    insert_bucket(&dict, &b2);
    insert_bucket(&dict, &b3);
    insert_bucket(&dict, &b4);
    insert_bucket(&dict, &b5);
    insert_bucket(&dict, &b6);
    print_bucket(get_bucket(&dict, "dos"), "%d");

    return 0;
}