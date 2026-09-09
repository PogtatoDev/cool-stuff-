use std::{thread::sleep, time::Duration};

#[derive(Clone)]
struct Letter {
    is_in_word: bool,
    revealed: bool,
    character: char
}

impl Letter {
    fn new(c: char) -> Self {
        Letter {
            is_in_word: false,
            character: c.to_ascii_uppercase(),
            revealed: false
        }
    }
}

struct WordleGame {
    letters: [Letter; 26],
    current_guess: usize,
    guesses: [String; 6]
}

impl WordleGame {
    fn new() -> Self {
        let letters: [Letter; 26] = std::array::from_fn(|_| Letter::new('c'));
        let guesses: [String; 6] = std::array::from_fn(|_| String::from(""));

        WordleGame {
            letters: letters,
            current_guess: 0,
            guesses: guesses
        }
    }

    fn draw(&self) {
        print!("\x1B[2J");
        for guess in self.guesses.iter() {
            if guess.is_empty() {
                println!("* * * * *");
            } else {
                for c in guess.chars(){
                    print!("{} ", c.to_ascii_uppercase());
                }
                print!("\n")
            }
        }

        print!("\n")
    }

    fn make_guess(&mut self, guess: &'static str) {
        if guess.len() == 5 {
            self.guesses[self.current_guess] = guess.to_uppercase();
            self.current_guess += 1;
            self.draw();
        } else {
            self.draw();
            println!("5 letter words dumbass");
        }

    }
}

fn main() {
    let mut game = WordleGame::new();
}
