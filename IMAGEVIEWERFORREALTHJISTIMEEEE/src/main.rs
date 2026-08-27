use image::GenericImageView;
use minifb::*;
use std::env::{self, args};
use std::fmt::Write;

fn parse(raw: String) -> std::result::Result<(usize, usize, Vec<u32>), String> {
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
                resolution.0 = buf.parse::<usize>().unwrap();
                buf.clear()
            } else if i == '=' {
                resolution.1 = buf.parse::<usize>().unwrap();
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
                        .expect("failed to convert to .kif file apparently"),
                );
                buf.clear();
            } else {
                buf.push(i);
            }
        }
    }

    if resolution.0 == 0 || resolution.1 == 0 {
        Err("???".to_string())
    } else {
        Ok((resolution.0, resolution.1, colors))
    }
}

fn convert_to_kif(filename: String) -> String {
    let img = image::open(filename).unwrap();
    let mut kif_file = String::new();
    write!(kif_file, "{}x{}=", img.width(), img.height()).unwrap();

    for (_x, _y, pixel) in img.pixels() {
        let channels = pixel.0;
        write!(
            kif_file,
            "{:02x}{:02x}{:02x};",
            channels[0], channels[1], channels[2]
        )
        .unwrap();
    }

    kif_file
}

fn main() {
    let arghhh: Vec<String> = args().collect();
    let data_raw: String = convert_to_kif(arghhh[1].clone());
    let (width, height, buffer): (usize, usize, Vec<u32>) = parse(data_raw).unwrap();
    dbg!(buffer.len());
    dbg!(width, height);

    let mut window: Window = Window::new(
        "image viewer??!?!?!?",
        width,
        height,
        WindowOptions {
            resize: true,
            ..WindowOptions::default()
        },
    )
    .unwrap();
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
