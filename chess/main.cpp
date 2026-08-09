#define DRAW_QUEUE_SIZE 256
#include "../draw_queue.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <array>
#include <stdint.h>

#define WINDOW_SIZE 1024
#define TILE_SIZE 128
#define KEY_PRESSED(k) key_pressed->code == Keyboard::Key::k

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

using namespace sf;

enum PIECE_TYPE { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };

bool bound_check(Vector2f pos) {
    return pos.x >= 0 && pos.x < WINDOW_SIZE && pos.y >= 0 &&
           pos.y < WINDOW_SIZE;
}

struct Piece {
    RectangleShape sprite;
    PIECE_TYPE type;
    i8 side;
    Piece(PIECE_TYPE t, i8 s) {
        this->type = t;
        this->side = s;
        if (this->side == 0)
            this->sprite.setFillColor(Color(100, 100, 100));
        else
            this->sprite.setFillColor(Color(166, 123, 91));

        switch (this->type) {
        case KING:
            this->sprite.setSize({100, 50});
            break;
        case QUEEN:
            this->sprite.setSize({50, 100});
            break;
        case ROOK:
            this->sprite.setSize({30, 50});
            break;
        case BISHOP:
            this->sprite.setSize({40, 40});
            break;
        case KNIGHT:
            this->sprite.setSize({10, 100});
            break;
        case PAWN:
            this->sprite.setSize({60, 60});
            break;
        }

        this->sprite.setOrigin(this->sprite.getSize() / 2.0f);
        dq_add(&this->sprite);
    }
};

int main() {
    for (auto &d : draw_queue)
        d = nullptr;

    RenderWindow game_window(sf::VideoMode({WINDOW_SIZE, WINDOW_SIZE}), "SFML");
    std::array<RectangleShape, 32> grid;

    // generate grid pattern i suppose
    // this is a lot better than the fuckass binary i was using before
    for (i8 i = 0; i < grid.size(); i++) {
        i8 col = (i % 4) * 2;
        i8 row = i / 4;

        col += (row & 1);

        grid[i].setSize({TILE_SIZE, TILE_SIZE});
        grid[i].setPosition(Vector2f(col * TILE_SIZE, row * TILE_SIZE));
        grid[i].setFillColor(Color::White);

        dq_add(&grid[i]);
    }

    std::array<Piece *, 16> w_pieces;
    std::array<Piece *, 16> b_pieces;
    // generate the pieces (temp code)
    for (i8 i = 0; i < 32; i++) {
        if (i < 16) {
            f32 row = WINDOW_SIZE - (2 * TILE_SIZE) + (TILE_SIZE / 2.0f);
            if (i > 8)
                row += TILE_SIZE;
            i32 col = i * TILE_SIZE + (TILE_SIZE / 2.0f);
            w_pieces[i] = new Piece(PAWN, 1);
            w_pieces[i]->sprite.setPosition(Vector2f(col, row));
        } else {
            if (i < 24) {
                b_pieces[i - 16] = new Piece(PAWN, 0);
                b_pieces[i - 16]->sprite.setPosition(Vector2f(
                    (i - 16) * TILE_SIZE + (TILE_SIZE / 2.0f),
                    WINDOW_SIZE - (7 * TILE_SIZE) + (TILE_SIZE / 2.0f)));
            } else
                b_pieces[i - 16] = nullptr;
        }
    }

    RectangleShape cursor({TILE_SIZE, TILE_SIZE});
    cursor.setFillColor(Color::Transparent);
    cursor.setOutlineColor(Color::Red);
    cursor.setOutlineThickness(5);
    cursor.setOrigin(cursor.getSize() / 2.0f);
    cursor.setPosition({TILE_SIZE * 1.5f, TILE_SIZE * 1.5f});
    dq_add(&cursor);

    i8 turn = 0;

    Piece *selected_piece = nullptr;

    while (game_window.isOpen()) {
        Vector2f cursor_pos = cursor.getPosition();
        Vector2f cursor_movement_vec({0, 0});

        while (const std::optional event = game_window.pollEvent()) {
            if (event->is<Event::Closed>())
                game_window.close();
            if (event->is<Event::KeyPressed>()) {
                if (const auto *key_pressed =
                        event->getIf<Event::KeyPressed>()) {
                    if (KEY_PRESSED(Q))
                        game_window.close();

                    switch (key_pressed->code) {
                    case Keyboard::Key::Q:
                        game_window.close();
                        break;

                    case Keyboard::Key::Z:
                        if (selected_piece) {
                            selected_piece = nullptr;
                            cursor.setOutlineColor(Color::Red);
                        } else {
                            FloatRect cursor_bounds = cursor.getGlobalBounds();
                            for (i8 i = 0; i < w_pieces.size(); i++) {
                                if (w_pieces[i] &&
                                    cursor_bounds.findIntersection(
                                        w_pieces[i]
                                            ->sprite.getGlobalBounds())) {
                                    selected_piece = w_pieces[i];
                                    cursor.setOutlineColor(Color::Blue);
                                    break;
                                }
                            }
                            if (!selected_piece) {
                                for (i8 i = 0; i < b_pieces.size(); i++) {
                                    if (b_pieces[i] &&
                                        cursor_bounds.findIntersection(
                                            b_pieces[i]
                                                ->sprite.getGlobalBounds())) {
                                        selected_piece = b_pieces[i];
                                        cursor.setOutlineColor(Color::Blue);
                                        break;
                                    }
                                }
                            }
                        }
                        break;

                    case Keyboard::Key::Up:
                        cursor_movement_vec = {0, -TILE_SIZE};
                        break;

                    case Keyboard::Key::Down:
                        cursor_movement_vec = {0, TILE_SIZE};
                        break;

                    case Keyboard::Key::Left:
                        cursor_movement_vec = {-TILE_SIZE, 0};
                        break;

                    case Keyboard::Key::Right:
                        cursor_movement_vec = {TILE_SIZE, 0};

                        break;

                    default:
                        break;
                    }
                }
            }
        }

        Vector2f new_pos = cursor_pos + cursor_movement_vec;
        if (bound_check(new_pos)) {
            cursor.setPosition(new_pos);
            if (selected_piece)
                selected_piece->sprite.setPosition(cursor.getPosition());
        }

        game_window.clear(Color::Black);

        for (i32 i = 0; i < DRAW_QUEUE_SIZE; i++)
            if (draw_queue[i])
                game_window.draw(*draw_queue[i]);

        game_window.display();
    }
}
