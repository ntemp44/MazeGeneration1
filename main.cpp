#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include <thread>
#include <cstdlib>
#include <iostream>

std::random_device rd;
std::mt19937 gen(rd());

class Cell {
private:
    char m_state;
public:
    Cell() {
        m_state = 219;
    }
    char getState() {
        return m_state;
    }
    void setState(char status) {
        m_state = status;
    }
};

class Maze {
private:
    int m_height;
    int m_width;
    std::vector<std::vector<Cell>> m_board;

public:
    Maze(int w, int h) : m_height(h), m_width(w) {
        m_board.resize(m_height, std::vector<Cell>(m_width));
    }

    void displayMaze() {
        for (int y = 0; y < m_height; y++) {
            for (int x = 0; x < m_width; x++) {
                std::cout << m_board[y][x].getState();
            }
            std::cout << std::endl;
        }
    }
    void generateMaze(int x, int y) {
        m_board[x][y].setState(32);
        std::vector<std::pair<int, int>> directions = {{0, -2},{0, 2}, {2,0}, {-2, 0}};
        std::shuffle(directions.begin(), directions.end(), gen);
        for (auto dir : directions) {
            int nextX = x + dir.first;
            int nextY = y + dir.second;
            if (nextX >= 0 && nextX < m_width && nextY >= 0 && nextY < m_height && m_board[nextX][nextY].getState() == char(219)){
               m_board[x + dir.first / 2][y + dir.second / 2].setState(32);
                system("cls");
                displayMaze();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                generateMaze(nextX, nextY);
            }
        }
    }
    void createMaze() {
        std::uniform_int_distribution<> dist(2, m_board.size() - 2);
        int startX = (dist(gen) % (m_width/2)) * 2 + 1;
        int startY = (dist(gen) % (m_height/2)) * 2 + 1;

        generateMaze(startX, startY);
        m_board[m_height - 1][1].setState('E');
        m_board[0][m_width - 2].setState('S');
        system("cls");
        displayMaze();
    }
};

int main() {
    Maze myMaze(25, 25);
    myMaze.displayMaze();
    myMaze.createMaze();
    system("pause");

    return 0;
}