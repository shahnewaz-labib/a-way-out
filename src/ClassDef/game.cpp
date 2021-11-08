#include "../include/grid.hpp"
#include "../include/game.hpp"
#include "../include/menu.hpp"
#include <exception>
#include <fstream>

sf::Color Game::dayBGCol = sf::Color(216, 226, 233, 255);
sf::Color Game::dayHoverCol = sf::Color(69, 72, 130, 255);
sf::Color Game::dayTextCol = sf::Color::Black;
sf::Color Game::nightBGCol = sf::Color(18, 18, 18, 255);
sf::Color Game::nightHoverCol = sf::Color(27, 57, 251, 255);
sf::Color Game::nightTextCol = sf::Color::White;



Game::Game(double Width,double Height):Width(Width),Height(Height) {
    readLevels();
    curBGCol = dayBGCol;
    curHoverCol = dayHoverCol;
    curTextCol = dayTextCol;
    day = true;

    srand(time(NULL));

    window = new sf::RenderWindow (sf::VideoMode(Width, Height), "A Way Out", sf::Style::Close);
    menu = new MainMenu(this,window, "A Way Out", 150, sf::Vector2f(Width / 2.0, Height - 150), 15);
    level = new Level_Select_Menu(this,window, "Select Type", 150, sf::Vector2f(Width / 2.0 - 70, Height - 150), 15);

    grid = new Grid(N, M, this,window);

    sf::Image icon;
    icon.loadFromFile("Assets/icon.png"); // File/Image/Pixel
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

}

void Game::toggleDayNight() {
    day = !day;
    curBGCol = day? dayBGCol : nightBGCol;
    curHoverCol = day? dayHoverCol : nightHoverCol;
    curTextCol = day? dayTextCol : nightTextCol;
}
sf::Color Game::getBGCol() {
    return curBGCol;
}
sf::Color Game::getHoverColor() {
    return curHoverCol;
}

sf::Color Game::getTextColor() {
    return curTextCol;
}

sf::Color Game::getInvertedTextColor() {
    return day ? sf::Color::White : sf::Color::Black;
}

void Game::play(){
    while (window->isOpen())
    {
        if(playButtonClicked && (level->getCurrentSelected()!=Level || maxLevelReached)){
            level->updateDimension(N, M);
            grid->regenGrid(N, M);
            playButtonClicked = 0;
            if(maxLevelReached){
                saveGrid();
                maxLevelReached = 0;
            }
        }

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::GainedFocus)
            {
                isWindowFocused = true;
            }
            if (event.type == sf::Event::LostFocus)
            {
                isWindowFocused = false;
            }

            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Q)
                {
                    window->close();
                }
            }
            if (currentState == state::inLevelSelect && sf::Event::TextEntered)
            {
                level->getTextInput(event.text.unicode);
            }
        }

        window->clear();

        if (currentState == state:: endProgram)
        {
            break;
        }

        if (currentState == state:: inMenu)
        {
            if (isWindowFocused)
            {
                menu->action();
            }
            menu->draw();
        }

        else if (currentState == state:: inLevelSelect)
        {
            if (isWindowFocused)
            {
                level->action();
            }
            level->draw();
        }

        else if (currentState == state:: inPlay)
        {
            if (isWindowFocused)
            {
                grid->takeInput();
            }

            grid->draw();

            if (grid->isGameSolved())
            {
                switch(level->getCurrentSelected()){
                    case Level:
                        level->setCurrentLevel(level->getCurrentLevel()+1);
                        if(level->getCurrentLevel()>numberOfLevels){
                            maxLevelReached = 1;
                        } else {
                            grid->regenGrid(-1,-1,-1,grids[level->getCurrentLevel()-1]);
                        }
                        break;
                    default:
                        break;
                }
                std::cout<<numberOfLevels<<','<<level->getCurrentLevel()<<'\n';
                playButtonClicked = 1;
            }
        }
        window->display();
    }
}

void Game::quit(){
    currentState = state::endProgram;
}

void Game::setState(state st){
    currentState = st;
}

void Game::saveGrid(){
    std::ofstream file(levelFile,std::ios::app);
    file<<N<<" "<<M<<"\n";
    
    for(int i=0;i<N;i++,file<<"\n"){
        for(int j=0;j<M;j++){
            file << (*grid)[i][j] <<" ";
        }
    }
    file.close();
    numberOfLevels++;
}

void Game::readLevels(){
    std::ifstream file(levelFile);
    if(!file) {
        numberOfLevels = 1;
        return;
    }
    int n,m,k=0;
    while(1){
        file>>n>>m;
        if(file.eof()) break;
        grids.push_back(std::vector<std::vector<int>>(n,std::vector<int>(m,-1)));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                file >> grids[k][i][j];
            }
        }
        k++;
    }
    numberOfLevels = k;
    file.close();
}
