#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <vector>
#include <iostream>
#include "include/grid.hpp"
#define tileSize 50
#define tileGap 40
#define lineHeight tileSize+tileGap
#define lineWidth 10

using namespace std;

sf::Vector2i Right(1,0);
sf::Vector2i Left(-1,0);
sf::Vector2i Down(0,-1);
sf::Vector2i Up(0,1);

sf::Vector2i Dirs[4]={Right,Left,Down,Up};

bool isNextCell(sf::Vector2i prevPos,sf::Vector2i curPos){
    for(auto dir:Dirs){
        if(curPos == prevPos+dir)
            return 1;
    }
    return 0;
}

sf::RectangleShape ConnectTwoNodes(sf::Vector2i prevPos,sf::Vector2i curPos){
    int h = lineHeight;
    int w = lineWidth;

    sf::RectangleShape R;
    int i1 = prevPos.x, j1 = prevPos.y;
    int i2 = curPos.x, j2 = curPos.y;

    // i -- Row, j -- Column

    double Y,X,F;

    if(i1 == i2){ // Horizontal
        Y = i1*(tileSize+tileGap) + tileGap + tileSize/2.0 - lineWidth/2.0;
        F = min(j1,j2);
        X = (F+1)*(tileSize+tileGap) - tileSize/2.0;
        swap(h,w);
    } else { // Vertical
        X = j1*(tileSize+tileGap) + tileGap + tileSize/2.0 - lineWidth/2.0;
        F = min(i1,i2);
        Y = (F+1)*(tileSize+tileGap) - tileSize/2.0;
    }
    R.setSize(sf::Vector2f(w,h));
    R.setPosition(sf::Vector2f(X,Y));
    return R;
}

int not_main(){
    int visitedNodes = 0;
    vector<sf::Vector2i> YellowPath;
    vector<sf::RectangleShape> LinePath;
    sf::Vector2i startingCell;


    srand(time(NULL));
    int N = 6;
    int M = 6;
    int mx = -1;
    sf::RenderWindow window(sf::VideoMode(N*tileSize+(N+1)*tileGap, M*tileSize+(M+1)*tileGap), "A Way Out", sf::Style::Close);

    sf::Image icon;
    icon.loadFromFile("Assets/icon.png"); // File/Image/Pixel
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Grid grid(N, M);

    bool visited[N][M];

    std::cout<<'\n';

    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            cout << grid[i][j] << "\t";
        }
        std::cout<<'\n';
    }

    sf::Shape *shape[N][M];

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            visited[i][j] = 0; // initialize visited array

            mx = max(grid[i][j], mx);
            if (grid[i][j] == -1)
            {
                shape[i][j] = new sf::RectangleShape();
                shape[i][j]->setFillColor(sf::Color::Green);
                shape[i][j]->setOutlineThickness(2.0f);
                shape[i][j]->setOutlineColor(sf::Color::Cyan);
                dynamic_cast<sf::RectangleShape*>(shape[i][j])->setSize(sf::Vector2f(tileSize, tileSize));
            }
            else if (grid[i][j] == 0)
            {
                shape[i][j] = new sf::CircleShape();
                shape[i][j]->setFillColor(sf::Color::Blue);
                YellowPath.emplace_back(sf::Vector2i(i,j));
                startingCell=sf::Vector2i(i,j);
                visited[i][j] = 1;
                dynamic_cast<sf::CircleShape*>(shape[i][j])->setRadius(tileSize/2.0);
            }
            else
            {
                shape[i][j] = new sf::CircleShape();
                shape[i][j]->setFillColor(sf::Color( (255 - 255 * grid[i][j]/255.0), (255 - 255 * grid[i][j]/255.0), ( 255 - 255 * grid[i][j]/255.0) ));
                shape[i][j]->setOutlineThickness(2.0f);
                shape[i][j]->setOutlineColor(sf::Color(255 * grid[i][j]/255.0, 255 * grid[i][j]/255.0, 255 * grid[i][j]/255.0));
                dynamic_cast<sf::CircleShape*>(shape[i][j])->setRadius(tileSize/2.0);
            }

            shape[i][j]->setOrigin(tileSize/2.0,tileSize/2.0);
        }
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            if(grid[i][j] == mx) {
                shape[i][j]->setFillColor(sf::Color::Cyan);
                shape[i][j]->setOutlineThickness(2.0f);
                shape[i][j]->setOutlineColor(sf::Color(0, 0, 0));
            }
            shape[i][j]->setPosition(sf::Vector2f( (j+1)*(tileSize+tileGap) - tileSize/2.0,(i+1)*(tileGap+tileSize) - tileSize/2.0) );
        }
    }

    bool isWindowFocused = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::GainedFocus) {
                // cout << "gained focus\n";
                isWindowFocused = true;
            }
            if(event.type == sf::Event::LostFocus) {
                // cout << "Lost focus\n";
                isWindowFocused = false;
            }

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Q) {
                    // cout << "q pressed. Quitting.\n";
                    window.close();
                
                }
            }
            if(isWindowFocused) {
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                swap(pos.x,pos.y);

                pos /= (tileSize+tileGap);

                if(pos.x<N && pos.x >= 0 and pos.y<M and pos.y >= 0){
                    int i=YellowPath.back().x;
                    int j=YellowPath.back().y;
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        if(grid[pos.x][pos.y] !=- 1 && isNextCell(YellowPath.back(), pos) && !visited[pos.x][pos.y]){
                            shape[pos.x][pos.y]->setFillColor(sf::Color::Red);
                            visited[pos.x][pos.y] = 1;
                            visitedNodes++;
                            if(YellowPath.size()>1){
                                shape[i][j]->setFillColor(sf::Color::Yellow);
                            }
                            LinePath.emplace_back(ConnectTwoNodes(YellowPath.back(), pos));
                            YellowPath.emplace_back(pos);
                        }
                    } else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                        if(visited[pos.x][pos.y] && YellowPath.size()>1){
                            while(YellowPath.back() != pos) {
                                auto last = YellowPath.back();
                                shape[last.x][last.y]->setFillColor(sf::Color::White);
                                visited[last.x][last.y] = false;
                                YellowPath.pop_back();
                                LinePath.pop_back();
                                visitedNodes--;
                            }
                            if(pos != startingCell) {
                                shape[pos.x][pos.y]->setFillColor(sf::Color::Red);
                            }
                        }
                    }
                }
            }
        }


        
        window.clear();

        for(auto x:LinePath){
            window.draw(x);
        }

        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                window.draw(*shape[i][j]);
            }
        }


        window.display();
        if(visitedNodes == mx){
            std::cout<<"Done"<<"\n";
            return 0;
        }
    }

    return 0;
}
