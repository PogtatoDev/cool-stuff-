package main

import (
	"image/color"
	"log"

	"github.com/hajimehoshi/ebiten/v2"
	"github.com/hajimehoshi/ebiten/v2/vector"
)

const CANVAS_W = 640
const CANVAS_H = 640
const RECT_SIZE = 50

type vector2 struct {
	x, y int
}

type Game struct {
	clickOnCurrentTick bool
	rectPosition       vector2
}

func (g *Game) Update() error {
	g.clickOnCurrentTick = ebiten.IsMouseButtonPressed(ebiten.MouseButton0)
	return nil
}

func (g *Game) Draw(screen *ebiten.Image) {
	screen.Fill(color.RGBA{0, 0, 0, 255})

	if g.clickOnCurrentTick {
		g.rectPosition.x, g.rectPosition.y = ebiten.CursorPosition()
	}

	vector.FillRect(screen, float32(g.rectPosition.x), float32(g.rectPosition.y), RECT_SIZE, RECT_SIZE, color.White, false)
}

func (g *Game) Layout(outsideWidth, outsideHeight int) (insideWidth, insideHeight int) {
	return CANVAS_W, CANVAS_H
}


func thing1_main() {
	ebiten.SetWindowSize(CANVAS_W, CANVAS_H)
	ebiten.SetWindowTitle("i3 floating")
	ebiten.SetVsyncEnabled(false)

	err := ebiten.RunGame(&Game{})
	if err != nil {
		log.Fatal(err)
	}
}
