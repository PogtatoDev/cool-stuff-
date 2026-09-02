#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <ostream>
#include <string>

#define WINDOW_W 1200
#define WINDOW_H 800

#define CELL_SIZE 16
#define COLUMNS (WINDOW_W / CELL_SIZE)
#define ROWS (WINDOW_H / CELL_SIZE)
#define CELL_N (COLUMNS * ROWS)

#define ON_COLOR sf::Color::Black
#define OFF_COLOR sf::Color::White

struct Cell {
    bool on;
    bool on_next;
    int idx;
    sf::RectangleShape sprite;

    Cell() {
        idx = 0;
        on = false;
        on_next = false;
        sprite = sf::RectangleShape({CELL_SIZE, CELL_SIZE});
    }
};

struct Game {
  private:
    sf::Vector2f index_to_position(int idx) {
        int col = idx % COLUMNS;
        int row = idx / COLUMNS;

        return sf::Vector2f(col * CELL_SIZE, row * CELL_SIZE);
    }

    int position_to_index(sf::Vector2f position) {
        int cell_x = static_cast<int>(position.x / CELL_SIZE);
        int cell_y = static_cast<int>(position.y / CELL_SIZE);
        return cell_y * COLUMNS + cell_x;
    }

    int get_neighbors(Cell *cell) {
        // SWAMP IZZO
        int neighbors = 0;

        int col = cell->idx % COLUMNS;
        int row = cell->idx / COLUMNS;

        for (int deltarune = -1; deltarune <= 1; deltarune++) {
            for (int marvel = -1; marvel <= 1; marvel++) {
                if (!deltarune && !marvel)
                    continue;

                int neighbor_col = col + marvel;
                int neighbor_row = row + deltarune;

                if (neighbor_col >= 0 && neighbor_col < COLUMNS &&
                    neighbor_row >= 0 && neighbor_row < ROWS) {

                    int neighbor_idx = neighbor_row * COLUMNS + neighbor_col;

                    if (board[neighbor_idx]->on) {
                        neighbors++;
                    }
                }
            }
        }

        return neighbors;
    }

    int generation;
    int population;
    sf::Font font = sf::Font("hello.ttf");
    sf::Text generation_text = sf::Text(font);
    sf::Text population_text = sf::Text(font);
    bool vroom;
    float auto_timeout = 0.5;
    sf::Clock auto_clock;
    std::array<Cell *, CELL_N> board;
    std::array<sf::RectangleShape, COLUMNS> rows;
    std::array<sf::RectangleShape, ROWS> columns;

    void update_state(bool lalalala) {
        generation++;
        for (Cell *cell : board) {
            int neighbors = get_neighbors(cell);
            if (cell->on) {
                if (neighbors < 2)
                    cell->on_next = false;
                if (neighbors == 2 || neighbors == 3)
                    cell->on_next = true;
                if (neighbors > 3)
                    cell->on_next = false;
            } else {
                if (neighbors == 3)
                    cell->on_next = true;
                else
                    cell->on_next = false;
            }
        }

        for (Cell *cell : board) {
            cell->on = cell->on_next;
            if (cell->on) {
                population++;
            }
        }

        population_text.setString("population: " + std::to_string(population));
        generation_text.setString("generation: " + std::to_string(generation));

        if (lalalala) {
            auto_clock.restart();
        }
    }

  public:
    sf::RenderWindow window;

    void init() {
        window = sf::RenderWindow(sf::VideoMode({WINDOW_W, WINDOW_H}),
                                  "i3 floating");
        vroom = false;
        auto_clock.start();
        population_text.move(sf::Vector2f(
            {0, static_cast<float>(population_text.getCharacterSize())}));

        generation_text.setFillColor(ON_COLOR);
        population_text.setFillColor(ON_COLOR);

        for (int i = 0; i < board.size(); i++) {
            board[i] = new Cell;

            board[i]->idx = i;
            board[i]->sprite.setPosition(index_to_position(i));
        }

        for (int i = 0; i < rows.size(); i++) {
            rows[i].setSize({1, WINDOW_H});
            rows[i].setFillColor(ON_COLOR);
            if (i >= 1) {
                rows[i].setPosition(
                    {rows[i - 1].getPosition().x + CELL_SIZE, 0});
            }
        }

        for (int i = 0; i < columns.size(); i++) {
            columns[i].setSize({WINDOW_W, 1});
            columns[i].setFillColor(ON_COLOR);
            if (i >= 1) {
                columns[i].setPosition(
                    {0, columns[i - 1].getPosition().y + CELL_SIZE});
            }
        }
    }

    void update() {
        bool next_gen = false;
        population = 0;
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto *key_pressed =
                    event->getIf<sf::Event::KeyPressed>()) {
                if (key_pressed->code == sf::Keyboard::Key::N) {
                    next_gen = true;
                }

                if (key_pressed->code == sf::Keyboard::Key::A) {
                    vroom = !vroom;
                }

                if (key_pressed->code == sf::Keyboard::Key::J) {
                    auto_timeout += 0.05;
                    std::cout << auto_timeout << std::endl;
                }

                if (key_pressed->code == sf::Keyboard::Key::K) {
                    if (auto_timeout > 0.001)
                        auto_timeout -= 0.05;
                    std::cout << auto_timeout << std::endl;
                }
            }
        }

        bool lalalala =
            (vroom && auto_clock.getElapsedTime().asSeconds() > auto_timeout);

        if (next_gen || lalalala) {
            update_state(lalalala);
        }

        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        sf::Vector2f mouse_world_pos(static_cast<float>(mouse_pos.x),
                                     static_cast<float>(mouse_pos.y));

        if (mouse_pos.x >= 0 && mouse_pos.x < WINDOW_W && mouse_pos.y >= 0 &&
            mouse_pos.y < WINDOW_H) {
            int hover_idx = position_to_index(mouse_world_pos);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                board[hover_idx]->on = true;
            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
                board[hover_idx]->on = false;
            }
        }
    }

    void draw() {
        window.clear();

        for (Cell *cell : board) {
            if (cell->on) {
                cell->sprite.setFillColor(ON_COLOR);
            } else {
                cell->sprite.setFillColor(OFF_COLOR);
            }

            window.draw(cell->sprite);
        }

        for (sf::RectangleShape &row : rows) {
            window.draw(row);
        }

        for (sf::RectangleShape &column : columns) {
            window.draw(column);
        }

        window.draw(population_text);
        window.draw(generation_text);

        window.display();
    }

    ~Game() {
        for (Cell *cell : board) {
            delete cell;
        }
    }
};

int main() {
    Game game;
    game.init();

    while (game.window.isOpen()) {
        game.update();
        game.draw();
    }

    return 0;
}
