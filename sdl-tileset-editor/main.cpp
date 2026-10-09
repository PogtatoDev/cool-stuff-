#include <SFML/Graphics.hpp>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

constexpr int WINDOW_W = 640 * 2;
constexpr int WINDOW_H = 480 * 2;
constexpr int CELL_SIZE = 20 * 2;
constexpr int COLUMNS = (WINDOW_W / CELL_SIZE);
constexpr int ROWS = (WINDOW_H / CELL_SIZE);
constexpr int CELL_N = (COLUMNS * ROWS);
constexpr sf::Color ON_COLOR = sf::Color::Blue;
constexpr sf::Color OFF_COLOR = sf::Color::Black;

sf::Font f("hi.ttf");
struct Cell {
    int tile_n;
    int idx;
    sf::RectangleShape sprite;
    sf::Text label = sf::Text(f);

    Cell() {
        idx = 0;
        int tile_n = 0;
        sprite = sf::RectangleShape({CELL_SIZE, CELL_SIZE});
    }
};

struct Game {
  private:
    inline sf::Vector2f index_to_position(int idx) {
        int col = idx % COLUMNS;
        int row = idx / COLUMNS;

        return sf::Vector2f(col * CELL_SIZE, row * CELL_SIZE);
    }

    inline int position_to_index(sf::Vector2f position) {
        int cell_x = static_cast<int>(position.x / CELL_SIZE);
        int cell_y = static_cast<int>(position.y / CELL_SIZE);
        return cell_y * COLUMNS + cell_x;
    }

    std::array<Cell *, CELL_N> board;
    std::array<int, CELL_N> tiles;
    std::array<sf::RectangleShape, COLUMNS> rows;
    std::array<sf::RectangleShape, ROWS> columns;

    int current_tile_n;

  public:
    sf::RenderWindow window;

    Game() {
        window = sf::RenderWindow(sf::VideoMode({WINDOW_W, WINDOW_H}),
                                  "i3 floating");
        window.setFramerateLimit(240);

        current_tile_n = 0;

        for (int i = 0; i < board.size(); i++) {
            board[i] = new Cell;

            board[i]->idx = i;
            board[i]->sprite.setPosition(index_to_position(i));
            board[i]->label.setString(std::to_string(board[i]->tile_n));
            board[i]->label.setPosition(
                sf::Vector2f(board[i]->sprite.getPosition().x + CELL_SIZE / 3,
                             board[i]->sprite.getPosition().y + CELL_SIZE / 3));
            board[i]->label.setCharacterSize(CELL_SIZE / 2);
        }

        for (int i = 0; i < rows.size(); i++) {
            rows[i].setSize({1, WINDOW_H});
            rows[i].setFillColor(sf::Color::White);
            if (i >= 1) {
                rows[i].setPosition(
                    {rows[i - 1].getPosition().x + CELL_SIZE, 0});
            }
        }

        for (int i = 0; i < columns.size(); i++) {
            columns[i].setSize({WINDOW_W, 1});
            columns[i].setFillColor(sf::Color::White);
            if (i >= 1) {
                columns[i].setPosition(
                    {0, columns[i - 1].getPosition().y + CELL_SIZE});
            }
        }
    }

    void save() {
        std::ofstream file("out.map");
        for (int i = 0; i < board.size(); i++) {
            file << board[i]->tile_n << " ";
        }
    }

    void update() {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto *key_pressed =
                    event->getIf<sf::Event::KeyPressed>()) {

                if (key_pressed->code == sf::Keyboard::Key::S) {
                    save();
                }

                if (key_pressed->code == sf::Keyboard::Key::K) {
                    current_tile_n++;
                    std::cout << current_tile_n << std::endl;
                }

                if (key_pressed->code == sf::Keyboard::Key::J) {
                    current_tile_n--;
                    std::cout << current_tile_n << std::endl;
                }
            }
        }

        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        sf::Vector2f mouse_world_pos(static_cast<float>(mouse_pos.x),
                                     static_cast<float>(mouse_pos.y));

        if (mouse_pos.x >= 0 && mouse_pos.x < WINDOW_W && mouse_pos.y >= 0 &&
            mouse_pos.y < WINDOW_H) {
            int hover_idx = position_to_index(mouse_world_pos);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                board[hover_idx]->tile_n = current_tile_n;
                board[hover_idx]->label.setString(
                    std::to_string(board[hover_idx]->tile_n));
            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
                board[hover_idx]->tile_n = 0;
                board[hover_idx]->label.setString(
                    std::to_string(board[hover_idx]->tile_n));
            }
        }
    }

    void draw() {
        window.clear();

        for (Cell *cell : board) {
            if (cell->tile_n) {
                cell->sprite.setFillColor(ON_COLOR);
            } else {
                cell->sprite.setFillColor(OFF_COLOR);
            }

            window.draw(cell->sprite);
            window.draw(cell->label);
        }

        for (sf::RectangleShape &row : rows) {
            window.draw(row);
        }

        for (sf::RectangleShape &column : columns) {
            window.draw(column);
        }

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
    while (game.window.isOpen()) {
        game.update();
        game.draw();
    }

    return 0;
}
