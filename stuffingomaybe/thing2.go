package main

import (
	"fmt"
	"image"
	_ "image/png"
	_ "image/jpeg"
	"log"
	"os"
	"strconv"
	"unicode"
)

func parse(raw string) (int32, int32, []int32) {
	var buf string
    var colors []int32
    start := false
	var width, height int32

	for _, char := range raw {
		if unicode.IsSpace(char) {
			continue
		}

        if !start {
            if char == 'x' {
				temp, err := strconv.ParseInt(buf, 10, 32)
				width = int32(temp)
				if err != nil {
					panic(err)
				}

                buf = ""
			} else if char == '=' {
				temp, err := strconv.ParseInt(buf, 10, 32)
				height = int32(temp)


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


				colors = append(colors, int32(new_val))
				buf = ""
            } else {
                buf += string(char)
            }
		}
	}
    if width == 0 || height == 0 {
        panic("whar")
	}
	return width, height, colors
}

func convertToKIF(filename string) (*os.File, error) {
	f, err := os.Open(filename)
	if err != nil {
		fmt.Println("failed to open " + f.Name())
		return nil, err
	}

	img, _, err := image.Decode(f)
	if err != nil {
		fmt.Println(err)
		return nil, err
	}

	fmt.Println("decoded lad")
	

	rgbaToHex := func(r, g, b, a uint32) uint32 {
		return (r << 16) | (g << 8) | b
	}

	width, height := img.Bounds().Dx(), img.Bounds().Dy()
	var KIFBuffer string
	for i := range width * height {
		rgbaToHex(img.At(i % width, i / width).RGBA())
		KIFBuffer += fmt.Sprintf("%X; ", rgbaToHex(img.At(i % width, i / width).RGBA()))
		if i % 10000 == 0 {
			fmt.Printf("listing lad im at %d\n", i)
		}
	}

	err = os.WriteFile("hello.kif", []byte(KIFBuffer), 0644)
	if err != nil {
		log.Fatal("hi guys")
	}

	f, err = os.Open("hello.kif")
	if err != nil {
		log.Fatal("bye guys")
	}

	defer f.Close()

	return f, nil
}

func thing2_main() {
	convertToKIF("hi.png")
}
