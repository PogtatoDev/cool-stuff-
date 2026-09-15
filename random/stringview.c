#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define STRFORMAT "%.*s"
#define STRARGS(s) (s).count, (s).data

typedef struct {
    char *data;
    size_t count;
} String;

String charToStr(char* cstr) { return (String) {cstr, strlen(cstr)}; }

void strChopLeft(String *str, size_t n) {
    if (n > str->count) n = str->count;

    str->count -= n;
    str->data += n;
}

void strChopRight(String *str, size_t n) {
    if (n > str->count) n = str->count;
    str->count -= n;
}


void *strToChar(String str, char *out) {
    if (str.data == NULL) return NULL;
    char *buf = malloc(str.count);
    strcpy(buf, str.data);
    buf[str.count-1] = 0;
    out = buf;
    free(buf);
};

String seperateAfterChar(String *str, char c) {
    size_t i = 0;
    while (i < str->count && str->data[i] != c) {
        i += 1;
    }

    if (i < str->count) {
        String temp = *str;
        strChopLeft(str, i+1);
        return (String) { temp.data, i };
    }

    *str = (String) { NULL, 0 };
    return (String) { NULL, 0 };
}

size_t charOccurence(String str, char c) {
    size_t n = 0;
    for (int i = 0; i < str.count; i++) {
        if (str.data[i] == c) n++;
    }

    return n;
}

void removeCharacters(String *str, char c) {
    for (int i = 0; i < charOccurence(*str, c); i++) {
        char *temp1 = strToChar(*str);
        String temp2 = charToStr(temp1);
        char *temp3 = strToChar(seperateAfterChar(&temp2, c));

        strcat(temp1, temp3);
        *str = charToStr(temp1);
    }
}

void to_upper(String *sv) {
  for (int i = 0; i < sv->count; i++)
    if (sv->data[i] >= 'a' && sv->data[i] <= 'z')
      sv->data[i] = toupper(sv->data[i]);
}


int main() {
    String s = charToStr("glungingus");


    printf(STRFORMAT, STRARGS(s));
    return 0;
}
