#include <check.h>

#include "../src/buffer.h"

START_TEST (simple_buffer_test)
{
    buffer b;
    initBuffer(&b);
    ck_assert_msg(b.status_message == NULL, "Expected buffer's status_message to be initialized to NULL, but it was not.");
}
END_TEST

START_TEST (append_line_buffer_test)
{
    buffer b;
    initBuffer(&b);
    appendLineBuffer(&b, "Test Line.");
    ck_assert_msg(b.lines != NULL, "Expected buffer to have lines, but lines is null");
    ck_assert_msg(b.num_lines == 1, "Expected buffer to have num_lines set to 1");
    destroyBuffer(&b);
    ck_assert_msg(b.lines == NULL, "Expected buffer to have freed lines, but they are not freed.");
}
END_TEST

Suite *buffer_suite() {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Buffer");
    tc_core = tcase_create("simple_tests");

    tcase_add_test(tc_core, simple_buffer_test);
    tcase_add_test(tc_core, append_line_buffer_test);
    suite_add_tcase(s, tc_core);

    return s;
}
