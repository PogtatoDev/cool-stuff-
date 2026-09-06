package main

import (
	"encoding/json"
	"io"
	"log"
	"math"
	"math/rand/v2"
	"net/http"
	"os"
	"os/signal"
	"strconv"
	"strings"
	"syscall"

	"github.com/bwmarrin/discordgo"
)

var client *http.Client

func init() {
	client = &http.Client{}
}

func main() {
	token := os.Getenv("FWEH")
	dg, err := discordgo.New("Bot " + token)
	if err != nil {
		log.Fatal("whar")
		return
	}

	dg.AddHandler(michealTimeHellYeah)
	dg.Identify.Intents = discordgo.IntentsGuildMessages

	err = dg.Open()
	if err != nil {
		log.Fatal("no way lad")
		return
	}
	sc := make(chan os.Signal, 1)
	signal.Notify(sc, syscall.SIGINT, syscall.SIGTERM, os.Interrupt)
	<-sc

	dg.Close()
}

func michealTimeHellYeah(s *discordgo.Session, m *discordgo.MessageCreate) {
	sendMessage := func(ID string) error {
		_, err := s.ChannelMessageSend(
			m.ChannelID,
			ID,
		)

		if err != nil {
			return err
		}

		return nil
	}
	if m.Author.ID == s.State.User.ID {
		return
	}

	if m.GuildID == "1403504316354134026" {
		if m.Author.ID == "1324266845414625290" {
			sendMessage("https://gif.fxtwitter.com/tweet_video/HQkcWVRXsAEv2RT.webp")
			return
		}
	}

	if rand.IntN(10-0) == 0 {
		sendMessage("kill yourself")
	}

	if strings.Contains(m.Content, "unbeatable") {
		sendMessage("beat my ! :joy: :joy: :joy:")
	}

	if strings.Contains(strings.ToLower(m.Content), "random") && strings.Contains(strings.ToLower(m.Content), "comment") {
		sendMessage("die")
	}

	switch m.Content {
	case "bomb deme reference":
		for i := range 3 {
			sendMessage(strconv.Itoa(int(math.Abs(float64(3 - i)))))
		}

		sendMessage("bom b")
	case "micheal":
		sendMessage("are you taking the micheal")
		sendMessage("https://klipy.com/gifs/renmakesmusic-micheal")
	
	case "demirramon":
		payload := strings.NewReader(`origin=comments&page=1`)
		req, err := http.NewRequest("POST", "https://demirramon.com/ajax/comments/load", payload)
		if err != nil {
			log.Fatal("no lad")
			return
		}

		req.Header.Set("Content-Type", "application/x-www-form-urlencoded")

		resp, err := client.Do(req)
		if err != nil {
			return
		}

		defer resp.Body.Close()

		jsonData, err := io.ReadAll(resp.Body)
		var data struct{ Comments []struct{ Comment string } }
		_ = json.Unmarshal(jsonData, &data)

		sendMessage(data.Comments[1].Comment)
	case "die die die":
		s.Close()
		os.Exit(0)

	case "green goo":
		msg, err := os.ReadFile("greengoo")
		if err != nil {
			log.Fatal("lad")
			return
		}

		sendMessage(string(msg))
	}

	
	switch m.Author.ID {
	case s.State.User.ID:
		return
	case "1324266845414625290": // arop
		sendMessage(m.Content + "\nhttps://gif.fxtwitter.com/tweet_video/HQkcWVRXsAEv2RT.webp")
		return
	case "1385380882273140756": // switchflip
		s.MessageReactionAdd(m.ChannelID, m.ID, "⭐")
		return
	case "1006951658774863943": // duck
		sendMessage("what time he guck")
		return
	case "1163184972912398397": // who
		sendMessage("orooeoeroero")
		return
	case "948354771729911828":
		sendMessage(m.Content)
		s.MessageReactionAdd(m.ChannelID, m.ID, "🇫")
		s.MessageReactionAdd(m.ChannelID, m.ID, "🅰️")
		s.MessageReactionAdd(m.ChannelID, m.ID, "🇬")
		return
	}
}
