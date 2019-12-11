#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char * itoa_with_charset(int integer, char *charset, int pad) {
    int working_value = integer;
    const size_t BASE = strlen(charset);

    char *growing_str = NULL;
    const size_t str_len = strlen(charset);
    if (BASE == 1) {
        // case of number system with only 1 type of digit
        // each number is just the digit repeated integer times...
        growing_str = (char *) malloc((integer + 1) * sizeof(char));
        for (int i = 0; i < integer; i++) {
            growing_str[i] = charset[0];
        }
        growing_str[integer] = '\0';
    } else if (integer == 0) {
        growing_str = (char *) malloc(2);
        growing_str[0] = charset[0];
        growing_str[1] = '\0';
    } else {
        // get the size first to not have to realloc
        size_t str_size = 0;
        while (working_value > 0) {
            int cur_digit = working_value % BASE;
            working_value /= BASE;
            str_size++;
        }
        growing_str = (char *) malloc((str_size + 1) * sizeof(char));
        working_value = integer;
        int i = str_size;
        growing_str[i] = '\0';
        while (working_value > 0) {
            i--;
            int cur_digit = working_value % BASE;
            working_value /= BASE;
            growing_str[i] = charset[cur_digit];
        }
    }

    const size_t growing_str_len = strlen(growing_str);
    const int difference = pad - growing_str_len;
    if (growing_str_len < pad) {
        growing_str = realloc(growing_str, pad + 1);
        memmove(growing_str + difference, growing_str, growing_str_len);
    }
    for (int i = 0; i < difference; i++) {
        growing_str[i] = charset[0];
    }

    return growing_str;
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
        char *new_word = itoa_with_charset(i, charset, length);
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

