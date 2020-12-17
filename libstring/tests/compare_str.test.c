#include "../dist/string.h"

int main() {
    string a, b;


    a = create_str("ab");
    b = create_str("c");

    printf("res (must be -1) - %d\n", compare_str(a, b));

    a = create_str("happen");
    b = create_str("happe");

    printf("res (must be 1) - %d\n", compare_str(a, b));

    a = create_str("equal");
    b = create_str("equal");

    printf("res (must be 0) - %d\n", compare_str(a, b));

    a = create_str("aa");
    b = create_str("ab");

    printf("res (must be -1) - %d\n", compare_str(a, b));

    a = create_str("cd");
    b = create_str("cc");

    printf("res (must be 1) - %d\n", compare_str(a, b));

    return 0;
}