use minifb::*;
use rand::*;

const HEIGHT: usize = 1024;
const WIDTH: usize = 1024;

struct Vector2<T> {
    x: T,
    y: T
}

impl<T> Vector2<T> {
    fn new(x: T, y: T) -> Self {
        Self { x, y }
    }
}

fn index_to_position(index: u32) -> Vector2<u32> {
    Vector2::new(
        (index as usize % WIDTH) as u32,
        ((index as usize / WIDTH) as f32).floor() as u32,
    )
}

fn position_to_index(position: Vector2<u32>) -> u32 {
    (position.y as usize * WIDTH + position.x as usize) as u32
}

#[inline]
fn rgb(r: u32, g: u32, b: u32) -> u32 {
    (r << 16) | (g << 8) | b
}


fn main() {
    let mut buffer: Vec<u32> = vec![0; WIDTH * HEIGHT];
    let mut window: Window = Window::new("i3 floating", WIDTH, HEIGHT, WindowOptions::default())
        .unwrap_or_else(|e| panic!("{}", e));
    let mut rng = rand::rng();
    window.set_target_fps(0);

    while window.is_open() {
        for (i, pixel) in buffer.iter_mut().enumerate() {

        }
        window.update_with_buffer(&buffer, WIDTH, HEIGHT).unwrap();
    }
}
