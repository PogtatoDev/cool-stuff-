use image::{DynamicImage, GenericImageView};
use minifb::*;
use std::env::{self, args};
use std::fmt::Write;
use std::io::{self, Write as IOWrite};

fn parse(raw: String) -> (usize, usize, Vec<u32>) {
    println!("[INFO]: started parsing .kif format into buffer");
    let mut buf: String = String::new();
    let mut colors: Vec<u32> = Vec::new();
    let mut start: bool = false;
    let mut resolution: (usize, usize) = (0, 0);

    for i in raw.chars() {
        if i.is_whitespace() {
            continue;
        }

        if !start {
            if i == 'x' {
                resolution.0 = buf
                    .parse::<usize>()
                    .expect("[FATAL]: failed to parse .kif file width");

                println!("[INFO]: parsed .kif file width");
                buf.clear()
            } else if i == '=' {
                resolution.1 = buf
                    .parse::<usize>()
                    .expect("[FATAL]: failed to parse .kif file height");

                println!("[INFO]: parsed .kif file height");
                println!("[INFO]: starting to read colors from .kif file");
                buf.clear();
                start = true;
                continue;
            } else {
                buf.push(i);
            }
        }

        if start {
            if i == ';' {
                colors.push(
                    u32::from_str_radix(buf.as_str(), 16)
                        .expect("[FATAL]: failed to read colors from .kif file"),
                );
                buf.clear();
            } else {
                buf.push(i);
            }
        }
    }

    println!("[INFO]: finished reading colors from .kif file");

    if resolution.0 == 0 || resolution.1 == 0 {
        panic!("[FATAL] Dude genuinely idk wtf went wrong here");
    } else {
        println!("[INFO]: parsed .kif file into .kif buffer");
        (resolution.0, resolution.1, colors)
    }
}

fn convert_to_kif(filename: String) -> String {
    println!("[INFO]: start converting file {} to .kif format", &filename);
    let mut img: DynamicImage = DynamicImage::new(0, 0, image::ColorType::Rgb16);
    match image::open(&filename) {
        hwello 
        Ok(i) => {
            img = i;
            println!("[INFO]: loaded file {}", &filename);
        }

        Err(e) => {
            eprintln!("[ERROR]: failed to open file {}: {}", &filename, e);
            print!("Try again? [y/N]: ");
            io::stdout().flush().unwrap();

            let mut input = String::new();
            io::stdin()
                .read_line(&mut input)
                .expect("[FATAL]: failed to read y/n from stdin");

            match input.trim().to_lowercase().as_str() {
                "y" => {
                    img = image::open(&filename).expect(&format!(
                        "[FATAL]: failed to open file {} after second attempt",
                        filename
                    ))
                }
                _ => {
                    println!("Exiting...");
                    std::process::exit(0);
                }
            };
        }
    }

    let mut kif_file = String::new();
    write!(kif_file, "{}x{}=", img.width(), img.height()).unwrap();

    println!("[INFO]: started writing pixels to .kif format");
    for (_x, _y, pixel) in img.pixels() {
        let channels = pixel.0;
        write!(
            kif_file,
            "{:02x}{:02x}{:02x};",
            channels[0], channels[1], channels[2]
        )
        .expect("[FATAL]: failed to write image pixels to .kif format");
    }

    println!("[INFO]: finished converting file to .kif format");
    kif_file
}

fn main() {
    let arghhh: Vec<String> = args().collect();
    for arg in arghhh.iter().skip(1) {
        let data_raw: String = convert_to_kif(arg.clone());
        let (width, height, buffer): (usize, usize, Vec<u32>) = parse(data_raw);
        println!("[INFO]: image width: {}", width);
        println!("[INFO]: image height: {}", height);
        println!("[INFO]: .kif buffer length: {}", buffer.len());

        let mut window: Window = Window::new(
            "image viewer??!?!?!?",
            width,
            height,
            WindowOptions {
                resize: true,
                ..WindowOptions::default()
            },
        )
        .expect("[FATAL]: failed to initialize minifb window");

        println!("[INFO]: initialized minifb window");

        window.set_target_fps(30);
        window.update_with_buffer(&buffer, width, height).unwrap();
        let mut old_size: (usize, usize) = (0, 0);

        while window.is_open() {
            window.update();
            if window.get_size() != old_size {
                window.update_with_buffer(&buffer, width, height).unwrap();
            }

            old_size = window.get_size();
        }
    }
}
