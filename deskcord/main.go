package main

import (
	"encoding/json"
	"fmt"
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
	"time"

	"github.com/bwmarrin/discordgo"
)

var client *http.Client
var token string
var cat_timer time.Ticker

func init() {
	client = &http.Client{}
	token = os.Getenv("FWEH")
	cat_timer = *time.NewTicker(1 * time.Second)
}

func main() {
	dg, err := discordgo.New("Bot " + token)
	if err != nil {
		log.Fatal("couldnt open discordgo for some reason what (" + err.Error() + ")")
	}

	dg.AddHandler(michealTimeHellYeah)
	dg.Identify.Intents = discordgo.MakeIntent(discordgo.IntentsGuildMessages | discordgo.IntentsDirectMessages)

	log.Println("added message created handler and intent")

	err = dg.Open()
	log.Println("websocket open")
	if err != nil {
		log.Fatal(err)
		return
	}

	log.Println("the bot is RUNNING. sigterm it or whatever to kill it")
	sc := make(chan os.Signal, 1)
	signal.Notify(sc, syscall.SIGINT, syscall.SIGTERM, os.Interrupt)
	<-sc
	
	log.Println("closing websocket ...")
	dg.Close()
}

func michealTimeHellYeah(s *discordgo.Session, m *discordgo.MessageCreate) {
	sendMessage := func(msg string) {
		_, err := s.ChannelMessageSend(
			m.ChannelID,
			msg,
		)

		log.Fatal("failed to send message!!! (" + err.Error() + ")")
	}

	if m.Author.ID == s.State.User.ID {
		return
	}

	if m.GuildID == "1403504316354134026" && m.Author.ID == "1324266845414625290" {
		sendMessage("https://gif.fxtwitter.com/tweet_video/HQkcWVRXsAEv2RT.webp")
	}

	if m.GuildID == "" && m.Author.ID == "1470860308875710716" {
		_, err := s.ChannelMessageSend(
			"1397697562051350541",
			m.Content,
		)

		if err != nil {
			log.Fatal(err)
		}
	}

	if rand.IntN(10) == 0 {
		sendMessage("kill yourself")
		if rand.IntN(50) == 50 {
			sendMessage("KILL YOURSELF")
		}
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
			resp.Body.Close()
			log.Fatal("i couldnt send the request nooo (" + err.Error() + ")")
		}

		defer resp.Body.Close()

		jsonData, err := io.ReadAll(resp.Body)
		var data struct{ Comments []struct{ Comment string } }
		err = json.Unmarshal(jsonData, &data)

		if err != nil {
			log.Fatal("what the flip (" + err.Error() + ")")
		}

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
	case "cat", "carlo":
		krisNDB, err := os.ReadFile("ndb.txt")
		if err != nil {
			log.Fatal("i dont wanna do these error messagse anymore (" + err.Error() + ")")
		}

		lines := strings.Split(string(krisNDB), "\n")
		found := false

		for i, line := range lines {
			if strings.Contains(line, m.Author.ID) {
				cats, _ := strconv.Atoi(line[:strings.IndexByte(line, ':')])
				if m.Content == "cat" {
					cats += 1
				} else {
					cats += 1000
				}
				sendMessage(fmt.Sprintf("<@%s> has %d jarops", m.Author.ID, cats))
				lines[i] = fmt.Sprintf("%d:%s", cats, m.Author.ID)
				found = true

				break
			}
		}

		if !found {
			lines = append(lines, "1:" + m.Author.ID)
		}

		output := strings.Join(lines, "\n")
		err = os.WriteFile("ndb.txt", []byte(output), 0644)

		if err != nil {
			log.Fatal(err)
		}
	case "dog":
		krisNDB, err := os.ReadFile("ndb.txt")
		if err != nil {
			log.Fatal(err)
		}

		lines := strings.Split(string(krisNDB), "\n")

		for i, line := range lines {
			if strings.Contains(line, m.Author.ID) {
				sendMessage("kys i reset your jarops")
				lines[i] = fmt.Sprintf("0:%s", m.Author.ID)

				output := strings.Join(lines, "\n")
				err = os.WriteFile("ndb.txt", []byte(output), 0644)


				if err != nil {
					log.Fatal(err)
				}

				break
			}
		}
	}
}
