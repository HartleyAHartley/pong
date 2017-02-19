#include "game.h"

Game::Game(float t, unsigned int w, unsigned int h, bool f) {
    lastFrame = Clock::now();
    m_screenWidth = w;
    m_screenHeight = h;
    m_fullscreen = f;
    timeScale = t;

    try {
        m_renderer = new Renderer( SDL_INIT_VIDEO | SDL_INIT_TIMER, m_screenHeight, m_screenWidth, m_fullscreen);
    } catch ( const GameError & err ) {
        std::cerr << "Error while initializing SDL:  "
                  << err.what()
                  << std::endl;
        m_initError = true;
    }
    m_eventHandler = new EventHandler(this);
    m_eventHandler->Update();

    std::shared_ptr<GameObject> ball = std::make_shared<Ball>("Ball",this);
    m_gameobjects["Ball"] = ball;

    std::shared_ptr<GameObject> ai = std::make_shared<PlayerPaddle>("AIPaddle", this, true, 0.875);
    m_gameobjects["AIPaddle"] = ai;
    std::shared_ptr<GameObject> player = std::make_shared<PlayerPaddle>("AIPaddleTwo", this, true);
    m_gameobjects["AIPaddleTwo"] = player;

    m_KeyCB.callback = std::bind(&close, this);
    m_KeyCB.keyDown = true;
    m_KeyCB.sc = SDL_SCANCODE_ESCAPE;
    GeteventHandler()->RegisterKeyCallback(&m_KeyCB);
}

Game::~Game() {
    delete m_renderer;
    delete m_eventHandler;
}

void Game::Draw() {
    m_renderer->Draw();
}

void Game::Step() {
    m_eventHandler->Update();
    for(auto const& i : m_gameobjects){
        i.second->Update();
    }
}

void Game::DTime(){
    dTime = Clock::now() - lastFrame;
    dTime *= timeScale;
    lastFrame = Clock::now();
}
