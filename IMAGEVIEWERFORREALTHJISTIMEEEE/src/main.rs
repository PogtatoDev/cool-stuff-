use minifb::*;
use std::fs::File;
use std::io::prelude::*;
use std::env::args;


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
                colors.push(u32::from_str_radix(buf.as_str(), 16).expect("input must be a proper .kif file"));
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

fn main() -> std::io::Result<()> {
    let arghhh: Vec<String> = args().collect();
    let mut img: File = File::open(arghhh[1].clone())?;
    let mut data_raw = String::new();
    img.read_to_string(&mut data_raw)?;
    let (width, height, buffer) = parse(data_raw).unwrap();
    dbg!(buffer.len());
    dbg!(width, height);

    let mut window: Window = Window::new("image viewer??!?!?!?", width, height, WindowOptions::default()).unwrap();
    window.set_target_fps(60);

    while window.is_open() {
        window.update_with_buffer(&buffer, width, height).unwrap();
    }

    Ok(())
}
