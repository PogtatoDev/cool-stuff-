use num_traits::AsPrimitive;
use std::sync::OnceLock;


static W_LOCK: OnceLock<usize> = OnceLock::new();
static H_LOCK: OnceLock<usize> = OnceLock::new();

pub fn init_utils(width: usize, length: usize) {
    W_LOCK.set(width);
    H_LOCK.set(length);
}

#[inline(always)]
fn width() -> usize {
    *W_LOCK.get().expect("initialize utils first!!!!!!!!!!!!!!")
}
#[inline(always)]
fn height() -> usize {
    *H_LOCK.get().expect("initialize utils first!!!!!!!!!!!!!!")
}

pub const RED: u32 = 0xFF0000;
pub const BLUE: u32 = 0x00FF00;
pub const GREEN: u32 = 0x0000FF;
pub const BLACK: u32 = 0x000000;
pub const WHITE: u32 = 0xFFFFFF;

pub struct Vector2<T> {
    pub x: T,
    pub y: T,
}

impl<T> Vector2<T> {
    pub fn new(x: T, y: T) -> Self {
        Self { x, y }
    }
}

#[inline]
pub fn index_to_position(index: u32) -> Vector2<u32> {
    Vector2::new(
        (index as usize % width()) as u32,
        ((index as usize / width()) as f32) as u32,
    )
}

#[inline]
pub fn position_to_index(x: u32, y: u32) -> u32 {
    (y as usize * width() + x as usize) as u32
}

#[inline]
pub fn rgb(r: u32, g: u32, b: u32) -> u32 {
    (r << 16) | (g << 8) | b
}

#[inline]
pub fn draw_pixel(position: &Vector2<u32>, color: u32, buffer: &mut Vec<u32>) -> () {
    buffer[position_to_index(position.x, position.y) as usize] = color;
}

pub fn draw_rect(
    position: &Vector2<u32>,
    color: u32,
    rect_width: u32,
    rect_height: u32,
    filled: bool,
    buffer: &mut Vec<u32>,
) -> () {
    let start_x: usize = position.x as usize;
    let start_y: usize = position.y as usize;
    let end_x: usize = (start_x + rect_width as usize).min(width());
    let end_y: usize = (start_y + rect_height as usize).min(height());

    if start_x >= width()
        || start_y >= height()
        || end_y >= height()
        || end_x >= width()
    {
        return;
    }

    if filled {
        for y in start_y..end_y {
            let row_start: usize = position_to_index(start_x as u32, y as u32) as usize;
            let row_end: usize = position_to_index(end_x as u32, y as u32) as usize;
            buffer[row_start..row_end].fill(color);
        }
    } else {
        for x in start_x..end_x {
            draw_pixel(&Vector2::new(x as u32, start_y as u32), color, buffer);
            if end_y > start_y {
                draw_pixel(&Vector2::new(x as u32, (end_y - 1) as u32), color, buffer);
            }
        }
        for y in start_y..end_y {
            draw_pixel(&Vector2::new(start_x as u32, y as u32), color, buffer);
            if end_x > start_x {
                draw_pixel(&Vector2::new((end_x - 1) as u32, y as u32), color, buffer);
            }
        }
    }
}

pub fn tuple_to_vector2<T: AsPrimitive<u32> + Copy>(tuple: (T, T)) -> Vector2<u32> {
    Vector2::<u32>::new(tuple.0.as_(), tuple.1.as_())
}
