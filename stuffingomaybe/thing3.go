package main

import (
	"image/color"
	"log"
	"math/rand"
	"os"
	"time"

	"github.com/zserge/fenster"
)

func thing3_main() {
	KIFFile, err := os.ReadFile("hello.kif")
	if err != nil {
		log.Fatal("couldnt open finl")
	}

	width, height, buffer := parse(string(KIFFile))
	window, err := fenster.New(int(width), int(height), "kif viewer")
	defer window.Close()

	ticker := 0.0
	
	for window.Loop(time.Second / 240) {
		r := rand.Float64()
		ticker += 5 / (r - r / 2)
		for i := range width * height {
			buffer[i] += uint32(ticker)
			c := color.RGBA {
				R: uint8(buffer[i] >> 16) & 0xFF,
				G: uint8(buffer[i] >> 8) & 0xFF,
				B: uint8(buffer[i]) & 0xFF,
				A: uint8(ticker),
			}

			window.Set(int(i % width), int(i / width), c)
		}
	}
}
