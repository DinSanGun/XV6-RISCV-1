#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {

    char *str = "Hello World xv6\n";
    //write(1, str, strlen(str));
    printf(str);

    exit(0, "");
}