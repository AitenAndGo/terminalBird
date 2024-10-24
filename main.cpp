#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Vector2 {
public:
    int x;
    int y;

    Vector2(int _x = 0, int _y = 0) {
        x = _x;
        y = _y;
    }
};

class cave{
private:
    std::vector<Vector2> Boundries;
};

class maze {
private:
    int size_x;
    int size_y;
    Vector2 start;
    Vector2 end;

    std::vector<cave> Caves;

    std::vector<std::vector<char>> map;
    std::vector<std::vector<char>> caveMap;

public:
    maze(int s = 10) : size_x(s), size_y(2*s), map(s, std::vector<char>(s*2, '#')) {
        start = Vector2(0, 0);
        end = Vector2(size_x - 1, size_y - 1);
        map[start.x][start.y] = 'S';
        map[end.x][end.y] = 'E';
    }

    ~maze() {};

    void generateMaze(int noise = 50, int gen = 1){

        for (size_t i = 1; i < size_x-1; i++)
        {
            for (size_t j = 1; j < size_y-1; j++)
            {
                if (rand() % 100 <= noise){
                    map[i][j] = '#';
                } else{
                    map[i][j] = ' ';
                }
            }
        }

        for (int g = 0; g < gen; g++){

            std::vector<std::vector<char>> Newmap = map;

            for (size_t i = 1; i < size_x-1; i++)
            {
                for (size_t j = 1; j < size_y-1; j++)
                {
                    int wallCount = 0;
                    for (int x = i - 1; x <= i + 1; x++){
                        for (int y = j - 1; y <= j + 1; y++){
                            if (x != i || y != j){
                                if (Newmap[x][y] == '#'){
                                    wallCount++;
                                }
                            }
                        }
                    }
                    if (wallCount >= 4){
                        map[i][j] = '#';
                    } else{
                        map[i][j] = ' ';
                    }
                }
            }
        }
    }

    void connectCaves(){
        findCaves();
    }

    void findCaves(){
        caveMap = map;
        int index = 0;

        for (int i = 1; i < size_x - 1; i++){
            for (int j = 1; j < size_y - 1; j++){
                if (caveMap[i][j] == ' '){
                    Caves.push_back(fillCave(i, j, index));
                }
            }
        }
    }

    cave fillCave(int x, int y, int index){
        cave newCave;
        return newCave;
    }

    std::vector<std::vector<char>> getMap() {
        return map;
    }
};

class ARES {
public:
    void draw(std::vector<std::vector<char>> map) {
        for (const auto& row : map) {
            for (const char cell : row) {
                std::cout << cell;
            }
            std::cout << "\n";
        }
    }
};

int main() {

    srand(static_cast<unsigned int>(time(0)));

    ARES window;
    maze Cave(60);

    Cave.generateMaze(39, 7);
    Cave.connectCaves();

    window.draw(Cave.getMap());

    return 0;
}
