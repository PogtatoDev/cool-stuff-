package main

import (
	"unicode"
	"strconv"
)

func parse(raw string) (int, int, []int) {
	var buf string
    var colors []int
    start := false
	var width, height int

	for _, char := range raw {
		if unicode.IsSpace(char) {
			continue
		}

        if !start {
            if char == 'x' {
				width, err := strconv.ParseInt(buf, 10, 32)
				if err != nil {
					panic(err)
				}

                buf = ""
			} else if char == '=' {
				height, err := strconv.ParseInt(buf, 10, 32)
				if err != nil {
					panic(err)
				}

				buf = ""
				start = true
			} else {
				buf += string(char)
			}
		} else {
			
            if char == ';' {
				new_val, err := strconv.ParseInt(buf, 16, 32)
				if err != nil {
					panic(err)
				}


				colors = append(colors, int(new_val))
				buf = ""
            } else {
                buf += string(char);
            }
		}
	}
    if width == 0 || height == 0 {
        panic("whar");
	}
	return width, height, colors
}

func thing2_main() {

}
