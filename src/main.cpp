#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>
#include <iostream>
using namespace std;

// vector<vector<int>> findGoodGrid(int, int);
sf::Vector2i Right(1,0);
sf::Vector2i Left(-1,0);
sf::Vector2i Down(0,-1);
sf::Vector2i Up(0,1);

sf::Vector2i Dirs[4]={Right,Left,Down,Up};

bool isNextCell(sf::Vector2i prevPos,sf::Vector2i curPos){
    for(auto dir:Dirs){
        //         cout<<(prevPos+dir).x<<" "<<(prevPos+dir).y<<"\n";
        if(curPos == prevPos+dir)
            return 1;
    }
    return 0;
}

vector<vector<int>> findGoodGrid(int,int);

int main(){
    int visitedNodes = 1;
    vector<sf::Vector2i> YellowPath;
    sf::Vector2i startingCell;

    srand(time(NULL));
    int N = 10;
    int M = 10;
    int mx = -1;
    sf::RenderWindow window(sf::VideoMode(500, 500), "A Way Out", sf::Style::Close);
    vector<vector<int>> grid = findGoodGrid(N, M);

    bool visited[N][M]{};

    puts("");

    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            cout << grid[i][j] << "\t";
        }
        puts("");
    }

    sf::RectangleShape shape[N][M];
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            mx = max(grid[i][j], mx);
            shape[i][j].setSize(sf::Vector2f(50.0f, 50.0f));
            if (grid[i][j] == -1)
            {
                shape[i][j].setFillColor(sf::Color::Green);
                shape[i][j].setOutlineThickness(2.0f);
                shape[i][j].setOutlineColor(sf::Color::Cyan);
            }
            else if (grid[i][j] == 0)
            {
                shape[i][j].setFillColor(sf::Color::Blue);
                YellowPath.emplace_back(sf::Vector2i(i,j));
                startingCell=sf::Vector2i(i,j);
                visited[i][j] = 1;
            }
            else
            {
                shape[i][j].setFillColor(sf::Color( (255 - 255 * grid[i][j]/255.0), (255 - 255 * grid[i][j]/255.0), ( 255 - 255 * grid[i][j]/255.0) ));
                shape[i][j].setOutlineThickness(2.0f);
                shape[i][j].setOutlineColor(sf::Color(255 * grid[i][j]/255.0, 255 * grid[i][j]/255.0, 255 * grid[i][j]/255.0));
            }
        }
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            if(grid[i][j] == mx) {
                shape[i][j].setFillColor(sf::Color(0, 0, 0));
                shape[i][j].setOutlineThickness(2.0f);
                shape[i][j].setOutlineColor(sf::Color(0, 0, 0));
            }
            shape[i][j].setPosition(sf::Vector2f(50.0f * j, 50.0f * i));
        }
    }
    // shape.setFillColor(sf::Color::Green);
    // shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
    // shape.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));




    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i pos = sf::Mouse::getPosition(window);
        swap(pos.x,pos.y);

        pos /=50;

        if(pos.x<N && pos.x>=0 && pos.y<M && pos.y>=0){
            int i=YellowPath.back().x;
            int j=YellowPath.back().y;
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                //                 cout<<pos.x<<" "<<pos.y<<"\n";

                if(grid[pos.x][pos.y]!=-1 && isNextCell(YellowPath.back(),pos) && !visited[pos.x][pos.y]){
                    shape[pos.x][pos.y].setFillColor(sf::Color::Red);
                    visited[pos.x][pos.y] = 1;
                    visitedNodes++;
                    if(YellowPath.size()>1){
                        shape[i][j].setFillColor(sf::Color::Yellow);
                    }
                    YellowPath.emplace_back(pos);
                }
                else if (shape[pos.x][pos.y].getFillColor()==sf::Color::Yellow){

                    //                     shape[pos.x][pos.y].setFillColor(sf::Color::White);
                }
            } else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){

                if(pos == YellowPath.back() && YellowPath.size()>1){
                    shape[pos.x][pos.y].setFillColor(sf::Color::White);
                    visited[pos.x][pos.y] = 0;
                    visitedNodes--;
                    YellowPath.pop_back();
                    i=YellowPath.back().x;
                    j=YellowPath.back().y;
                    if(startingCell!=sf::Vector2i(i,j))
                        shape[i][j].setFillColor(sf::Color::Red);
                }
            }
            //             cout<<YellowPath.size()<<"\n";
        }
        window.clear();
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                window.draw(shape[i][j]);
            }
        }

        window.display();
        if(visitedNodes == mx){
            cout<<"Done"<<"\n";
            return 0;
        }
    }

    return 0;
}
