#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRFORMAT "%.*s"
#define STRARGS(s) (int)(s).length, (s).text

typedef struct {
	size_t length;
	char *text;
} StringView;

StringView cstr_to_sv(char *cstr) {
	return (StringView){.text = cstr, .length = strlen(cstr)};
}

size_t sv_character_occurence(StringView sv, char c, bool case_sensitive) {
	size_t n = 0;
	if (case_sensitive) {
		for (size_t i = 0; i < sv.length; i++) {
			if (sv.text[i] == c) n++;
		}

		return n;
	}

	for (size_t i = 0; i < sv.length; i++) {
		if (sv.text[i] == toupper(c) || sv.text[i] == tolower(c)) n++;
	}

	return n;
}

void sv_remove_character(StringView sv_in, StringView *sv_out, char c,
						 bool case_sensitive) {

	size_t out_idx = 0;
	size_t occurrences = sv_character_occurence(sv_in, c, case_sensitive);
	sv_out->text = malloc(sv_in.length - occurrences);
	if (sv_out->text == NULL) {
		sv_out->length = 0;
		return;
	}
	if (case_sensitive) {
		for (size_t i = 0; i < sv_in.length; i++) {
			if (sv_in.text[i] != c) {
				sv_out->text[out_idx] = sv_in.text[i];
				out_idx++;
			}
		}

		sv_out->length = out_idx;
		return;
	}

	for (size_t i = 0; i < sv_in.length; i++) {
		if (sv_in.text[i] != toupper(c) && sv_in.text[i] != tolower(c)) {
			sv_out->text[out_idx] = sv_in.text[i];
			out_idx++;
		}
	}

	sv_out->length = out_idx;
	return;
}

void sv_chop_left(StringView *sv, size_t n) {
	if (sv->length < n) n = sv->length;
	sv->length -= n;
	sv->text += n;
}

void sv_chop_right(StringView *sv, size_t n) {
	if (sv->length < n) n = sv->length;
	sv->length -= n;
}

void sv_to_upper(StringView sv_in, StringView *sv_out) {

	sv_out->text = malloc(sv_in.length + 1);

	for (int i = 0; i < sv_in.length; i++)
		if (sv_in.text[i] >= 'a' && sv_in.text[i] <= 'z')
			sv_out->text[i] = sv_in.text[i] - 32;
		else

			sv_out->text[i] = sv_in.text[i];
	sv_out->length = sv_in.length;
	sv_out->text[sv_in.length + 1] = '\0';
}

void sv_to_lower(StringView sv_in, StringView *sv_out) {
	sv_out->text = (char *)malloc(sv_in.length + 1);
	if (sv_out->text == NULL) return;
	for (int i = 0; i < sv_in.length; i++)
		if (sv_in.text[i] >= 'A' && sv_in.text[i] <= 'Z')
			sv_out->text[i] = sv_in.text[i] + 32;
		else
			sv_out->text[i] = sv_in.text[i];

	sv_out->text[sv_in.length + 1] = '\0';
}

void sv_to_cstr(StringView sv_in, char *dest_cstr) {
	size_t dest_size = sv_in.length + 1;
	for (size_t i = 0; i < dest_size; i++) { dest_cstr[i] = sv_in.text[i]; }
	dest_cstr[sv_in.length] = '\0';
}

int main() {
	StringView s = cstr_to_sv("wd;   -==-=-=- LAAA LA LA LA WAIT TILL I GET MY "
							  "MONEY RIGHTTT erindeltarune");

	StringView buf;
	sv_remove_character(s, &buf, 'l', false);

	printf(STRFORMAT "\n", STRARGS(buf));
	printf("%llu", sv_character_occurence(s, 'l', false));

	return 0;
}
