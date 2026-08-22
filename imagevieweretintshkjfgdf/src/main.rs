use minifb::*;

const HEIGHT: usize = 1024;
const WIDTH: usize = 1024;

struct Vector2<T> {
    x: T,
    y: T,
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

fn position_to_index(position: &Vector2<u32>) -> u32 {
    (position.y as usize * WIDTH + position.x as usize) as u32
}

#[inline]
fn rgb(r: u32, g: u32, b: u32) -> u32 {
    (r << 16) | (g << 8) | b
}

fn draw_pixel(position: &Vector2<u32>, color: u32, buffer: &mut Vec<u32>) -> () {
    let idx: u32 = position_to_index(position);
    buffer[idx as usize] = color;
}

fn draw_rect(
    position: Vector2<u32>,
    color: u32,
    width: u32,
    height: u32,
    filled: bool,
    mut buffer: &mut Vec<u32>,
) -> () {
    let mut cursor: Vector2<u32> = Vector2::new(position.x, position.y);
    if filled {
        let mut counter: u32 = 0;
        for i in 0..(width * height) {
            if i % width == 0 {
                counter += 1;
                cursor = Vector2::new(position.x, position.y + counter);
            }
            cursor.x += 1;
            draw_pixel(&cursor, color, &mut buffer);
        }
    } else {
       for _ in 0..width {
           cursor.x += 1;
           draw_pixel(&cursor, color, &mut buffer);
       }
       for _ in 0..height {
           cursor.y += 1;
           draw_pixel(&cursor, color, &mut buffer);
       }
       for _ in 0..width {
           cursor.x -= 1;
           draw_pixel(&cursor, color, &mut buffer);
       }
       for _ in 0..height {
           cursor.y -= 1;
           draw_pixel(&cursor, color, &mut buffer);
       }
    }
}

fn main() {
    let mut buffer: Vec<u32> = vec![0; WIDTH * HEIGHT];
    let mut window: Window = Window::new("i3 floating", WIDTH, HEIGHT, WindowOptions::default())
        .unwrap_or_else(|e| panic!("{}", e));
    window.set_target_fps(30);
    let mut temp: bool = false;

    while window.is_open() && !window.is_key_down(Key::Escape) {
        for pixel in buffer.iter_mut() {
            *pixel = 0;
        }
        draw_rect(
            Vector2::new(50, 50),
            rgb(255, 0, 0),
            100,
            100,
            true,
            &mut buffer,
        );
        window.update_with_buffer(&buffer, WIDTH, HEIGHT).unwrap();
    }
}
