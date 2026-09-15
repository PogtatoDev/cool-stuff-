use std::{thread::sleep, time::Duration};
use std::io::{self, BufRead};
use rand::*;

struct WordleGame {
    word: String,
    current_guess: usize,
    guesses: [String; 6],
    is_running: bool,
}

impl WordleGame {
    fn new(word: String) -> Self {
        WordleGame {
            word: word.to_uppercase(),
            current_guess: 0,
            guesses: std::array::from_fn(|_| String::from("")),
            is_running: true,
        }
    }

    fn draw(&mut self) {
        print!("\x1B[2J");
        for guess in self.guesses.iter() {
            if guess.is_empty() {
                println!("* * * * *");
            } else {
                for (i, c) in guess.char_indices() {
                    let mut color: &str = "\x1B[0;97m";
                    if self.word.contains(c) {
                        color = "\x1B[43m";
                        if self.word.as_bytes()[i] == c as u8 {
                            color = "\x1B[42m";
                        }
                    }

                    print!("{}{}\x1B[0m ", color, c.to_ascii_uppercase());
                }

                print!("\n")
            }
        }

        print!("\n");

        if self.current_guess == 6 {
            println!("tge word was '{}'", self.word);
            self.is_running = false
        }
    }

    fn make_guess(&mut self, guess: &String) {
        if *guess == self.word {
            println!("yeah lad");
            self.is_running = false;
        }

        if guess.len() == 5 && !guess.contains(" ") && guess.is_ascii() {
            self.guesses[self.current_guess] = guess.to_uppercase();
            self.current_guess += 1;
            self.draw();
        } else {
            self.draw();
            if guess.contains(" ") || !guess.is_ascii() {
                println!("no spaces or utf-8 characters");
            } else if guess.len() != 5 {
                println!("5 letter words only oidiot");
            }
        }
    }
}


fn main() {
    let temp = std::fs::read_to_string("dictionary.txt").unwrap();
    let dict: Vec<&str> = temp.split(';').collect();

    let mut lllaalal = dict[rng().random_range(0..dict.len())];
    lllaalal = lllaalal.trim_end();

    let mut game = WordleGame::new(String::from(lllaalal));
    let mut guess_buffer = String::new();

    game.draw();

    while game.is_running {
        io::stdin().read_line(&mut guess_buffer).unwrap();
        guess_buffer = String::from(guess_buffer.trim_end()).to_ascii_uppercase();
        game.make_guess(&guess_buffer);
        guess_buffer = String::new();
    }
}
