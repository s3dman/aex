#include <SDL2/SDL.h>
#include <vector>

int RES = 1000;

struct Vector2 {
    float x,y;
};
struct Agent {
    Vector2 position;
    Vector2 angle;
};

std::vector<Agent> Agents;


int random(int min, int max)
{
    static bool first = true;
    if (first) {
        srand( time(NULL) );
        first = false;
    }
    return min + rand() % (( max + 1 ) - min);
}
void DebugData(Agent &agent) {
    printf("(%f,%f):(%f,%f)\n",agent.position.x,agent.position.y,agent.angle.x,agent.angle.y);
}
void UpdateData(SDL_Renderer* renderer,Agent &agent,float speed=1) {
    agent.position.x += agent.angle.x*speed;
    agent.position.y += agent.angle.y*speed;

    if(agent.position.x<=0) {
        agent.angle.x *= -1;
        agent.position.x = 0;
    }
    else if (agent.position.x>=RES) {
        agent.angle.x *= -1;
        agent.position.x = RES;
    }
    if(agent.position.y<=0) {
        agent.angle.y *= -1;
        agent.position.y = 0;
    }
    else if (agent.position.y>=RES) {
        agent.angle.y *= -1;
        agent.position.y = RES;
    }

    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderDrawPoint(renderer,agent.position.x,agent.position.y);
}

// Sense
// void Sense(Agent &agent,float sangle,float slength) {
//     Vector2 max_pix = {0,0};
//     int max_intensity = -1;
//
//     for(int i=-1; i<2; ++i) {
//         for(int j=-1; j<2; ++j) {
//             if(pdata(agent.position.x+i,agent.position.y+j).r>max_intensity) {
//                 max_pix = {agent.position.x+i,agent.position.y+j};
//             }
//         }
//     }
//     // DEBUG
//     printf("(%f,%f)\n",max_pix.x,max_pix.y);
// }

// // Initialize induvigual agents with random angle at x,y
// void AgentInit(float x, float y) {
//     float randangle = GetRandomValue(0,360);
//     Vector2 agent_angle = {cos(static_cast<float>(randangle*M_PI/180)),sin(static_cast<float>(randangle*M_PI/180))};
//     agent_list.push_back(Agent{{x,y},agent_angle});
// }
//
// Initial bulk generation of agents with random angle
void RandomAgentGenerator(int n, int rangl=0, int rangr=RES) {
    for(int b=0; b<n; ++b) {
        float randangle = random(0,360);
        Vector2 agent_angle = {cos(static_cast<float>(randangle*M_PI/180)),sin(static_cast<float>(randangle*M_PI/180))};
        Agents.push_back((Agent) {
            { static_cast<float>(random(rangl,rangr)), static_cast<float>(random(rangl,rangr)) },
            agent_angle
        });
    }
}

int main()
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    if(SDL_Init(SDL_INIT_VIDEO) <0) printf("ERROR:%s\n",SDL_GetError());
    window = SDL_CreateWindow("sdl-test",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,RES,RES,SDL_WINDOW_RESIZABLE);
    if(window != NULL) {
        bool quit = false;
        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        if(renderer == NULL) quit = true;


        SDL_Texture* texture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, RES, RES);
        unsigned char* pixels;
        int pitch;
        SDL_LockTexture( texture, NULL, (void**)&pixels, &pitch );
        for(int i = 0; i < pitch * RES; i++) pixels[i] = 255;
        SDL_UnlockTexture( texture );
        SDL_SetRenderTarget( renderer, texture );


        RandomAgentGenerator(50000,0,RES);

        SDL_Event event;
        while(!quit) {
            while( SDL_PollEvent( &event ) != 0) {
                if( event.type == SDL_QUIT ) quit=true;
            }
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);

            for(int k=0; k<Agents.size(); ++k) {
                UpdateData(renderer,Agents[k]);
            }

            SDL_RenderPresent(renderer);
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
