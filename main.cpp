#include <stdio.h>

#include "test/test.h"
#include "protocol/wmp/wmp.h"

int main(int argc, char *argv[]) {
    wmp_plist packs = build_wmp_packets(NULL);

    printf("%d\n", packs.count);

    return 0;
}
