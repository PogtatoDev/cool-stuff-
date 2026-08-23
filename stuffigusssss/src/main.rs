use minifb::*;
use num_traits::AsPrimitive;
use std::time::Instant;
use minifbutils::*;
const HEIGHT: usize = 1024 / 2;
const WIDTH: usize = 1024 / 2;

fn main() {
    let mut buffer: Vec<u32> = vec![0; WIDTH * HEIGHT];
    let mut window: Window = Window::new("i3 floating", WIDTH, HEIGHT, WindowOptions::default())
        .unwrap_or_else(|e| panic!("{}", e));
    window.set_target_fps(120);
    init_utils(WIDTH, HEIGHT);
    let mut held_down: bool = false;
    let mut original_pos: Vector2<u32> = Vector2::new(0, 0);
    let mut current_pos: Vector2<u32>;
    while window.is_open() && !window.is_key_down(Key::Escape) {
        buffer.fill(0);
        if window.get_mouse_down(MouseButton::Left) && !held_down {
            held_down = true;
            original_pos = tuple_to_vector2(
                window
                    .get_mouse_pos(MouseMode::Clamp)
                    .unwrap_or_else(|| panic!("lawd")),
            );
        } else if window.get_mouse_down(MouseButton::Left) && held_down {
            current_pos = tuple_to_vector2(window.get_mouse_pos(MouseMode::Clamp).unwrap_or_else(|| panic!("lawd")));
            if (original_pos.x as i32 - current_pos.x as i32) > 0 && original_pos.y as i32 - current_pos.y as i32 > 0{
            let min_x = original_pos.x.min(current_pos.x);
            let min_y = original_pos.y.min(current_pos.y);
            let width = (original_pos.x as i32 - current_pos.x as i32).abs() as u32;
            let height = (original_pos.y as i32 - current_pos.y as i32).abs() as u32;
                draw_rect(
                    &Vector2::new(min_x, min_y),
                    minifbutils::RED,
                    width,
                    height,
                    false,
                    &mut buffer,
                )
            }
        } else {
            held_down = false;
        }

        window.update_with_buffer(&buffer, WIDTH, HEIGHT).unwrap();
    }
}
