#include "world.h"
#include "gameobject.h"
#include "dynamicobject.h"
#include "dynamiccircle.h"
#include "staticcircle.h"
#include "button.h"
#define WINDOW_TITLE "Needs Work, 10/10 - IGN"
#define WIDTH 800
#define HEIGHT 800
//--------------------------------------------------------------------------------------------------------------------------------------------
World *scene = NULL;
Button *gui = NULL;
SDL_Window* gWindow = NULL;
SDL_GLContext gContext;
float convertPixCoorX(int _x);
float convertPixCoorY(int _y);
//--------------------------------------------------------------------------------------------------------------------------------------------
int initSDL()
{
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return EXIT_FAILURE;
    }
    else
    {
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        gWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
Uint32 timerCallback(Uint32 interval, void *) {
    if (scene != NULL)
    {
        for(int i = 0;i < scene->m_calcs; ++i)
        {
            scene->updateObjectsVel();
            scene->updateObjectsPos();
        }
    }
    return interval;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
int main() {
    if( initSDL() == EXIT_FAILURE )
        return EXIT_FAILURE;
    gContext = SDL_GL_CreateContext( gWindow );
    if( gContext == NULL )
        return EXIT_FAILURE;
    if( SDL_GL_SetSwapInterval( 1 ) < 0 )
    {
        fprintf(stderr, "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
    }
    gui = new Button();
    scene = new World();
    scene->init();
    scene->resize(WIDTH, HEIGHT);
    SDL_TimerID timerID = SDL_AddTimer(10, timerCallback, (void*) NULL);
    //Main loop flag
    bool quit = false;
    //Event handler
    SDL_Event e;
    //Enable text input
    SDL_StartTextInput();
    //While application is running
    while(!quit)
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            // The window has been resized
            if ((e.type == SDL_WINDOWEVENT) &&
                    (e.window.event == SDL_WINDOWEVENT_RESIZED)) {
                SDL_SetWindowSize(gWindow, e.window.data1, e.window.data2);
                scene->resize(e.window.data1, e.window.data2);
            }
            //User requests quit
            else if( e.type == SDL_QUIT ) {
                quit = true;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                GameObject *newShape;
                switch (e.key.keysym.sym)
                {
                // if we have an escape quit
                case SDLK_ESCAPE : quit=1; break;
                case SDLK_z :
                {
                    if(scene->m_gravOn)
                    {
                        scene->m_gravOn = false;
                    }
                    else
                    {
                        scene->m_gravOn = true;
                    }
                };break;
                case SDLK_x :
                {
                    if(scene->m_xray)
                    {
                        scene->m_xray = false;
                    }
                    else
                    {
                        scene->m_xray = true;
                    }
                };break;
                case SDLK_v :
                {
                    int x , y;
                    SDL_GetMouseState( &x, &y );
                    newShape = new StaticCircle(convertPixCoorX(x), convertPixCoorY(y), scene->m_shapeSize);
                    scene->masterList.push_back(newShape);
                };break;
                case SDLK_c :
                {
                    int x , y;
                    SDL_GetMouseState( &x, &y );
                    newShape = new DynamicCircle(convertPixCoorX(x), convertPixCoorY(y), scene->m_shapeSize);
                    scene->masterList.push_back(newShape);
                };break;
                case SDLK_UP :
                {
                    scene->m_shapeSize += 1;
                };break;
                case SDLK_DOWN :
                {
                    if(scene->m_shapeSize > 1)
                        scene->m_shapeSize -= 1;
                };break;
                case SDLK_SPACE :
                {
                    if(scene->m_shapeSwitch)
                    {
                        int x , y;
                        SDL_GetMouseState( &x, &y );
                        newShape = new DynamicCircle(convertPixCoorX(x), convertPixCoorY(y), scene->m_shapeSize);
                        scene->masterList.push_back(newShape);
                    }
                    else
                    {
                        int x , y;
                        SDL_GetMouseState( &x, &y );
                        newShape = new StaticCircle(convertPixCoorX(x), convertPixCoorY(y), scene->m_shapeSize);
                        scene->masterList.push_back(newShape);
                    }
                };break;
                }
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN )
            {
                int x , y;
                SDL_GetMouseState( &x, &y );
                if(convertPixCoorY(y) >= 0.9)
                {
                    if((convertPixCoorX(x) > gui->m_leftBounds[0]) && (convertPixCoorX(x) < gui->m_leftBounds[1]))
                    {
                        if(scene->m_gravOn)
                        {
                            scene->m_gravOn = false;
                        }
                        else
                        {
                            scene->m_gravOn = true;
                        }
                    }
                    else if((convertPixCoorX(x) > gui->m_leftBounds[1]) && (convertPixCoorX(x) < gui->m_leftBounds[2]))
                    {
                        if(scene->m_xray)
                        {
                            scene->m_xray = false;
                        }
                        else
                        {
                            scene->m_xray = true;
                        }
                    }
                    else if((convertPixCoorX(x) > gui->m_leftBounds[2]) && (convertPixCoorX(x) < gui->m_leftBounds[3]))
                    {
                        if(scene->m_shapeSize > 1)
                            scene->m_shapeSize -= 1;
                    }
                    else if((convertPixCoorX(x) > gui->m_leftBounds[3]) && (convertPixCoorX(x) < gui->m_leftBounds[4]))
                    {
                        scene->m_shapeSize += 1;
                    }
                    else if((convertPixCoorX(x) > gui->m_leftBounds[4]) && (convertPixCoorX(x) < gui->m_leftBounds[5]))
                    {
                        scene->m_shapeSwitch = true;
                    }
                    else if((convertPixCoorX(x) > gui->m_leftBounds[5]) && (convertPixCoorX(x) < 1.0F))
                    {
                        scene->m_shapeSwitch = false;
                    }
                }
            }
        }
        //Render the scene
        scene->draw();
        //scene->updateObjects();
        for(auto& i : scene->masterList)
        {
            i->draw(scene->m_xray);
        }
        gui->draw();
        //Update screen
        SDL_GL_SwapWindow( gWindow );
    }
    //Disable text input
    SDL_StopTextInput();
    // Disable our timer
    SDL_RemoveTimer(timerID);
    // Delete our scene
    delete scene;
    //Destroy window
    SDL_DestroyWindow( gWindow );
    //Quit SDL subsystems
    SDL_Quit();
    return EXIT_SUCCESS;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
float convertPixCoorX(int _x)
{
    float f = static_cast<float>(_x);
    f = static_cast<float>((f/WIDTH)*2-1);
    return f;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
float convertPixCoorY(int _y)
{
    float f = static_cast<float>(_y);
    float flippedHeight =  std::abs(HEIGHT-f);
    f = static_cast<float>((flippedHeight/HEIGHT)*2-1);
    return f;
}
