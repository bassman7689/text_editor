#include <check.h>
#include <stdlib.h>

Suite *buffer_suite();

Suite *main_suite() {
    Suite *s;

    s = suite_create("Text Editor");
    return s;
}

int main() {
    int number_failed;

    SRunner *sr = srunner_create(main_suite());
    srunner_add_suite(sr, buffer_suite());

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
