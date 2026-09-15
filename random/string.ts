class StringView {
	text: string = '';
	len: number = 0;
}

function sv_character_occurence(sv: StringView, c: string, case_sensitive: boolean) {
	let n: number = 0;
	if (case_sensitive) {
		for (let i = 0; i < sv.len; i++) {
			if (sv.text[i] == c) n += 1;
		}
		return n;
	}

	for (let i = 0; i < sv.len; i++) {
		if (sv.text[i] == c.toUpperCase() || sv.text[i] == c.toUpperCase()) n += 1;
	}

	return n;
}

let s: StringView = new StringView;
s.len = 5;
s.text = "laabo";

console.log(sv_character_occurence(s, 'a', false));
