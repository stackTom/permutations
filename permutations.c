#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char * itoa_with_charset(int integer, char *charset, int pad, char *buf) {
    int working_value = integer;
    const size_t str_len = strlen(charset);
    const size_t BASE = str_len;

    if (BASE == 1) {
        // case of number system with only 1 type of digit
        // each number is just the digit repeated integer times...
        memset(buf, charset[0], integer);
        buf[integer] = '\0';
    } else if (integer == 0) {
        buf[0] = charset[0];
        buf[1] = '\0';
    } else {
        // get the size first to not have to realloc
        size_t str_size = 0;
        while (working_value > 0) {
            int cur_digit = working_value % BASE;
            working_value /= BASE;
            str_size++;
        }
        working_value = integer;
        int i = str_size;
        buf[i] = '\0';
        while (working_value > 0) {
            i--;
            int cur_digit = working_value % BASE;
            working_value /= BASE;
            buf[i] = charset[cur_digit];
        }
    }

    const size_t buf_len = strlen(buf);
    const int difference = pad - buf_len;
    if (buf_len < pad) {
        // buf_len +1 because memmove copies n bytes. need to copy null byte as well
        memmove(buf + difference, buf, buf_len + 1);
        memset(buf, charset[0], difference);
    }

    return buf;
}

size_t get_total_num_strings_from_min_to_max_len(char *charset, int min_len, int max_len) {
    size_t num = 0;

    size_t len_charset = strlen(charset);
    for (int i = min_len; i < max_len + 1; i++) {
        num += pow(len_charset, i);
    }

    return num;
}

void generate_strings_of_length(int length, char *charset, char *buffer, void (*callback)(char *buffer, char *new_word)) {
    const size_t num_strings = pow(strlen(charset), length);

    for (int i = 0; i < num_strings; i++) {
        char *buf = (char *) malloc(sizeof(char) * (length + 1));
        char *new_word = itoa_with_charset(i, charset, length, buf);
        if (callback) {
            (*callback)(buffer, new_word);
        }
        free(new_word);
    }
}

void generate_all_strings_min_max_len(int min_len, int max_len, char *charset, char *buffer, void (*callback)(char *buffer, char *new_word)) {
    for (int i = min_len; i < max_len + 1; i++) {
        generate_strings_of_length(i, charset, buffer, callback);
    }
}

// TESTING ;)
int i = 0;
void my_callback(char *buffer, char *word) {
    printf("%d %s\n", i++, word);
}

int main(void) {
    char *CHARSET = "0123456789";
    const size_t str_len = 5;
    char output[32];
    generate_all_strings_min_max_len(1, str_len, CHARSET, output, &my_callback);

    return 0;
}

