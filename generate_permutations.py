#! /usr/bin/python3

def itoa_with_charset(integer, charset, pad=0):
    working_value = integer
    BASE = len(charset)

    growing_str = ""
    if BASE == 1:
        # case of number system with only 1 type of digit
        # each number is just the digit repeated integer times...
        for i in range(integer):
            growing_str += charset[0]
    elif integer == 0:
        # base is NOT 1, integer is 0
        growing_str = charset[0]
    else:
        while working_value > 0:
            cur_digit = working_value % BASE
            working_value //= BASE
            growing_str = charset[cur_digit] + growing_str

    for i in range(pad - len(growing_str)):
        # pad first digits with 0th char of charset
        growing_str = charset[0] + growing_str

    return growing_str

def get_total_num_strings_from_min_to_max_len(charset, min_len, max_len):
    num = 0
    for i in range(min_len, max_len + 1):
        num += (len(charset) ** i)

    return num

def generate_strings_of_length(length, charset, buffer, callback):
    num_strings = (len(charset) ** length)

    for i in range(num_strings):
        new_word = itoa_with_charset(i, charset, length) 
        if callback is not None:
            callback(buffer, new_word)

def generate_all_strings_min_max_len(min_len, max_len, charset, buffer, callback):
    for i in range(min_len, max_len + 1):
        generate_strings_of_length(i, charset, buffer, callback)

# TESTING ;)
output = []
def my_callback(buffer, word):
    buffer.append(word)

CHARSET = "01"
str_len = 5
generate_all_strings_min_max_len(1, str_len, CHARSET, output, my_callback)
for i in range(len(output)):
    print("%d %s" % (i, output[i]))

