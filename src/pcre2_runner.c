#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match(PCRE2_SPTR pattern, PCRE2_SPTR subject)
{
    int    errornumber;
    size_t erroroffset;

    pcre2_code *re = pcre2_compile(
        pattern,               /* the pattern */
        PCRE2_ZERO_TERMINATED, /* indicates pattern is zero-terminated */
        0,                     /* default options */
        &errornumber,          /* for error number */
        &erroroffset,          /* for error offset */
        NULL);                 /* use default compile context */

    /* Compilation failed: print the error message and exit. */

    if (re == NULL) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errornumber, buffer, sizeof(buffer));
        printf("PCRE2 compilation failed at offset %d: %s\n", (int) erroroffset,
               buffer);
        return 1;
    }

    pcre2_match_data *match_data =
        pcre2_match_data_create_from_pattern(re, NULL);

    /* Now run the match. */

    int rc = pcre2_match(
        re,                                    /* the compiled pattern */
        subject,                               /* the subject string */
        (PCRE2_SIZE) strlen((char *) subject), /* the length of the subject */
        0,          /* start at offset 0 in the subject */
        0,          /* default options */
        match_data, /* block for storing the result */
        NULL);      /* use default match context */

    /* Matching failed: handle error cases */

    if (rc < 0) {
        switch (rc) {
            case PCRE2_ERROR_NOMATCH: printf("No match\n"); break;
            default: printf("Matching error %d\n", rc); break;
        }
        pcre2_match_data_free(
            match_data);     /* Release memory used for the match */
        pcre2_code_free(re); /*   data and the compiled pattern. */
        return 1;
    }

    /* Match succeeded. Get a pointer to the output vector, where string offsets
    are stored. */
    printf("[match_1]\n\n");
    PCRE2_SIZE *ovector = pcre2_get_ovector_pointer(match_data);

    /*************************************************************************
     * We have found the first match within the subject string. If the output *
     * vector wasn't big enough, say so. Then output any substrings that were *
     * captured.                                                              *
     *************************************************************************/

    /* The output vector wasn't big enough. This should not happen, because we
    used pcre2_match_data_create_from_pattern() above. */

    if (rc == 0)
        printf("ovector was not big enough for all the captured substrings\n");

    for (int i = 0; i < rc; i++) {
        PCRE2_SPTR substring_start  = subject + ovector[2 * i];
        PCRE2_SIZE substring_length = ovector[2 * i + 1] - ovector[2 * i];
        printf("[match_1.group_%d]\nspan = [%d, %d]\nstr = '''%.*s'''\n\n", i,
               (int) (substring_start - subject),
               (int) (substring_start + substring_length - subject),
               (int) substring_length, (char *) substring_start);
    }
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: %s <pattern> <subject>\n", argv[0]);
        return 1;
    }
    return match((PCRE2_SPTR) argv[1], (PCRE2_SPTR) argv[2]);
}
