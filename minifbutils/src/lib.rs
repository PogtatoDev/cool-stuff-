use num_traits::AsPrimitive;
use std::sync::OnceLock;
use std::ops::{Add, Mul, Sub};


static W_LOCK: OnceLock<usize> = OnceLock::new();
static H_LOCK: OnceLock<usize> = OnceLock::new();

pub fn init_utils(width: usize, length: usize) {
    W_LOCK.set(width);
    H_LOCK.set(length);
}

#[inline(always)]
fn width() -> u32 {
    *W_LOCK.get().expect("minibufutils: utils not initialized") as u32
}
#[inline(always)]
fn height() -> u32 {
    *H_LOCK.get().expect("minibufutils: utils not initialized") as u32
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

impl<T: num_traits::Num + Copy + num_traits::NumCast> Vector2<T> {
    pub fn new(x: T, y: T) -> Self {
        Self { x, y }
    }

    pub fn rotate(self, angle_rad: f32) -> Vector2<T> {
        let cos = angle_rad.cos();
        let sin = angle_rad.sin();

        let x_rotated: f32 = num_traits::cast::<T, f32>(self.x).unwrap() * cos - num_traits::cast::<T, f32>(self.x).unwrap() * sin;
        let y_rotated: f32 = num_traits::cast::<T, f32>(self.x).unwrap() * sin - num_traits::cast::<T, f32>(self.x).unwrap() * cos;

        Vector2::new(
            num_traits::cast(x_rotated).unwrap(),
            num_traits::cast(y_rotated).unwrap()
        )
    }
}

#[inline(always)]
pub fn index_to_position(index: u32) -> Vector2<u32> {
    Vector2::new(index % width(), index / width())
}

#[inline(always)]
pub fn position_to_index(x: u32, y: u32) -> u32 {
    y * width() + x
}

#[inline(always)]
pub fn rgb(r: u32, g: u32, b: u32) -> u32 {
    (r << 16) | (g << 8) | b
}

#[inline(always)]
pub fn draw_pixel(position: &Vector2<u32>, color: u32, buffer: &mut Vec<u32>) -> () {
    if position.x > width() || position.y > height() {
        return;
    }

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
    let end_x: u32 = (position.x + rect_width).min(width());
    let end_y: u32 = (position.y + rect_height).min(height());

    if filled {
        for y in position.y..end_y {
            let row_start: u32 = position_to_index(position.x, y);
            let row_end: u32 = position_to_index(end_x, y);

            if (row_end as usize) <= buffer.len() {
                buffer[row_start as usize..row_end as usize].fill(color);
            }
        }
    } else {
        for x in position.x..end_x {
            draw_pixel(&Vector2::new(x as u32, position.y as u32), color, buffer);
            if end_y > position.y {
                draw_pixel(&Vector2::new(x as u32, (end_y - 1) as u32), color, buffer);
            }
        }
        for y in position.y..end_y {
            draw_pixel(&Vector2::new(position.x as u32, y as u32), color, buffer);
            if end_x > position.x {
                draw_pixel(&Vector2::new((end_x - 1) as u32, y as u32), color, buffer);
            }
        }
    }
}

pub fn tuple_to_vector2<T: AsPrimitive<u32> + Copy>(tuple: (T, T)) -> Vector2<u32> {
    Vector2::<u32>::new(tuple.0.as_(), tuple.1.as_())
}

pub fn draw_circle(
    mut buffer: &mut Vec<u32>,
    position: &Vector2<u32>,
    radius: u32,
    color: u32,
) -> () {
    let mut d: isize = 3 - 2 * radius as isize;
    let mut x: u32 = 0;
    let mut y = radius;
    while y >= x {
        x += 1;
        if d > 0 {
            y -= 1;
            d = d + 4 * (x as isize - y as isize) + 10;
        } else {
            d = d + 4 * x as isize + 6;
        }

        let xpx = position.x + x;       let xmx = position.x - x;
        let xpy = position.x + y;       let xmy = position.x - y;
        let ypx = position.y + x;
        let ypy = position.y + y;       let ymy = position.y - y;
        draw_pixel(&Vector2::new(xpx, ypy), color, &mut buffer);
        draw_pixel(&Vector2::new(xmx, ypy), color, &mut buffer);
        draw_pixel(&Vector2::new(xpx, ymy), color, &mut buffer);
        draw_pixel(&Vector2::new(xmx, ymy), color, &mut buffer);
        draw_pixel(&Vector2::new(xpy, ypx), color, &mut buffer);
        draw_pixel(&Vector2::new(xmy, ypx), color, &mut buffer);
        draw_pixel(&Vector2::new(xpy, xmy), color, &mut buffer);
        draw_pixel(&Vector2::new(xmy, xmy), color, &mut buffer);
    }
}
