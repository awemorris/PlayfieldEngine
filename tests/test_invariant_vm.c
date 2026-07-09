#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <signal.h>

static jmp_buf jump_buffer;
static volatile sig_atomic_t segfault_occurred = 0;

static void segfault_handler(int sig) {
    segfault_occurred = 1;
    longjmp(jump_buffer, 1);
}

START_TEST(test_vm_string_copy_bounds)
{
    // Invariant: VM string operations must not corrupt stack or cause crashes regardless of input size
    const char *payloads[] = {
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",  // 256 bytes - exploit case
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",  // 128 bytes - boundary
        "valid_key"  // valid input
    };
    int num_payloads = sizeof(payloads) / sizeof(payloads[0]);

    for (int i = 0; i < num_payloads; i++) {
        segfault_occurred = 0;
        signal(SIGSEGV, segfault_handler);
        signal(SIGABRT, segfault_handler);
        
        if (setjmp(jump_buffer) == 0) {
            char script[4096];
            snprintf(script, sizeof(script), "d = {%s: 1}; return d;", payloads[i]);
            
            FILE *f = fopen("/tmp/test_vm_script.txt", "w");
            ck_assert_ptr_nonnull(f);
            fprintf(f, "%s", script);
            fclose(f);
            
            int ret = system("timeout 2 ./vm_test_harness /tmp/test_vm_script.txt 2>/dev/null");
            ck_assert_msg(WIFEXITED(ret) && (WEXITSTATUS(ret) == 0 || WEXITSTATUS(ret) == 1),
                         "VM must handle oversized strings without crashing (payload %d)", i);
        } else {
            ck_abort_msg("Stack corruption or segfault detected with payload %d", i);
        }
        
        signal(SIGSEGV, SIG_DFL);
        signal(SIGABRT, SIG_DFL);
    }
    
    unlink("/tmp/test_vm_script.txt");
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Security");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_vm_string_copy_bounds);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = security_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}