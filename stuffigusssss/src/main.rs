use minifb::*;
use minifbutils::*;
use rand::*;

fn main() {
    let width = 100;
    let height = 100;

    let mut buffer: Vec<u32> = vec![0; width * height];
    let mut window: Window = Window::new(
        "i3 floating",
        width,

        height,
        WindowOptions {
            transparency: true,
            borderless: true,
            scale: Scale::X1,
            resize: true,
            title: true,
            ..WindowOptions::default()
        },
    )
    .unwrap_or_else(|e| panic!("{}", e));

    window.set_target_fps(0);
    init_utils(width, height);
    while window.is_open() && !window.is_key_down(Key::Escape) {
        buffer.resize(window.get_size().0 * window.get_size().1, 0);
        for pixel in buffer.iter_mut() {
            *pixel = rgb((random::<u32>() % 2) * 255, (random::<u32>() % 2) * 255, (random::<u32>() % 2) * 255);
        }


        window.update_with_buffer(&buffer, window.get_size().0, window.get_size().1).unwrap();
    }
}
