use minifb::*;
use std::time::Instant;

const HEIGHT: usize = 1024;
const WIDTH: usize = 1024;

const RED: u32 = 0xFF0000;
const BLUE: u32 = 0x00FF00;
const GREEN: u32 = 0x0000FF;
const BLACK: u32 = 0x000000;
const WHITE: u32 = 0xFFFFFF;

struct Vector2<T> {
    x: T,
    y: T,
}

impl<T> Vector2<T> {
    fn new(x: T, y: T) -> Self {
        Self { x, y }
    }
}

#[inline]
fn index_to_position(index: u32) -> Vector2<u32> {
    Vector2::new(
        (index as usize % WIDTH) as u32,
        ((index as usize / WIDTH) as f32) as u32,
    )
}

#[inline]
fn position_to_index(x: u32, y: u32) -> u32 {
    (y as usize * WIDTH + x as usize) as u32
}

#[inline]
fn rgb(r: u32, g: u32, b: u32) -> u32 {
    (r << 16) | (g << 8) | b
}

#[inline]
fn draw_pixel(position: &Vector2<u32>, color: u32, buffer: &mut Vec<u32>) -> () {
    buffer[position_to_index(position.x, position.y) as usize] = color;
}

fn draw_rect(
    position: &Vector2<u32>,
    color: u32,
    width: u32,
    height: u32,
    filled: bool,
    mut buffer: &mut Vec<u32>,
) -> () {
    let start_x: usize = position.x as usize;
    let start_y: usize = position.y as usize;
    let end_x: usize = (start_x + width as usize).min(WIDTH);
    let end_y: usize = (start_y + height as usize).min(HEIGHT);

    if start_x >= WIDTH || start_y >= HEIGHT {
        return;
    }

    if filled {
        for y in start_y..end_y {
            let row_start: usize = position_to_index(start_x as u32, y as u32) as usize;
            let row_end: usize = position_to_index(end_x as u32, y as u32) as usize;
            buffer[row_start..row_end].fill(color);
        }
    } else {
        let mut cursor: Vector2<u32> = Vector2::new(position.x, position.y);
        draw_pixel(&cursor, color, &mut buffer);
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
    window.set_target_fps(120);

    let mut player_pos: Vector2<f32> = Vector2::new(0.0, 0.0);
    let mut last_time = Instant::now();
    let speed = 1000.0;
    while window.is_open() && !window.is_key_down(Key::Escape) {
        buffer.fill(BLACK);
        let now = Instant::now();
        let delta_time = now.duration_since(last_time).as_secs_f32();
        last_time = now;
        if window.is_key_down(Key::Up) {
            player_pos.y -= speed * delta_time;
        }
        if window.is_key_down(Key::Down) {
            player_pos.y += speed * delta_time;
        }
        if window.is_key_down(Key::Right) {
            player_pos.x += speed * delta_time;
        }
        if window.is_key_down(Key::Left) {
            player_pos.x -= speed * delta_time;
        }
        player_pos.x = player_pos.x.clamp(0.0, (WIDTH - 100) as f32);
        player_pos.y = player_pos.y.clamp(0.0, (HEIGHT - 100) as f32);

        let render_pos = Vector2::new(player_pos.x as u32, player_pos.y as u32);
        draw_rect(&render_pos, RED, 100, 100, true, &mut buffer);
        window.update_with_buffer(&buffer, WIDTH, HEIGHT).unwrap();
    }
}
