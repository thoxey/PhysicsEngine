// Includes needed for SDL and GL

#include "world.h"
#include "gameobject.h"
#include "dynamicobject.h"
#include "dynamiccircle.h"
#include "staticsquare.h"
#include "staticcircle.h"
// Change this if you want something different.
#define WINDOW_TITLE "Being outsmarted by a circle"
#define TESTSHAPE DynamicCircle
// These defines are for the initial window size (it can be changed in the resize function)
#define WIDTH 800
#define HEIGHT 800

#define STARTPOS 0.0f

// Our scene, which will store all the GL stuff
World *scene = NULL;
TESTSHAPE *testShape = NULL;
StaticSquare *square = NULL;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

//Prototyping below funtions
float convertPixCoorX(int _x);
float convertPixCoorY(int _y);

int initSDL()
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return EXIT_FAILURE;
    }
    else
    {
        //Use OpenGL 3.1 core
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
                SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
                SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
                SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
                SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        //Create window
        gWindow = SDL_CreateWindow( WINDOW_TITLE,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    WIDTH,
                                    HEIGHT,
                                    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int main() {
    //Start up SDL and create window
    if( initSDL() == EXIT_FAILURE ) return EXIT_FAILURE;

    //Create context
    gContext = SDL_GL_CreateContext( gWindow );
    if( gContext == NULL ) return EXIT_FAILURE;

    //Use Vsync
    if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
        fprintf(stderr, "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
    }

    // We should now be ready to use OpenGL
    // This object holds our scene. It needs to be initialised before it can be drawn.
    scene = new World();
    square = new StaticSquare(0,0);
    testShape = new TESTSHAPE(0,0);
    testShape->m_posY = STARTPOS;
    // Initialise the scene
    scene->init();
    // Need an initial resize to make sure the projection matrix is initialised
    scene->resize(WIDTH, HEIGHT);


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
              case SDLK_x :
              {
                  int x , y;
                  SDL_GetMouseState( &x, &y );
                  newShape = new StaticCircle(convertPixCoorX(x), convertPixCoorY(y));
                  scene->masterList.push_back(newShape);
              };break;
              case SDLK_c :
              {
                  int x , y;
                  SDL_GetMouseState( &x, &y );
                  newShape = new DynamicCircle(convertPixCoorX(x), convertPixCoorY(y));
                  scene->masterList.push_back(newShape);
               };break;
              case SDLK_v :
              {
                  int x , y;
                  SDL_GetMouseState( &x, &y );
                  newShape = new StaticSquare(convertPixCoorX(x), convertPixCoorY(y));
                  scene->masterList.push_back(newShape);
              }
            }
          }
        }
        //Render the scene
        scene->draw();
        scene->updateObjects(scene->masterList);
        for(auto& i : scene->masterList)
        {
            i->draw();
        }
        //Update screen
        SDL_GL_SwapWindow( gWindow );
    }

    //Disable text input
    SDL_StopTextInput();

    // Delete our scene
    delete scene;

    //Destroy window
    SDL_DestroyWindow( gWindow );

    //Quit SDL subsystems
    SDL_Quit();

    return EXIT_SUCCESS;
}
float convertPixCoorX(int _x)
{
    float f = static_cast<float>(_x);
    f = static_cast<float>((f/WIDTH)*2-1);
    return f;
}
float convertPixCoorY(int _y)
{
    float f = static_cast<float>(_y);
    float flippedHeight =  std::abs(HEIGHT-f);
    f = static_cast<float>((flippedHeight/HEIGHT)*2-1);
    return f;
}
