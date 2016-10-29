///  @file main.cpp
///  @brief Contains the main game loop, all the code for the SDl window, this is the main body of the program
#include "world.h"
#include "gameobject.h"
#include "vector2d.h"
#include "dynamicobject.h"
#include "dynamiccircle.h"
#include "staticcircle.h"
#include "staticline.h"
#include "button.h"
#define WINDOW_TITLE "Rigid Body Simlation"
//--------------------------------------------------------------------------------------------------------------------------------------------
World *scene = NULL;
Button *gui = NULL;
SDL_Window* gWindow = NULL;
SDL_GLContext gContext;
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
Uint32 timerCallback(Uint32 interval, void *)
{
    if (scene != NULL)
    {

        for(int i = 0;i < scene->m_calcs; ++i)
        {
            scene->m_startTime += 0.001;
            scene->updateObjectsVel();
            scene->updateObjectsPos();

        }
        scene->m_elapsedTime = scene->m_startTime;
        scene->m_startTime = 0;

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
            GameObject *newShape;
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

                switch (e.key.keysym.sym)
                {
                // if we have an escape quit
                case SDLK_ESCAPE : quit=1; break;
                case SDLK_g :
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
                    newShape = new StaticCircle(gui->convertPixCoorX(x), gui->convertPixCoorY(y), scene->m_shapeSize);
                    scene->m_masterList.push_back(newShape);
                };break;
                case SDLK_c :
                {
                    int x , y;
                    SDL_GetMouseState( &x, &y );
                    newShape = new DynamicCircle(gui->convertPixCoorX(x), gui->convertPixCoorY(y), scene->m_shapeSize);
                    scene->m_masterList.push_back(newShape);
                };break;
                case SDLK_q :
                {
                    std::cout<<scene->m_masterList.size()<<std::endl;
                };break;
                case SDLK_k :
                {
                    scene->m_masterList.erase(scene->m_masterList.begin(),scene->m_masterList.end());
                };break;
                case SDLK_u:
                {
                    scene->m_masterList.pop_back();
                };
                case SDLK_UP :
                {
                    scene->m_shapeSize += 1;
                };break;
                case SDLK_DOWN :
                {
                    if(scene->m_shapeSize > 2)
                        scene->m_shapeSize -= 1;
                };break;
                case SDLK_l :
                {
                    int x , y;
                    SDL_GetMouseState( &x, &y );
                    newShape = new StaticLine(gui->convertPixCoorX(x), gui->convertPixCoorY(y), gui->convertPixCoorX(x), gui->convertPixCoorY(y));
                    scene->m_masterList.push_back(newShape);
                };break;
                }
            }
            else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_l)
            {
                int x , y;
                SDL_GetMouseState( &x, &y );
                scene->m_masterList[scene->m_masterList.size()-1]->setPos2(gui->convertPixCoorX(x), gui->convertPixCoorY(y));
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN )
            {
                int x , y;
                SDL_GetMouseState( &x, &y );
                if(e.button.button == SDL_BUTTON_LEFT && gui->convertPixCoorY(y) >= 0.9)
                {
                    if((gui->convertPixCoorX(x) > gui->m_leftBounds[0]) && (gui->convertPixCoorX(x) < gui->m_leftBounds[1]))
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
                    else if((gui->convertPixCoorX(x) > gui->m_leftBounds[1]) && (gui->convertPixCoorX(x) < gui->m_leftBounds[2]))
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
                    else if((gui->convertPixCoorX(x) > gui->m_leftBounds[2]) && (gui->convertPixCoorX(x) < gui->m_leftBounds[3]))
                    {
                        if(scene->m_shapeSize > 2)
                            scene->m_shapeSize -= 1;
                    }
                    else if((gui->convertPixCoorX(x) > gui->m_leftBounds[3]) && (gui->convertPixCoorX(x) < gui->m_leftBounds[4]))
                    {
                        scene->m_shapeSize += 1;
                    }
                    else if((gui->convertPixCoorX(x) > gui->m_leftBounds[4]) && (gui->convertPixCoorX(x) < gui->m_leftBounds[5]))
                    {
                        scene->m_masterList.pop_back();
                    }
                    else if((gui->convertPixCoorX(x) > gui->m_leftBounds[5]) && (gui->convertPixCoorX(x) < 1.0F))
                    {
                        scene->m_masterList.erase(scene->m_masterList.begin(),scene->m_masterList.end());
                    }
                }
            }
        }
        //Render the scene
        scene->draw();
        //scene->updateObjects();
        for(auto& i : scene->m_masterList)
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

