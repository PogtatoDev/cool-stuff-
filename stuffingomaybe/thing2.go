package main

import (
	"bufio"
	"fmt"
	"image"
	_ "image/jpeg"
	_ "image/png"
	"log"
	"os"
	"strconv"
	"unicode"
)

func parse(raw string) (int32, int32, []uint32) {
	var buf string
    var colors []uint32
    start := false
	var width, height int32

	for _, char := range raw {
		if unicode.IsSpace(char) {
			continue
		}

        if !start {
            if char == 'x' {
				temp, err := strconv.ParseUint(buf, 10, 32)
				width = int32(temp)
				if err != nil {
					panic(err)
				}

                buf = ""
			} else if char == '=' {
				temp, err := strconv.ParseUint(buf, 10, 32)
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
				new_val, err := strconv.ParseUint(buf, 16, 64)
				if err != nil {
					panic(err)
				}


				colors = append(colors, uint32(new_val))
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
		r8 := r >> 8
		g8 := g >> 8
		b8 := b >> 8
		return (r8 << 16) | (g8 << 8) | b8
	}

	width, height := img.Bounds().Dx(), img.Bounds().Dy()
	KIFFile, err := os.Create("hello.kif")

	if err != nil {
		log.Fatal(err)
	}

	var KIFWriter = bufio.NewWriter(KIFFile)
	fmt.Fprintf(KIFWriter, "%dx%d=\n", width, height)

	for i := range width * height {

		fmt.Fprintf(KIFWriter, "%X; ", rgbaToHex(img.At(i % width, i / width).RGBA()))
		fmt.Printf("listing lad im at %d\n", i)

	}

	if err != nil {
		log.Fatal("hi guys")
	}

	f, err = os.Open("hello.kif")
	if err != nil {
		log.Fatal("bye guys")
	}

	defer f.Close()

	err = KIFWriter.Flush()
	if err != nil {
		log.Fatal("ji hugs")
	}

	return f, nil
}

func thing2_main() {
	convertToKIF("hi.png")
}
