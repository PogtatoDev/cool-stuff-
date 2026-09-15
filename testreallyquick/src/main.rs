use minifb::{Key::H, *};

const WIDTH: usize = 1200;
const HEIGHT: usize = 800;

fn rgb(r: u8, g: u8, b:u8) -> u32 {
    ((r as u32) << 16) | ((g as u32) << 8) | b as u32
}

fn main() {
    let mut buffer: Vec<u32> = vec![0; WIDTH * HEIGHT];
    let mut window = Window::new("test", WIDTH, HEIGHT, WindowOptions::default()).unwrap();
    window.set_target_fps(60);

    while window.is_open() {
        for i in 0..buffer.len() {
            let x = rand::random::<u8>();
            buffer[i] = rgb(255, i as u8 % 255, x);
        }


        window.update_with_buffer(&buffer, WIDTH, HEIGHT).unwrap();
    }
}
