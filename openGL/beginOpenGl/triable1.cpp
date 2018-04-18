
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include <iostream>
#include "shader/Shader.h"


int main(void)
{	
    // Notre fenêtre
	
    SDL_Window* fenetre(0);
    SDL_Event evenements;
    bool terminer(false);
	
	SDL_GLContext contexteOpenGL(0);
	
	
    // Initialisation de la SDL
	
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
		
        return -1;
    }
	
	
    // Création de la fenêtre

    fenetre = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(fenetre == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return -1;
    }
	//INITIALIZE OPENGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);
    
	//DOUBLE BUFFER
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	contexteOpenGL = SDL_GL_CreateContext(fenetre);
	if (contexteOpenGL == 0)
	{
		std::cout << SDL_GetError() << std::endl;
		SDL_DestroyWindow(fenetre);
		SDL_Quit();
		return (-1);
	}

	float vertices[] =  {-0.5,-0.5,  0.0,0.5,  0.5,-0.5};//triangles1
	//float colors[] =  {0.0,204.0/255.0,1.0,  0.0,204.0/255.0,1.0,  0.0,204.0/255.0,1.0 };//triangles1
	float colors[] =  {1.0,0.0,0.0,  0.0,1.0,0.0, 0.0,0.0,1.0};//triangles1
	// Boucle principale
   
   //Shader shaderBasique("Shaders/basique_2D.vert","Shaders/basique.frag");
   Shader shaderCouleur("shader/Shaders/couleur2D.vert","shader/Shaders/couleur2D.frag");
   //shaderBasique.charger();
   shaderCouleur.charger();
   
   while(!terminer)
    {
		SDL_WaitEvent(&evenements);
		
		if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
			terminer = true;
		glClear(GL_COLOR_BUFFER_BIT);
		//glUseProgram(shaderBasique.getProgramID());
		glUseProgram(shaderCouleur.getProgramID());

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,0, vertices);
			glEnableVertexAttribArray(0);
			

			glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0, colors);
			glEnableVertexAttribArray(1);

			glDrawArrays(GL_TRIANGLES, 0, 6);
			
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(0);

		glUseProgram(0);
		SDL_GL_SwapWindow(fenetre);
    }
	
	
    // On quitte la SDL
	SDL_GL_DeleteContext(contexteOpenGL);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
	
    return 0;
}
