use minifb::{Window, WindowOptions};
use minifbutils::{Vector2, init_utils};
const WIDTH: usize = 1024;
const HEIGHT: usize = 1024;

struct Vector3<T> {
    x: T,
    y: T,
    z: T
}

impl<T> Vector3<T> {
    fn new(x: T, y: T, z: T) -> Self {
        Vector3 {
            x: x,
            y: y,
            z: z
        }
    }
}


fn convert_space(position: &Vector2<f32>) -> Vector2<u32> {
    Vector2::new(
        ((position.x + 1.0) / 2.0 * WIDTH as f32) as u32,
        ((position.y + 1.0) / 2.0 * HEIGHT as f32) as u32,
    )
}

fn draw_marker(position: &Vector2<u32>, buffer: &mut Vec<u32>) {
    let size = 25;
    minifbutils::draw_rect(
        &Vector2::new(position.x, position.y),
        0x00FF00,
        size,
        size,
        true,
        buffer,
    );
}

fn project(position: &Vector3<f32>) -> Vector2<f32> {
    Vector2::new(position.x / position.z, position.y / position.z)
}

fn main() {
    let mut window: Window =
        Window::new("hi guys", WIDTH, HEIGHT, WindowOptions::default()).expect("whar");
    init_utils(WIDTH, HEIGHT);

    window.set_target_fps(60);


    let mut buffer = vec![0; WIDTH * HEIGHT];

    let mut z_off: f32 = -1.0;


    while window.is_open() {
        z_off -= 1.0 / 60.0;

        let vertices: Vec<Vector3::<f32>> = vec![
            Vector3::new(-0.5, -0.5, z_off),
            Vector3::new(-0.5, 0.5, z_off),
            Vector3::new(0.5, 0.5, z_off),
            Vector3::new(0.5, -0.5, z_off),
            Vector3::new(-0.5, -0.5, z_off + 1.0),
            Vector3::new(-0.5, 0.5, z_off + 1.0),
            Vector3::new(0.5, 0.5, z_off + 1.0),
            Vector3::new(0.5, -0.5, z_off + 1.0)
        ];

        buffer.fill(0x000000);

        for v in vertices.iter() {
            draw_marker(&convert_space(&project(&v)), &mut buffer);
        }

        window.update_with_buffer(&buffer, WIDTH, HEIGHT).unwrap();
    }
}
