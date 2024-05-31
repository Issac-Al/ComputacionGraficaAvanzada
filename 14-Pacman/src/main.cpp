#define _USE_MATH_DEFINES
#include <cmath>
//glew include
#include <GL/glew.h>

//std includes
#include <string>
#include <iostream>
#include <sstream>
#include <regex>

//glfw include
#include <GLFW/glfw3.h>

// program include
#include "Headers/TimeManager.h"

// Shader include
#include "Headers/Shader.h"

// Model geometric includes
#include "Headers/Sphere.h"
#include "Headers/Cylinder.h"
#include "Headers/Box.h"
#include "Headers/FirstPersonCamera.h"
#include "Headers/ThirdPersonCamera.h"

// Font rendering include
#include "Headers/FontTypeRendering.h"

//GLM include
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Headers/Texture.h"

// Include loader Model class
#include "Headers/Model.h"

// Include Terrain
#include "Headers/Terrain.h"

#include "Headers/AnimationUtils.h"

// Include Colision headers functions
#include "Headers/Colisiones.h"

// ShadowBox include
#include "Headers/ShadowBox.h"

// OpenAL include
#include <AL/alut.h>

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

int screenWidth;
int screenHeight;


const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

GLFWwindow *window;

Shader shader;
//Shader con skybox
Shader shaderSkybox;
//Shader con multiples luces
Shader shaderMulLighting;
//Shader para el terreno
Shader shaderTerrain;
// Shader para dibujar un objeto con solo textura
Shader shaderTexture;
//Shader para dibujar el buffer de profunidad
Shader shaderDepth;
// Shader para visualizar el buffer de profundidad
Shader shaderViewDepth;
//Shader para las particulas de fountain
/*Shader shaderParticlesFountain;*/

std::shared_ptr<Camera> camera(new ThirdPersonCamera());
float distanceFromTarget = 7.0;

Sphere skyboxSphere(20, 20);
Box boxCesped;
Box boxWalls;
Box boxHighway;
Box boxLandingPad;
Sphere esfera1(10, 10);
Box boxCollider;
Sphere sphereCollider(10, 10);
Cylinder rayModel(10, 10, 1.0, 1.0, 1.0);
Box boxIntro;
Box boxViewDepth;

//Pacman Ghosts
Model modelGhostRed;
Model modelGhostPink;
Model modelGhostBlue;
Model modelGhostOrange; 
Model modelGhostScared;
Model modelSphere;
Model modelWall;
Model modelLargeWall;

// Modelos animados
// Mayow
Model mayowModelAnimate;
// Terrain model instance
Terrain terrain(-1, -1, 200, 8, "../Textures/heightmapPacman.png");

ShadowBox * shadowBox;

GLuint textureCespedID, textureWallID, textureWindowID, textureHighwayID, textureLandingPadID;
GLuint textureTerrainRID, textureTerrainGID, textureTerrainBID, textureTerrainBlendMapID;
GLuint skyboxTextureID;
GLuint textureInit1ID, textureInit2ID, textureActivaID, textureScreenID, textureScreenID2, textureScreenID3, textureVictoryID, textureGameOverID;
GLuint textureParticleFountainID;

bool iniciaPartida = false, presionarOpcion = false;

// Modelo para el render del texto
FontTypeRendering::FontTypeRendering *modelText;

GLenum types[6] = {
GL_TEXTURE_CUBE_MAP_POSITIVE_X,
GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

std::string fileNames[6] = { "../Textures/mp_bloodvalley/pacman_ft.tga",
		"../Textures/mp_bloodvalley/pacman_bk.tga",
		"../Textures/mp_bloodvalley/pacman_up.tga",
		"../Textures/mp_bloodvalley/pacman_dn.tga",
		"../Textures/mp_bloodvalley/pacman_rt.tga",
		"../Textures/mp_bloodvalley/pacman_lf.tga" };

bool exitApp = false;
int lastMousePosX, offsetX = 0;
int lastMousePosY, offsetY = 0;
bool gameFinished = false;

// Model matrix definitions
glm::mat4 modelMatrixMayow = glm::mat4(1.0f);
glm::mat4 modelMatrixGhostRed = glm::mat4(1.0f);
glm::mat4 modelMatrixGhostPink = glm::mat4(1.0f);
glm::mat4 modelMatrixGhostBlue = glm::mat4(1.0f);
glm::mat4 modelMatrixGhostOrange = glm::mat4(1.0f);
glm::mat4 modelMatrixWall = glm::mat4(1.0f);
glm::mat4 modelMatrixWall1 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall2 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall3 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall4 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall5 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall6 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall7 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall8 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall9 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall10 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall11 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall12 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall13 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall14 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall15 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall16 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall17 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall18 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall19 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall20 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall21 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall22 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall23 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall24 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall25 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall26 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall27 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall28 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall29 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall30 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall31 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall32 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall33 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall34 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall35 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall36 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall37 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall38 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall39 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall40 = glm::mat4(1.0f);
glm::mat4 modelMatrixWall41 = glm::mat4(1.0f);


int animationMayowIndex = 1;
int modelSelected = 0;
bool enableCountSelected = true;

float levitating_controller = 0;
float BlinkyX = 13.6f, BlinkyY = -12.8f;
int Blinky = 0;
int Pinky = 0;
int Clyde = 0;
int Inky = 0;
int direction = 1;
int directionP = 1;
int directionI = 1;
int directionC = 1;
bool powerUp = false;
bool setPowerUpTime = false;
float powerUpEndTime = 0.0;
bool reset_player = false;
int vidas = 3;
bool reset_blinky = false;
bool reset_pinky = false;
bool reset_inky = false;
bool reset_clyde = false;
int state = 0;
float advanceCount = 0.0;
float advanceCountP = 0.0;
float advanceCountI = 0.0;
float advanceCountC = 0.0;
float rotCount = 0.0;
float rotCountP = 0.0;
float rotCountI = 0.0;
float rotCountC = 0.0;
int numberAdvance = 0;
int numberAdvanceP = 0;
int numberAdvanceI = 0;
int numberAdvanceC = 0;
int maxAdvance = 0.0;
int maxAdvanceP = 0.0;
int maxAdvanceI = 0.0;
int maxAdvanceC = 0.0;
float currentTime = 0.0;
int score = 0;
int spheres_to_win = 999;

// Blending model unsorted
std::map<std::string, glm::vec3> blendingUnsorted = {
};

std::vector<glm::vec3> spherePosition = {
	//Esquina1 cuadrante 1 
	glm::vec3(-11.2, 0, 9.6),
	//Esferas en X
	glm::vec3(-14.2, 0, 9.6),
	glm::vec3(-19.2, 0, 9.6),
	glm::vec3(-24.2, 0, 9.6),
	glm::vec3(-29.2, 0, 9.6),
	glm::vec3(-34.2, 0, 9.6),
	glm::vec3(-39.2, 0, 9.6),
	glm::vec3(-44.2, 0, 9.6),
	glm::vec3(-49.2, 0, 9.6),
	glm::vec3(-54.2, 0, 9.6),
	glm::vec3(-59.2, 0, 9.6),
	glm::vec3(-64.2, 0, 9.6),
	glm::vec3(-69.2, 0, 9.6),
	glm::vec3(-74.2, 0, 9.6),
	glm::vec3(-79.2, 0, 9.6),
	glm::vec3(-84.2, 0, 9.6),
	//Esferas en Y
	glm::vec3(-11.2, 0, 16.6),
	glm::vec3(-11.2, 0, 21.6),
	glm::vec3(-11.2, 0, 26.6),
	glm::vec3(-11.2, 0, 31.6),

	//Esquina 2
	glm::vec3(-14.2, 0, 31.6), 
	glm::vec3(-19.2, 0, 31.6),
	glm::vec3(-24.2, 0, 31.6), 
	glm::vec3(-29.2, 0, 31.6),
	glm::vec3(-33.2, 0, 31.6), 
	glm::vec3(-38.2, 0, 31.6),
	glm::vec3(-43.2, 0, 31.6), 
	glm::vec3(-48.2, 0, 31.6), 
	glm::vec3(-54.2, 0, 31.6), 
	glm::vec3(-54.2, 0, 26.6),
	glm::vec3(-54.2, 0, 21.6),
	glm::vec3(-54.2, 0, 16.6),

    glm::vec3(-38.2, 0, 36.6), 
	glm::vec3(-38.2, 0, 41.6), 
	glm::vec3(-38.2, 0, 46.6), 
	glm::vec3(-38.2, 0, 51.6), 
	glm::vec3(-38.2, 0, 56.6), 
	glm::vec3(-38.2, 0, 61.6), 
	glm::vec3(-38.2, 0, 66.6), 

	glm::vec3(-32.2, 0, 66.6),
	glm::vec3(-27.2, 0, 66.6), 
	glm::vec3(-22.2, 0, 66.6), 
	glm::vec3(-22.2, 0, 71.6), 
	glm::vec3(-22.2, 0, 76.6),
	glm::vec3(-22.2, 0, 81.6),   

	//Esquina 3
	glm::vec3(-87.2, 0, 9.6),
	glm::vec3(-87.2, 0, 17.6),
	glm::vec3(-87.2, 0, 22.6),
	glm::vec3(-87.2, 0, 27.6),
	//glm::vec3(-87.2, 0, 32.6), //PowerUp
    glm::vec3(-80.2, 0, 32.6),
	glm::vec3(-75.2, 0, 32.6),
	glm::vec3(-75.2, 0, 37.6),
	glm::vec3(-75.2, 0, 42.6),
	glm::vec3(-75.2, 0, 47.6),
	glm::vec3(-75.2, 0, 52.6),
	glm::vec3(-75.2, 0, 57.6),
	glm::vec3(-75.2, 0, 62.6),
	glm::vec3(-75.2, 0, 67.6),//encrucijada
	glm::vec3(-70.2, 0, 67.6),
	glm::vec3(-65.2, 0, 67.6),
	glm::vec3(-60.2, 0, 67.6),
	glm::vec3(-54.2, 0, 62.6),
	glm::vec3(-54.2, 0, 57.6),
	glm::vec3(-54.2, 0, 52.6),
	glm::vec3(-54.2, 0, 47.6),
	glm::vec3(-54.2, 0, 42.6),
	glm::vec3(-54.2, 0, 37.6),


	glm::vec3(-81.2, 0, 67.6),
    glm::vec3(-86.2, 0, 67.6),
	glm::vec3(-86.2, 0, 70.6),
	glm::vec3(-86.2, 0, 75.6),
	glm::vec3(-86.2, 0, 80.6),
	glm::vec3(-86.2, 0, 85.6),
	//pasillo largo
	glm::vec3(-81.2, 0, 85.6),
	glm::vec3(-71.2, 0, 85.6),
	glm::vec3(-61.2, 0, 85.6),
	glm::vec3(-51.2, 0, 85.6),
	glm::vec3(-46.2, 0, 85.6),
	glm::vec3(-41.2, 0, 85.6),
	glm::vec3(-36.2, 0, 85.6),
	glm::vec3(-31.2, 0, 85.6),
	glm::vec3(-26.2, 0, 85.6),
	glm::vec3(-22.2, 0, 85.6),
	glm::vec3(-16.2, 0, 85.6),
	glm::vec3(-11.2, 0, 85.6),
	glm::vec3(-6.2, 0, 85.6),
	glm::vec3(-1.2, 0, 85.6),
	glm::vec3(4.2, 0, 85.6),
	glm::vec3(9.2, 0, 85.6),
	glm::vec3(14.2, 0, 85.6),
	glm::vec3(19.2, 0, 85.6),
	glm::vec3(24.2, 0, 85.6),
	glm::vec3(29.2, 0, 85.6),
	glm::vec3(37.2, 0, 85.6),
	glm::vec3(47.2, 0, 85.6),
	glm::vec3(57.2, 0, 85.6),
	glm::vec3(67.2, 0, 85.6),
	glm::vec3(77.2, 0, 85.6),
	glm::vec3(87.2, 0, 85.6),

	//Inicio Pasillo largo - Cuadrante 2
	glm::vec3(87.2, 0, 80.6),

	//Cuadrante 2
	glm::vec3(-6.2, 0, 31.6),
	glm::vec3(-1.2, 0, 31.6),
	glm::vec3(4.2, 0, 31.6),
	glm::vec3(9.2, 0, 31.6),
	glm::vec3(14.2, 0, 31.6),
	glm::vec3(19.2, 0, 31.6),
	glm::vec3(24.2, 0, 31.6),
	glm::vec3(29.2, 0, 31.6),
	glm::vec3(34.2, 0, 31.6),
	glm::vec3(39.2, 0, 31.6),

	glm::vec3(19.2, 0, 36.6),
	glm::vec3(19.2, 0, 41.6),
	glm::vec3(19.2, 0, 46.6),
	glm::vec3(19.2, 0, 51.6),
	glm::vec3(19.2, 0, 56.6),
	glm::vec3(19.2, 0, 61.6),
	glm::vec3(19.2, 0, 66.6),

	glm::vec3(14.2, 0, 66.6),
	glm::vec3(9.2, 0, 66.6),
	glm::vec3(4.2, 0, 66.6),

	glm::vec3(4.2, 0, 70.6),
	glm::vec3(4.2, 0, 75.6),
	glm::vec3(4.2, 0, 80.6),

	glm::vec3(9.2, 0, 28.6),
	glm::vec3(9.2, 0, 23.6),
	glm::vec3(9.2, 0, 18.6),
	glm::vec3(9.2, 0, 13.6),
	glm::vec3(9.2, 0, 8.6),
	
	glm::vec3(14.2, 0, 8.6),
	glm::vec3(24.2, 0, 8.6),
	glm::vec3(34.2, 0, 8.6),
	glm::vec3(44.2, 0, 8.6),
	glm::vec3(54.2, 0, 8.6),
	glm::vec3(64.2, 0, 8.6),
	glm::vec3(72.2, 0, 8.6),
	glm::vec3(82.2, 0, 8.6),
	glm::vec3(87.2, 0, 8.6),

    glm::vec3(87.2, 0, 14.6),
	glm::vec3(87.2, 0, 19.6),
	glm::vec3(87.2, 0, 24.6),
	glm::vec3(87.2, 0, 29.6),
	glm::vec3(87.2, 0, 34.6),
	
	//glm::vec3(87.2, 0, 39.6),//PowerUp

	glm::vec3(84.2, 0, 39.6),
	glm::vec3(79.2, 0, 39.6),
	glm::vec3(74.2, 0, 39.6),
	glm::vec3(69.2, 0, 39.6),
	glm::vec3(64.2, 0, 39.6),
	glm::vec3(59.2, 0, 39.6),

	glm::vec3(59.2, 0, 44.6),
	glm::vec3(59.2, 0, 49.6),
	glm::vec3(59.2, 0, 54.6),
	glm::vec3(59.2, 0, 60.6),

	glm::vec3(64.2, 0, 60.6),
	glm::vec3(69.2, 0, 60.6),
	glm::vec3(74.2, 0, 60.6),
	glm::vec3(79.2, 0, 60.6),
	glm::vec3(84.2, 0, 60.6),
	glm::vec3(87.2, 0, 60.6),
	
	glm::vec3(87.2, 0, 65.6),
	glm::vec3(87.2, 0, 70.6),
	glm::vec3(87.2, 0, 75.6),
	glm::vec3(87.2, 0, 80.6),

	glm::vec3(54.2, 0, 60.6),
	glm::vec3(49.2, 0, 60.6),
	glm::vec3(44.2, 0, 60.6),
	glm::vec3(39.2, 0, 60.6),

	glm::vec3(39.2, 0, 60.6),
	glm::vec3(39.2, 0, 55.6),
	glm::vec3(39.2, 0, 50.6),
	glm::vec3(39.2, 0, 45.6),
	glm::vec3(39.2, 0, 40.6),
	glm::vec3(39.2, 0, 35.6),

	//Cuadrante 3
	glm::vec3(-54.2, 0, 4.6),
	glm::vec3(-54.2, 0, -6.6),
	glm::vec3(-54.2, 0, -16.6),
	glm::vec3(-54.2, 0, -26.6),
	glm::vec3(-54.2, 0, -36.6),
	glm::vec3(-54.2, 0, -47.6),
	glm::vec3(-54.2, 0, -58.6),
	glm::vec3(-54.2, 0, -67.6),
	glm::vec3(-54.2, 0, -77.6),
	glm::vec3(-54.2, 0, -87.6),

	glm::vec3(-47.2, 0, -87.6),
	glm::vec3(-37.2, 0, -87.6),
	glm::vec3(-27.2, 0, -87.6),
	glm::vec3(-17.2, 0, -87.6),

	glm::vec3(-17.2, 0, -83.6),
	glm::vec3(-17.2, 0, -68.6),
	glm::vec3(-17.2, 0, -63.6),
	glm::vec3(-17.2, 0, -58.6),

	glm::vec3(-24.2, 0, -58.6),
	glm::vec3(-34.2, 0, -58.6),
	glm::vec3(-44.2, 0, -58.6),
	glm::vec3(-54.2, 0, -58.6), 
	glm::vec3(-64.2, 0, -58.6),
	glm::vec3(-72.2, 0, -58.6),
	glm::vec3(-82.2, 0, -58.6),
	glm::vec3(-87.2, 0, -58.6),

	glm::vec3(-87.2, 0, -52.6),
	glm::vec3(-87.2, 0, -47.6),
	glm::vec3(-87.2, 0, -42.6), 
	glm::vec3(-87.2, 0, -37.6),

	glm::vec3(-82.2, 0, -31.6),
	glm::vec3(-72.2, 0, -31.6),
	glm::vec3(-62.2, 0, -31.6),


    glm::vec3(-87.2, 0, -31.6), 
	glm::vec3(-87.2, 0, -62.6),
	glm::vec3(-87.2, 0, -67.6),
	// glm::vec3(-87.2, 0, -72.6), //PowerUp
	glm::vec3(-87.2, 0, -77.6),
	glm::vec3(-87.2, 0, -82.6),
	glm::vec3(-87.2, 0, -87.6),

	glm::vec3(-82.2, 0, -87.6),
	glm::vec3(-72.2, 0, -87.6),
	glm::vec3(-62.2, 0, -87.6),
	glm::vec3(-52.2, 0, -87.6),

	//Cuadrante 4

    glm::vec3(-19.2, 0, -58.6),
	glm::vec3(-9.2, 0, -58.6),
	glm::vec3(1.2, 0, -58.6),
	glm::vec3(11.2, 0, -58.6),
	glm::vec3(21.2, 0, -58.6),
	glm::vec3(31.2, 0, -58.6),
	glm::vec3(47.2, 0, -58.6),
	glm::vec3(51.2, 0, -58.6),
	glm::vec3(61.2, 0, -58.6),
	glm::vec3(71.2, 0, -58.6),
	glm::vec3(81.2, 0, -58.6),
	glm::vec3(87.2, 0, -58.6),

	glm::vec3(13.2, 0, -51.6),
	glm::vec3(13.2, 0, -41.6),
	glm::vec3(13.2, 0, -34.6),

	glm::vec3(-30.2, 0, -51.6),
	glm::vec3(-30.2, 0, -41.6),
	glm::vec3(-30.2, 0, -34.6),

    glm::vec3(-24.2, 0, -34.6),
	glm::vec3(-18.2, 0, -34.6),

	glm::vec3(7.2, 0, -34.6),
	glm::vec3(1.2, 0, -34.6),

	glm::vec3(87.2, 0, -46.6),
	glm::vec3(87.2, 0, -36.6),

	glm::vec3(77.2, 0, -36.6),
	glm::vec3(67.2, 0, -36.6),
	glm::vec3(57.2, 0, -36.6),
	glm::vec3(47.2, 0, -36.6),
	
    glm::vec3(38.2, 0, -46.6),
	glm::vec3(38.2, 0, -56.6),
	glm::vec3(38.2, 0, -66.6),
	glm::vec3(38.2, 0, -76.6),
	glm::vec3(38.2, 0, -86.6),

	glm::vec3(28.2, 0, -86.6),
	glm::vec3(18.2, 0, -86.6),
	glm::vec3(11.2, 0, -86.6),

    glm::vec3(11.2, 0, -76.6),
	glm::vec3(11.2, 0, -66.6),

	glm::vec3(38.2, 0, -36.6),
	glm::vec3(38.2, 0, -26.6),
	glm::vec3(38.2, 0, -16.6),
	glm::vec3(38.2, 0, -6.6),
	glm::vec3(38.2, 0, 4.6),
	glm::vec3(38.2, 0, 14.6),


	glm::vec3(87.2, 0, -68.6),
	//glm::vec3(87.2, 0, -77.6), //PowerUp
	glm::vec3(87.2, 0, -86.6),

    glm::vec3(77.2, 0, -86.6),
	glm::vec3(67.2, 0, -86.6),
	glm::vec3(57.2, 0, -86.6),
	glm::vec3(47.2, 0, -86.6),
	
};

std::vector<glm::vec3> powerUpPosition = {
	glm::vec3(87.2, 0, -77.6),
	glm::vec3(-87.2, 0, -72.6),
	glm::vec3(87.2, 0, 39.6),
	glm::vec3(-87.2, 0, 32.6),
};

std::vector<bool> spheresCollisions;
std::vector<bool> powerUpCollisions;

double deltaTime;
double currTime, lastTime;


// Jump variables
bool isJump = false;
float GRAVITY = 1.81;
double tmv = 0;
double startTimeJump = 0;

// Colliders
std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> > collidersOBB;
std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> > collidersSBB;

// Variables animacion maquina de estados eclipse
const float avance = 0.45;
const float giroFantasma = 9.0f;
float rotWheelsX = 0.0;
float rotWheelsY = 0.0;

// OpenAL Defines
#define NUM_BUFFERS 5
#define NUM_SOURCES 5
#define NUM_ENVIRONMENTS 1
// Listener
ALfloat listenerPos[] = { 0.0, 0.0, 4.0 };
ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat listenerOri[] = { 0.0, 0.0, 1.0, 0.0, 1.0, 0.0 };
// Source 0
ALfloat source0Pos[] = { -2.0, 0.0, 0.0 };
ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
// Source 1
ALfloat source1Pos[] = { 2.0, 0.0, 0.0 };
ALfloat source1Vel[] = { 0.0, 0.0, 0.0 };
// Source 2
ALfloat source2Pos[] = { 2.0, 0.0, 0.0 };
ALfloat source2Vel[] = { 0.0, 0.0, 0.0 };
// Buffers
ALuint buffer[NUM_BUFFERS];
ALuint source[NUM_SOURCES];
ALuint environment[NUM_ENVIRONMENTS];
// Configs
ALsizei size, freq;
ALenum format;
ALvoid *data;
int ch;
ALboolean loop;
std::vector<bool> sourcesPlay = {false, false, false, false};

// Framesbuffers
GLuint depthMap, depthMapFBO;

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow *window, int key, int scancode, int action,
		int mode);
void mouseCallback(GLFWwindow *window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void initParticleBuffers();
void init(int width, int height, std::string strTitle, bool bFullScreen);
void destroy();
bool processInput(bool continueApplication = true);

// Implementacion de todas las funciones.
void init(int width, int height, std::string strTitle, bool bFullScreen) {

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}

	screenWidth = width;
	screenHeight = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (bFullScreen)
		window = glfwCreateWindow(width, height, strTitle.c_str(),
				glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr,
				nullptr);

	if (window == nullptr) {
		std::cerr
				<< "Error to create GLFW window, you can try download the last version of your video card that support OpenGL 3.3+"
				<< std::endl;
		destroy();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetWindowSizeCallback(window, reshapeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Init glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Inicialización de los shaders
	shader.initialize("../Shaders/colorShader.vs", "../Shaders/colorShader.fs");
	shaderSkybox.initialize("../Shaders/skyBox.vs", "../Shaders/skyBox_fog.fs");
	shaderMulLighting.initialize("../Shaders/iluminacion_textura_animation_shadow.vs", "../Shaders/multipleLights_shadow.fs");
	shaderTerrain.initialize("../Shaders/terrain_shadow.vs", "../Shaders/terrain_shadow.fs");
	shaderTexture.initialize("../Shaders/texturizado.vs", "../Shaders/texturizado.fs");
	shaderViewDepth.initialize("../Shaders/texturizado.vs", "../Shaders/texturizado_depth_view.fs");
	shaderDepth.initialize("../Shaders/shadow_mapping_depth.vs", "../Shaders/shadow_mapping_depth.fs");
	/*shaderParticlesFountain.initialize("../Shaders/particlesFountain.vs", "../Shaders/particlesFountain.fs");*/

	// Inicializacion de los objetos.
	skyboxSphere.init();
	skyboxSphere.setShader(&shaderSkybox);
	skyboxSphere.setScale(glm::vec3(20.0f, 20.0f, 20.0f));

	boxCollider.init();
	boxCollider.setShader(&shader);
	boxCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	sphereCollider.init();
	sphereCollider.setShader(&shader);
	sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	rayModel.init();
	rayModel.setShader(&shader);
	rayModel.setColor(glm::vec4(1.0));

	boxCesped.init();
	boxCesped.setShader(&shaderMulLighting);

	boxWalls.init();
	boxWalls.setShader(&shaderMulLighting);

	boxHighway.init();
	boxHighway.setShader(&shaderMulLighting);

	boxLandingPad.init();
	boxLandingPad.setShader(&shaderMulLighting);

	esfera1.init();
	esfera1.setShader(&shaderMulLighting);

	boxIntro.init();
	boxIntro.setShader(&shaderTexture);
	boxIntro.setScale(glm::vec3(2.0, 2.0, 1.0));

	boxViewDepth.init();
	boxViewDepth.setShader(&shaderViewDepth);

	//Pacman Ghosts
	modelGhostRed.loadModel("../models/ghosts/red/pacman_ghost_red.fbx");
	modelGhostRed.setShader(&shaderMulLighting);
	modelGhostBlue.loadModel("../models/ghosts/blue/pacman_ghost_blue.fbx");
	modelGhostBlue.setShader(&shaderMulLighting);
	modelGhostPink.loadModel("../models/ghosts/pink/pacman_ghost_pink.fbx");
	modelGhostPink.setShader(&shaderMulLighting);
	modelGhostOrange.loadModel("../models/ghosts/orange/pacman_ghost_orange.fbx");
	modelGhostOrange.setShader(&shaderMulLighting);
	modelGhostScared.loadModel("../models/ghosts/scared/pacman_scared_ghost.fbx");
	modelGhostScared.setShader(&shaderMulLighting);

	modelWall.loadModel("../models/wall/fall.fbx");
	modelWall.setShader(&shaderMulLighting);
	modelLargeWall.loadModel("../models/box/box.fbx");
	modelLargeWall.setShader(&shaderMulLighting);

	// Mayow
	mayowModelAnimate.loadModel("../models/Pacman/HappyWalk3.fbx");
	mayowModelAnimate.setShader(&shaderMulLighting);

	modelSphere.loadModel("../models/sphere/sphere.fbx");
	modelSphere.setShader(&shaderMulLighting);

	// Terreno
	terrain.init();
	terrain.setShader(&shaderTerrain);

	// Se inicializa el model de render text
	modelText = new FontTypeRendering::FontTypeRendering(screenWidth, screenHeight);
	modelText->Initialize();

	camera->setPosition(glm::vec3(0.0, 3.0, 4.0));
	camera->setDistanceFromTarget(distanceFromTarget);
	camera->setSensitivity(1.0);
	
	// Carga de texturas para el skybox
	Texture skyboxTexture = Texture("");
	glGenTextures(1, &skyboxTextureID);
	// Tipo de textura CUBE MAP
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(types); i++) {
		skyboxTexture = Texture(fileNames[i]);
		skyboxTexture.loadImage(true);
		if (skyboxTexture.getData()) {
			glTexImage2D(types[i], 0, skyboxTexture.getChannels() == 3 ? GL_RGB : GL_RGBA, skyboxTexture.getWidth(), skyboxTexture.getHeight(), 0,
			skyboxTexture.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, skyboxTexture.getData());
		} else
			std::cout << "Failed to load texture" << std::endl;
		skyboxTexture.freeImage();
	}

	// Definiendo la textura a utilizar
	Texture textureCesped("../Textures/blackground.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	textureCesped.loadImage();
	// Creando la textura con id 1
	glGenTextures(1, &textureCespedID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureCespedID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (textureCesped.getData()) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		std::cout << "Numero de canales :=> " << textureCesped.getChannels() << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, textureCesped.getChannels() == 3 ? GL_RGB : GL_RGBA, textureCesped.getWidth(), textureCesped.getHeight(), 0,
		textureCesped.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureCesped.getData());
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureCesped.freeImage();

	// Defininiendo texturas del mapa de mezclas
	// Definiendo la textura
	Texture textureR("../Textures/path_pacman.png");
	textureR.loadImage(); // Cargar la textura
	glGenTextures(1, &textureTerrainRID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainRID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureR.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureR.getChannels() == 3 ? GL_RGB : GL_RGBA, textureR.getWidth(), textureR.getHeight(), 0,
		textureR.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureR.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureR.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureG("../Textures/powerUpPacmanGround.png");
	textureG.loadImage(); // Cargar la textura
	glGenTextures(1, &textureTerrainGID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainGID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureG.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureG.getChannels() == 3 ? GL_RGB : GL_RGBA, textureG.getWidth(), textureG.getHeight(), 0,
		textureG.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureG.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureG.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureB("../Textures/blackground.png");
	textureB.loadImage(); // Cargar la textura
	glGenTextures(1, &textureTerrainBID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainBID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureB.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureB.getChannels() == 3 ? GL_RGB : GL_RGBA, textureB.getWidth(), textureB.getHeight(), 0,
		textureB.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureB.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureB.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureBlendMap("../Textures/blendMapPacman.png");
	textureBlendMap.loadImage(); // Cargar la textura
	glGenTextures(1, &textureTerrainBlendMapID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainBlendMapID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureBlendMap.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureBlendMap.getChannels() == 3 ? GL_RGB : GL_RGBA, textureBlendMap.getWidth(), textureBlendMap.getHeight(), 0,
		textureBlendMap.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureBlendMap.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureBlendMap.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureIntro1("../Textures/IntroPacmanStart.png");
	textureIntro1.loadImage(); // Cargar la textura
	glGenTextures(1, &textureInit1ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureInit1ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureIntro1.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureIntro1.getChannels() == 3 ? GL_RGB : GL_RGBA, textureIntro1.getWidth(), textureIntro1.getHeight(), 0,
		textureIntro1.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureIntro1.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureIntro1.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureIntro2("../Textures/IntroPacmanExit.png");
	textureIntro2.loadImage(); // Cargar la textura
	glGenTextures(1, &textureInit2ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureInit2ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureIntro2.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureIntro2.getChannels() == 3 ? GL_RGB : GL_RGBA, textureIntro2.getWidth(), textureIntro2.getHeight(), 0,
		textureIntro2.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureIntro2.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureIntro2.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureScreen("../Textures/Screen3HP.png");
	textureScreen.loadImage(); // Cargar la textura
	glGenTextures(1, &textureScreenID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureScreenID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureScreen.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureScreen.getChannels() == 3 ? GL_RGB : GL_RGBA, textureScreen.getWidth(), textureScreen.getHeight(), 0,
		textureScreen.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureScreen.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureScreen.freeImage(); // Liberamos memoria

	Texture textureScreen2("../Textures/Screen2HP.png");
	textureScreen2.loadImage(); // Cargar la textura
	glGenTextures(1, &textureScreenID2); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureScreenID2); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureScreen2.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureScreen2.getChannels() == 3 ? GL_RGB : GL_RGBA, textureScreen2.getWidth(), textureScreen2.getHeight(), 0,
		textureScreen2.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureScreen2.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureScreen2.freeImage();

	Texture textureScreen3("../Textures/Screen1HP.png");
	textureScreen3.loadImage(); // Cargar la textura
	glGenTextures(1, &textureScreenID3); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureScreenID3); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureScreen3.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureScreen3.getChannels() == 3 ? GL_RGB : GL_RGBA, textureScreen3.getWidth(), textureScreen3.getHeight(), 0,
		textureScreen3.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureScreen3.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureScreen3.freeImage();  

    Texture textureGameOver("../Textures/gameOver.png");
	textureGameOver.loadImage(); // Cargar la textura
	glGenTextures(1, &textureGameOverID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureGameOverID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureGameOver.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureGameOver.getChannels() == 3 ? GL_RGB : GL_RGBA, textureGameOver.getWidth(), textureGameOver.getHeight(), 0,
		textureGameOver.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureGameOver.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureGameOver.freeImage();

	Texture textureVictory("../Textures/victory.png");
	textureVictory.loadImage(); // Cargar la textura
	glGenTextures(1, &textureVictoryID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureVictoryID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureVictory.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureVictory.getChannels() == 3 ? GL_RGB : GL_RGBA, textureVictory.getWidth(), textureVictory.getHeight(), 0,
		textureVictory.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureVictory.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureVictory.freeImage();  


	/*******************************************
	 * OpenAL init
	 *******************************************/
	alutInit(0, nullptr);
	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
	alGetError(); // clear any error messages
	if (alGetError() != AL_NO_ERROR) {
		printf("- Error creating buffers !!\n");
		exit(1);
	}
	else {
		printf("init() - No errors yet.");
	}
	// Generate buffers, or else no sound will happen!
	alGenBuffers(NUM_BUFFERS, buffer);
	buffer[0] = alutCreateBufferFromFile("../sounds/pacman_beginning.wav");
	buffer[1] = alutCreateBufferFromFile("../sounds/pacman_chomp.wav");
	buffer[2] = alutCreateBufferFromFile("../sounds/pacman_death.wav");
	buffer[3] = alutCreateBufferFromFile("../sounds/pacman_eatghost.wav");
	buffer[4] = alutCreateBufferFromFile("../sounds/pacman_intermission.wav");
	int errorAlut = alutGetError();
	if (errorAlut != ALUT_ERROR_NO_ERROR){
		printf("- Error open files with alut texto en openGL %d !!\n", errorAlut);
		exit(2);
	}

	alGetError(); /* clear error */
	alGenSources(NUM_SOURCES, source);

	if (alGetError() != AL_NO_ERROR) {
		printf("- Error creating sources !!\n");
		exit(2);
	}
	else {
		printf("init - no errors after alGenSources\n");
	}
	alSourcef(source[0], AL_GAIN, 3.0f);
	alSourcefv(source[0], AL_POSITION, source1Pos);
	alSourcefv(source[0], AL_VELOCITY, source1Vel);
	alSourcei(source[0], AL_BUFFER, buffer[0]);
	alSourcei(source[0], AL_LOOPING, AL_FALSE);
	alSourcef(source[0], AL_MAX_DISTANCE, 0.0);
	//alSourcef(source[0], AL_ROLLOFF_FACTOR, 0.0f);


	alSourcef(source[1], AL_PITCH, 1.0f);
	alSourcef(source[1], AL_GAIN, 0.5f);
	alSourcefv(source[1], AL_POSITION, source1Pos);
	alSourcefv(source[1], AL_VELOCITY, source1Vel);
	alSourcei(source[1], AL_BUFFER, buffer[1]);
	alSourcei(source[1], AL_LOOPING, AL_TRUE);
	alSourcef(source[1], AL_MAX_DISTANCE, 0.0);

	alSourcef(source[2], AL_PITCH, 1.0f);
	alSourcef(source[2], AL_GAIN, 2.5f);
	alSourcefv(source[2], AL_POSITION, source1Pos);
	alSourcefv(source[2], AL_VELOCITY, source1Vel);
	alSourcei(source[2], AL_BUFFER, buffer[2]);
	alSourcei(source[2], AL_LOOPING, AL_FALSE);
	alSourcef(source[2], AL_MAX_DISTANCE, 0.0);

	alSourcef(source[3], AL_PITCH, 1.0f);
	alSourcef(source[3], AL_GAIN, 20.0f);
	alSourcefv(source[3], AL_POSITION, source1Pos);
	alSourcefv(source[3], AL_VELOCITY, source1Vel);
	alSourcei(source[3], AL_BUFFER, buffer[3]);
	alSourcei(source[3], AL_LOOPING, AL_FALSE);
	alSourcef(source[3], AL_MAX_DISTANCE, 0.0);

	alSourcef(source[4], AL_PITCH, 1.0f);
	alSourcef(source[4], AL_GAIN, 2.5f);
	alSourcefv(source[4], AL_POSITION, source1Pos);
	alSourcefv(source[4], AL_VELOCITY, source1Vel);
	alSourcei(source[4], AL_BUFFER, buffer[4]);
	alSourcei(source[4], AL_LOOPING, AL_FALSE);
	alSourcef(source[4], AL_MAX_DISTANCE, 0.0);

    alSourceQueueBuffers(source[0], 1, &buffer[0]);
    
	/*******************************************
	 * Inicializacion del framebuffer para
	 * almacenar el buffer de profunidadad
	 *******************************************/
	glGenFramebuffers(1, &depthMapFBO);
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
				 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
	// --------- IMPORTANTE ----------
	// Eliminar los shader y buffers creados.

	// Shaders Delete
	shader.destroy();
	shaderMulLighting.destroy();
	shaderSkybox.destroy();
	shaderTerrain.destroy();
	/*shaderParticlesFountain.destroy();*/

	// Basic objects Delete
	skyboxSphere.destroy();
	boxCesped.destroy();
	boxWalls.destroy();
	boxHighway.destroy();
	boxLandingPad.destroy();
	esfera1.destroy();
	boxCollider.destroy();
	sphereCollider.destroy();
	rayModel.destroy();
	boxIntro.destroy();
	boxViewDepth.destroy();

	// Custom objects Delete
	mayowModelAnimate.destroy();
	modelGhostRed.destroy();
	modelGhostBlue.destroy();
	modelGhostOrange.destroy();
	modelGhostPink.destroy();
	modelWall.destroy();
	modelSphere.destroy();

	// Terrains objects Delete
	terrain.destroy();

	// Textures Delete
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &textureCespedID);
	glDeleteTextures(1, &textureWallID);
	glDeleteTextures(1, &textureWindowID);
	glDeleteTextures(1, &textureHighwayID);
	glDeleteTextures(1, &textureLandingPadID);
	glDeleteTextures(1, &textureTerrainBID);
	glDeleteTextures(1, &textureTerrainGID);
	glDeleteTextures(1, &textureTerrainRID);
	glDeleteTextures(1, &textureTerrainBlendMapID);
	glDeleteTextures(1, &textureInit1ID);
	glDeleteTextures(1, &textureInit2ID);
	glDeleteTextures(1, &textureScreenID);
	glDeleteTextures(1, &textureParticleFountainID);

	// Cube Maps Delete
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDeleteTextures(1, &skyboxTextureID);
}

void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
		int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			exitApp = true;
			break;
		}
	}
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
	offsetX = xpos - lastMousePosX;
	offsetY = ypos - lastMousePosY;
	lastMousePosX = xpos;
	lastMousePosY = ypos;
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
	distanceFromTarget -= yoffset;
	camera->setDistanceFromTarget(distanceFromTarget);
}

void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod) {
	if (state == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_RIGHT:
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_LEFT:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		}
	}
}

bool processInput(bool continueApplication) {
	if (exitApp || glfwWindowShouldClose(window) != 0) {
		return false;
	}

	if(!iniciaPartida){
		bool presionarEnter = glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS;
		if(textureActivaID == textureInit1ID && presionarEnter){
			iniciaPartida = true;
			//alSourcePlay(source[0]);
			textureActivaID = textureScreenID;
			alSourcePlay(source[0]);
			spheres_to_win = spherePosition.size() + powerUpPosition.size();
			//spheres_to_win = 1;
			ALint source0State;
			do {
    	    			alGetSourcei(source[0], AL_SOURCE_STATE, &source0State);
				} while (source0State == AL_PLAYING);
			 //Adjuntar el segundo buffer al source[0]
			alSourceQueueBuffers(source[0], 1, &buffer[1]);
			alSourcePlay(source[1]);
		}
		else if(!presionarOpcion && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
			presionarOpcion = true;
			if(textureActivaID == textureInit1ID)
				textureActivaID = textureInit2ID;
			else if(textureActivaID == textureInit2ID)
				textureActivaID = textureInit1ID;
		}
		else if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
			presionarOpcion = false;
		if(textureActivaID == textureInit2ID && presionarEnter)
		{
			exitApp = true;
		}
	}

    bool presionarEnter = glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS;
	if(textureActivaID == textureGameOverID && presionarEnter)
		exitApp = true;
    if(textureActivaID == textureVictoryID && presionarEnter)
		{
			exitApp = true;
		}

	if (glfwJoystickPresent(GLFW_JOYSTICK_1) == GL_TRUE) {
		std::cout << "Esta presente el joystick" << std::endl;
		int axesCount, buttonCount;
		const float * axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
		std::cout << "Número de ejes disponibles :=>" << axesCount << std::endl;
		std::cout << "Left Stick X axis: " << axes[0] << std::endl;
		std::cout << "Left Stick Y axis: " << axes[1] << std::endl;
		std::cout << "Left Trigger/L2: " << axes[2] << std::endl;
		std::cout << "Right Stick X axis: " << axes[3] << std::endl;
		std::cout << "Right Stick Y axis: " << axes[4] << std::endl;
		std::cout << "Right Trigger/R2: " << axes[5] << std::endl;

		if(fabs(axes[1]) > 0.2){
			modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(0, 0, -axes[1] * 0.1));
			animationMayowIndex = 2;
		}if(fabs(axes[0]) > 0.2){
			modelMatrixMayow = glm::rotate(modelMatrixMayow, glm::radians(-axes[0] * 0.5f), glm::vec3(0, 1, 0));
			animationMayowIndex = 2;
		}

		if(fabs(axes[3]) > 0.2){
			camera->mouseMoveCamera(axes[3], 0.0, deltaTime);
		}if(fabs(axes[4]) > 0.2){
			camera->mouseMoveCamera(0.0, axes[4], deltaTime);
		}

		const unsigned char * buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
		std::cout << "Número de botones disponibles :=>" << buttonCount << std::endl;
		if(buttons[0] == GLFW_PRESS)
			std::cout << "Se presiona x" << std::endl;

		if(!isJump && buttons[0] == GLFW_PRESS){
			isJump = true;
			startTimeJump = currTime;
			tmv = 0;
		}
	}

	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		camera->mouseMoveCamera(offsetX, 0.0, deltaTime);
	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		camera->mouseMoveCamera(0.0, offsetY, deltaTime);

	offsetX = 0;
	offsetY = 0;

	// Controles de mayow
	if(vidas > 0)
	{
		if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
			modelMatrixMayow = glm::rotate(modelMatrixMayow, 0.06f, glm::vec3(0, 1, 0));
			animationMayowIndex = 2;
		} else if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
			modelMatrixMayow = glm::rotate(modelMatrixMayow, -0.06f, glm::vec3(0, 1, 0));
			animationMayowIndex = 2;
		}
		if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
			modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(0.0, 0.0, 0.6));
			animationMayowIndex = 2;
		}
		else if (modelSelected == 0 && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
			modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(0.0, 0.0, -0.6));
			animationMayowIndex = 2;
		}

		if(setPowerUpTime){
			auto inicio = std:: chrono::high_resolution_clock::now;
			auto tiempo_actual = inicio;
			std::chrono::duration<double> duracion_maxima(3.0);
			setPowerUpTime = false;
			std::cout << "power up time" << powerUpEndTime << std::endl;
		}

		if(reset_blinky){
			modelMatrixGhostRed = glm::mat4(1.0);
			modelMatrixGhostRed = glm::translate(modelMatrixGhostRed, glm::vec3(13.6, 2.2, -12.8));
			modelMatrixGhostRed = glm::scale(modelMatrixGhostRed, glm::vec3(1.4, 1.4, 1.4));
			modelMatrixGhostRed = glm::rotate(modelMatrixGhostRed, glm::radians(-90.0f), glm::vec3(1, 0, 0));
			modelMatrixGhostRed = glm::rotate(modelMatrixGhostRed, glm::radians(90.0f), glm::vec3(0, 0, 1));
			state = 0;
			numberAdvance = 0;
			advanceCount = 0;
			rotCount = 0;
			alSourcePlay(source[3]);
			reset_blinky = false;

		}	

		if(reset_pinky){
			modelMatrixGhostPink = glm::mat4(1.0);
			modelMatrixGhostPink = glm::translate(modelMatrixGhostPink, glm::vec3(-13.6, 2.2, -12.8));
			modelMatrixGhostPink = glm::scale(modelMatrixGhostPink, glm::vec3(1.4, 1.4, 1.4));
			modelMatrixGhostPink = glm::rotate(modelMatrixGhostPink, glm::radians(-90.0f), glm::vec3(1, 0, 0));
			modelMatrixGhostPink = glm::rotate(modelMatrixGhostPink, glm::radians(90.0f), glm::vec3(0, 0, -1));
			Pinky = 0;
			advanceCountP = 0;
			numberAdvanceP = 0;
			rotCountP = 0;
			alSourcePlay(source[3]);
			reset_pinky = false;
		}	

		if(reset_inky){
			modelMatrixGhostBlue = glm::mat4(1.0);
			modelMatrixGhostBlue = glm::translate(modelMatrixGhostBlue, glm::vec3(13.6, 2.2, -6.4));
			modelMatrixGhostBlue = glm::scale(modelMatrixGhostBlue, glm::vec3(1.4, 1.4, 1.4));
			modelMatrixGhostBlue = glm::rotate(modelMatrixGhostBlue, glm::radians(-90.0f), glm::vec3(1, 0, 0));
			modelMatrixGhostBlue = glm::rotate(modelMatrixGhostBlue, glm::radians(90.0f), glm::vec3(0, 0, 1));
			Inky = 0;
			advanceCountI = 0;
			numberAdvanceI = 0;
			rotCountI = 0;
			alSourcePlay(source[3]);
			reset_inky = false;
		}	

		if(reset_clyde){
			modelMatrixGhostOrange = glm::mat4(1.0);
			modelMatrixGhostOrange = glm::translate(modelMatrixGhostOrange, glm::vec3(-13.6, 2.2, -6.4));
			modelMatrixGhostOrange = glm::scale(modelMatrixGhostOrange, glm::vec3(1.4, 1.4, 1.4));
			modelMatrixGhostOrange = glm::rotate(modelMatrixGhostOrange, glm::radians(-90.0f), glm::vec3(1, 0, 0));
			modelMatrixGhostOrange = glm::rotate(modelMatrixGhostOrange, glm::radians(90.0f), glm::vec3(0, 0, -1));
			Clyde = 0;
			advanceCountC = 0;
			numberAdvanceC = 0;
			rotCountC = 0;
			alSourcePlay(source[3]);
			reset_clyde = false;
		}	

		if(spheres_to_win == 0 && !gameFinished)
		{
			modelMatrixMayow = glm::mat4(1.0);
			modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(0.0f, 0.05f, 5.0f));
			modelMatrixMayow = glm::rotate(modelMatrixMayow, glm::radians(-90.0f), glm::vec3(0, 1, 0));
			textureActivaID = textureVictoryID;
			alSourcePause(source[1]);
			alSourcePlay(source[4]);
			gameFinished = true;
		}

		if(reset_player){
			modelMatrixMayow = glm::mat4(1.0);
			modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(0.0f, 0.05f, 5.0f));
			modelMatrixMayow = glm::rotate(modelMatrixMayow, glm::radians(-90.0f), glm::vec3(0, 1, 0));
			vidas--;
			reset_player = false;
			switch(vidas){
				ALint source0State;
				case 3: textureActivaID = textureScreenID;
				        alSourcePause(source[1]);
				        alSourcePlay(source[2]);
						do {
    						alGetSourcei(source[2], AL_SOURCE_STATE, &source0State);
						} while (source0State == AL_PLAYING);
						// Adjuntar el segundo buffer al source[0]
						alSourceQueueBuffers(source[0], 1, &buffer[1]);
						alSourcePlay(source[1]);
						break;
				case 2: textureActivaID = textureScreenID2;
				        alSourcePause(source[1]);
				        alSourcePlay(source[2]);
						do {
    						alGetSourcei(source[2], AL_SOURCE_STATE, &source0State);
						} while (source0State == AL_PLAYING);
						// Adjuntar el segundo buffer al source[0]
						alSourceQueueBuffers(source[0], 1, &buffer[1]);
						alSourcePlay(source[1]);
						break;
				case 1: textureActivaID = textureScreenID3;
						alSourcePause(source[1]);
				        alSourcePlay(source[2]);
						do {
    						alGetSourcei(source[2], AL_SOURCE_STATE, &source0State);
						} while (source0State == AL_PLAYING);
						// Adjuntar el segundo buffer al source[0]
						alSourceQueueBuffers(source[0], 1, &buffer[1]);
						alSourcePlay(source[1]);
						break;
				case 0: 
				        textureActivaID = textureGameOverID;
						alSourcePause(source[1]);
						break;
				}
			std::cout << "menos una vida :(" << std::endl;
	}

	//std::cout << "time left " << currTime - powerUpEndTime << std::endl;

	/*if(currTime - powerUpEndTime > 3 && powerUp){
		powerUp = false;
		std::cout << "endTime " << powerUpEndTime << std::endl;
		std::cout << "desactivando power up " << std::endl;
	}*/
	}

	glfwPollEvents();
	return continueApplication;
}

void prepareScene(){

	terrain.setShader(&shaderTerrain);
	
	//Pacman Ghosts
	modelGhostRed.setShader(&shaderMulLighting);
	modelGhostPink.setShader(&shaderMulLighting);
	modelGhostBlue.setShader(&shaderMulLighting);
	modelGhostOrange.setShader(&shaderMulLighting);
	//Mayow
	mayowModelAnimate.setShader(&shaderMulLighting);
	modelSphere.setShader(&shaderMulLighting);


}

void prepareDepthScene(){

	terrain.setShader(&shaderDepth);

	//Mayow
	mayowModelAnimate.setShader(&shaderDepth);
	modelGhostRed.setShader(&shaderDepth);
	modelGhostPink.setShader(&shaderDepth);
	modelGhostBlue.setShader(&shaderDepth);
	modelGhostOrange.setShader(&shaderDepth);
	modelSphere.setShader(&shaderDepth);

}

void renderSolidScene(){
	/*******************************************
	 * Terrain Cesped
	 *******************************************/
	// Se activa la textura del agua
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureCespedID);
	shaderTerrain.setInt("backgroundTexture", 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureTerrainRID);
	shaderTerrain.setInt("rTexture", 1);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textureTerrainGID);
	shaderTerrain.setInt("gTexture", 2);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, textureTerrainBID);
	shaderTerrain.setInt("bTexture", 3);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, textureTerrainBlendMapID);
	shaderTerrain.setInt("blendMapTexture", 4);
	shaderTerrain.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(80, 80)));
	terrain.setPosition(glm::vec3(100, 0, 100));
	terrain.render();
	shaderTerrain.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(0, 0)));
	glBindTexture(GL_TEXTURE_2D, 0);

	/*******************************************
	 * Custom objects obj
	 *******************************************/

	/*****************************************
	 * Objetos animados por huesos
	 * **************************************/
	glm::vec3 ejey = glm::normalize(terrain.getNormalTerrain(modelMatrixMayow[3][0], modelMatrixMayow[3][2]));
	glm::vec3 ejex = glm::vec3(modelMatrixMayow[0]);
	glm::vec3 ejez = glm::normalize(glm::cross(ejex, ejey));
	ejex = glm::normalize(glm::cross(ejey, ejez));
	modelMatrixMayow[0] = glm::vec4(ejex, 0.0);
	modelMatrixMayow[1] = glm::vec4(ejey, 0.0);
	modelMatrixMayow[2] = glm::vec4(ejez, 0.0);
	modelMatrixMayow[3][1] = -GRAVITY * tmv * tmv + 3.5 * tmv + terrain.getHeightTerrain(modelMatrixMayow[3][0], modelMatrixMayow[3][2]);
	tmv = currTime - startTimeJump;
	if(modelMatrixMayow[3][1] < terrain.getHeightTerrain(modelMatrixMayow[3][0], modelMatrixMayow[3][2])){
		isJump = false;
		modelMatrixMayow[3][1] = terrain.getHeightTerrain(modelMatrixMayow[3][0], modelMatrixMayow[3][2]);
	}
	glm::mat4 modelMatrixMayowBody = glm::mat4(modelMatrixMayow);
	modelMatrixMayowBody = glm::scale(modelMatrixMayowBody, glm::vec3(0.005f));
	mayowModelAnimate.setAnimationIndex(animationMayowIndex);
	mayowModelAnimate.render(modelMatrixMayowBody);

	modelLargeWall.render(modelMatrixWall1);
	modelLargeWall.render(modelMatrixWall2);
	modelLargeWall.render(modelMatrixWall3);
	modelLargeWall.render(modelMatrixWall4);
	modelLargeWall.render(modelMatrixWall5);
	modelLargeWall.render(modelMatrixWall6);
	modelLargeWall.render(modelMatrixWall7);
	modelLargeWall.render(modelMatrixWall8);
	modelLargeWall.render(modelMatrixWall9);
	modelLargeWall.render(modelMatrixWall10);
	modelLargeWall.render(modelMatrixWall11);
	modelLargeWall.render(modelMatrixWall12);
	modelLargeWall.render(modelMatrixWall13);
	modelLargeWall.render(modelMatrixWall14);
	modelLargeWall.render(modelMatrixWall15);
	modelLargeWall.render(modelMatrixWall16);
	modelLargeWall.render(modelMatrixWall17);
	modelLargeWall.render(modelMatrixWall18);
	modelLargeWall.render(modelMatrixWall19);
	modelLargeWall.render(modelMatrixWall20);
	modelLargeWall.render(modelMatrixWall21);
	modelLargeWall.render(modelMatrixWall22);
	modelLargeWall.render(modelMatrixWall23);
	modelLargeWall.render(modelMatrixWall24);
	modelLargeWall.render(modelMatrixWall25);
	modelLargeWall.render(modelMatrixWall26);
	modelLargeWall.render(modelMatrixWall27);
	modelLargeWall.render(modelMatrixWall28);
	modelLargeWall.render(modelMatrixWall29);
	modelLargeWall.render(modelMatrixWall30);
	modelLargeWall.render(modelMatrixWall31);
	modelLargeWall.render(modelMatrixWall32);
	modelLargeWall.render(modelMatrixWall33);
	modelLargeWall.render(modelMatrixWall34);
	modelLargeWall.render(modelMatrixWall35);
	modelLargeWall.render(modelMatrixWall36);
	modelLargeWall.render(modelMatrixWall37);
	modelLargeWall.render(modelMatrixWall38);
	modelLargeWall.render(modelMatrixWall39);
	modelLargeWall.render(modelMatrixWall40);
	modelLargeWall.render(modelMatrixWall41);

	for(int i = 0; i < spherePosition.size(); i++){
		if(spheresCollisions[i] == false)
		{
			spherePosition[i].y = terrain.getHeightTerrain(spherePosition[i].x, spherePosition[i].z) + 1.0f;
			modelSphere.setPosition(spherePosition[i]);
			modelSphere.setScale(glm::vec3(0.75));
			//modelSphere.setOrientation(glm::vec3(0, lamp1Orientation[i], 0));
			modelSphere.render();
		}
	}

	for(int i = 0; i < powerUpPosition.size(); i++){
		if(powerUpCollisions[i] == false)
		{
			powerUpPosition[i].y = terrain.getHeightTerrain(powerUpPosition[i].x, powerUpPosition[i].z) + 1.0f;
			modelSphere.setPosition(powerUpPosition[i]);
			modelSphere.setScale(glm::vec3(1.25));
			//modelSphere.setOrientation(glm::vec3(0, lamp1Orientation[i], 0));
			modelSphere.render();
		}
	}
	
	//glm::mat4 modelMatrixGhostRed = glm::mat4(modelMatrixGhostRed);
	modelGhostRed.setAnimationIndex(0);

	levitating_controller += 0.1f;
	
	//printf("levitating controller: %f", levitating_controller);
	modelMatrixGhostRed = glm::translate(modelMatrixGhostRed, glm::vec3(0.0, 0.0, sin(levitating_controller)/200));
	modelMatrixGhostPink = glm::translate(modelMatrixGhostPink, glm::vec3(0.0, 0.0, sin(levitating_controller)/200));
	modelMatrixGhostBlue = glm::translate(modelMatrixGhostBlue, glm::vec3(0.0, 0.0, sin(levitating_controller)/200));
	modelMatrixGhostOrange = glm::translate(modelMatrixGhostOrange, glm::vec3(0.0, 0.0, sin(levitating_controller)/200));

	if(!powerUp){
	modelGhostRed.render(modelMatrixGhostRed);
	modelGhostPink.render(modelMatrixGhostPink);
	modelGhostBlue.render(modelMatrixGhostBlue);
	modelGhostOrange.render(modelMatrixGhostOrange);
	}
	else{
	modelGhostScared.render(modelMatrixGhostRed);
	modelGhostScared.render(modelMatrixGhostPink);
	modelGhostScared.render(modelMatrixGhostBlue);
	modelGhostScared.render(modelMatrixGhostOrange);
	}

	/*******************************************
	 * Skybox
	 *******************************************/
	GLint oldCullFaceMode;
	GLint oldDepthFuncMode;
	// deshabilita el modo del recorte de caras ocultas para ver las esfera desde adentro
	glGetIntegerv(GL_CULL_FACE_MODE, &oldCullFaceMode);
	glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFuncMode);
	shaderSkybox.setFloat("skybox", 0);
	glCullFace(GL_FRONT);
	glDepthFunc(GL_LEQUAL);
	glActiveTexture(GL_TEXTURE0);
	skyboxSphere.render();
	glCullFace(oldCullFaceMode);
	glDepthFunc(oldDepthFuncMode);
}

void renderAlphaScene(bool render = true){
	/**********
	 * Update the position with alpha objects
	/**********
	 * Sorter with alpha objects
	 */
	std::map<float, std::pair<std::string, glm::vec3>> blendingSorted;
	std::map<std::string, glm::vec3>::iterator itblend;
	for(itblend = blendingUnsorted.begin(); itblend != blendingUnsorted.end(); itblend++){
		float distanceFromView = glm::length(camera->getPosition() - itblend->second);
		blendingSorted[distanceFromView] = std::make_pair(itblend->first, itblend->second);
	}

	/**********
	 * Render de las transparencias
	 */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	for(std::map<float, std::pair<std::string, glm::vec3> >::reverse_iterator it = blendingSorted.rbegin(); it != blendingSorted.rend(); it++){
	}
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	if(render){
		/************Render de imagen de frente**************/
		shaderTexture.setMatrix4("projection", 1, false, glm::value_ptr(glm::mat4(1.0)));
		shaderTexture.setMatrix4("view", 1, false, glm::value_ptr(glm::mat4(1.0)));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureActivaID);
		shaderTexture.setInt("outTexture", 0);
		glEnable(GL_BLEND);
		boxIntro.render();
		glDisable(GL_BLEND);
		char bufferScore[50];
		std::sprintf(bufferScore, "%d", score);
		std::string scoreString = bufferScore;
		modelText->render(scoreString, -0.7, 0.95);
	}
}

void renderScene(){
	renderSolidScene();
	renderAlphaScene(false);
}

void applicationLoop() {
	bool psi = true;

	glm::vec3 axis;
	glm::vec3 target;
	float angleTarget;

	for (int i = 0; i < spherePosition.size(); i++) {
    		spheresCollisions.push_back(false);
		}

	for (int i = 0; i < powerUpPosition.size(); i++) {
    		powerUpCollisions.push_back(false);
		}

	modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(0.0f, 0.05f, 10.0f));
	modelMatrixMayow = glm::rotate(modelMatrixMayow, glm::radians(-90.0f), glm::vec3(0, 1, 0));

	modelMatrixWall1 = glm::rotate(modelMatrixWall1, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall1 = glm::scale(modelMatrixWall1, glm::vec3(1, 1, 2));
	modelMatrixWall1 = glm::translate(modelMatrixWall1, glm::vec3(-36.8, 74.2, 2.1));
	modelMatrixWall1 = glm::scale(modelMatrixWall1, glm::vec3(16, 12, 1));
	
	modelMatrixWall2 = glm::rotate(modelMatrixWall2, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall2 = glm::scale(modelMatrixWall2, glm::vec3(1, 1, 2));
	modelMatrixWall2 = glm::translate(modelMatrixWall2, glm::vec3(-70.5, 74.2, 2.1));
	modelMatrixWall2 = glm::scale(modelMatrixWall2, glm::vec3(13, 12, 1));

	modelMatrixWall3 = glm::rotate(modelMatrixWall3, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall3 = glm::scale(modelMatrixWall3, glm::vec3(1, 1, 2));
	modelMatrixWall3 = glm::translate(modelMatrixWall3, glm::vec3(-70.5, 45.2, 2.1));
	modelMatrixWall3 = glm::scale(modelMatrixWall3, glm::vec3(13, 12, 1));

	modelMatrixWall4 = glm::rotate(modelMatrixWall4, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall4 = glm::scale(modelMatrixWall4, glm::vec3(1, 1, 2));
	modelMatrixWall4 = glm::translate(modelMatrixWall4, glm::vec3(23.4, 73.4, 2.1));
	modelMatrixWall4 = glm::scale(modelMatrixWall4, glm::vec3(10, 11, 1));

	modelMatrixWall5 = glm::rotate(modelMatrixWall5, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall5 = glm::scale(modelMatrixWall5, glm::vec3(1, 1, 2));
	modelMatrixWall5 = glm::translate(modelMatrixWall5, glm::vec3(63.2, 73.4, 2.1));
	modelMatrixWall5 = glm::scale(modelMatrixWall5, glm::vec3(21, 11, 1));

	modelMatrixWall6 = glm::rotate(modelMatrixWall6, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall6 = glm::scale(modelMatrixWall6, glm::vec3(1, 1, 2));
	modelMatrixWall6 = glm::translate(modelMatrixWall6, glm::vec3(63.2, 47.8, 2.1));
	modelMatrixWall6 = glm::scale(modelMatrixWall6, glm::vec3(21, 8, 1));

	modelMatrixWall7 = glm::rotate(modelMatrixWall7, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall7 = glm::scale(modelMatrixWall7, glm::vec3(1, 1, 2));
	modelMatrixWall7 = glm::translate(modelMatrixWall7, glm::vec3(63.2, 13.4, 2.1));
	modelMatrixWall7 = glm::scale(modelMatrixWall7, glm::vec3(21, 19, 1));

	modelMatrixWall8 = glm::rotate(modelMatrixWall8, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall8 = glm::scale(modelMatrixWall8, glm::vec3(1, 1, 2));
	modelMatrixWall8 = glm::translate(modelMatrixWall8, glm::vec3(63.2, -24.2, 2.1));
	modelMatrixWall8 = glm::scale(modelMatrixWall8, glm::vec3(21, 13, 1));

	modelMatrixWall9 = glm::rotate(modelMatrixWall9, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall9 = glm::scale(modelMatrixWall9, glm::vec3(1, 1, 2));
	modelMatrixWall9 = glm::translate(modelMatrixWall9, glm::vec3(23, -20.2, 2.1));
	modelMatrixWall9 = glm::scale(modelMatrixWall9, glm::vec3(10, 8, 1));

	modelMatrixWall10 = glm::rotate(modelMatrixWall10, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall10 = glm::scale(modelMatrixWall10, glm::vec3(1, 1, 2));
	modelMatrixWall10 = glm::translate(modelMatrixWall10, glm::vec3(-32.6, -20.2, 2.1));
	modelMatrixWall10 = glm::scale(modelMatrixWall10, glm::vec3(18, 8, 1));

	modelMatrixWall11 = glm::rotate(modelMatrixWall11, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall11 = glm::scale(modelMatrixWall11, glm::vec3(1, 1, 2));
	modelMatrixWall11 = glm::translate(modelMatrixWall11, glm::vec3(-8.2, 46.4, 2.1));
	modelMatrixWall11 = glm::scale(modelMatrixWall11, glm::vec3(18, 10, 1));

	modelMatrixWall12 = glm::rotate(modelMatrixWall12, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall12 = glm::scale(modelMatrixWall12, glm::vec3(1, 1, 2));
	modelMatrixWall12 = glm::translate(modelMatrixWall12, glm::vec3(24.8, 41.6, 2.1));
	modelMatrixWall12 = glm::scale(modelMatrixWall12, glm::vec3(9, 14.5, 1));

	modelMatrixWall13 = glm::rotate(modelMatrixWall13, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall13 = glm::scale(modelMatrixWall13, glm::vec3(1, 1, 2));
	modelMatrixWall13 = glm::translate(modelMatrixWall13, glm::vec3(-42.6, 41.6, 2.1));
	modelMatrixWall13 = glm::scale(modelMatrixWall13, glm::vec3(9, 14.5, 1));

	modelMatrixWall14 = glm::rotate(modelMatrixWall14, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall14 = glm::scale(modelMatrixWall14, glm::vec3(1, 1, 2));
	modelMatrixWall14 = glm::translate(modelMatrixWall14, glm::vec3(-9.6, -49.4, 2.1));
	modelMatrixWall14 = glm::scale(modelMatrixWall14, glm::vec3(25, 15, 1));

	modelMatrixWall15 = glm::rotate(modelMatrixWall15, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall15= glm::scale(modelMatrixWall15, glm::vec3(1, 1, 2));
	modelMatrixWall15 = glm::translate(modelMatrixWall15, glm::vec3(-54.1, -76.6, 2.1));
	modelMatrixWall15 = glm::scale(modelMatrixWall15, glm::vec3(29, 7, 1));

	modelMatrixWall16 = glm::rotate(modelMatrixWall16, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall16 = glm::scale(modelMatrixWall16, glm::vec3(1, 1, 2));
	modelMatrixWall16 = glm::translate(modelMatrixWall16, glm::vec3(53.2, -73, 2.1));
	modelMatrixWall16 = glm::scale(modelMatrixWall16, glm::vec3(31, 10, 1));

	modelMatrixWall17 = glm::rotate(modelMatrixWall17, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall17 = glm::scale(modelMatrixWall17, glm::vec3(1, 1, 2));
	modelMatrixWall17 = glm::translate(modelMatrixWall17, glm::vec3(-74.4, 12.4, 2.1));
	modelMatrixWall17 = glm::scale(modelMatrixWall17, glm::vec3(16.7, 18.2, 1));

	modelMatrixWall18 = glm::rotate(modelMatrixWall18, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall18 = glm::scale(modelMatrixWall18, glm::vec3(1, 1, 2));
	modelMatrixWall18 = glm::translate(modelMatrixWall18, glm::vec3(-3, 75.8, 2.1));
	modelMatrixWall18 = glm::scale(modelMatrixWall18, glm::vec3(11, 14, 1));

	modelMatrixWall19 = glm::rotate(modelMatrixWall19, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall19 = glm::scale(modelMatrixWall19, glm::vec3(1, 1, 2));
	modelMatrixWall19 = glm::translate(modelMatrixWall19, glm::vec3(-7.8, 33.6, 2.1));
	modelMatrixWall19 = glm::scale(modelMatrixWall19, glm::vec3(3, 4, 1));

	modelMatrixWall20 = glm::rotate(modelMatrixWall20, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall20 = glm::scale(modelMatrixWall20, glm::vec3(1, 1, 2));
	modelMatrixWall20 = glm::translate(modelMatrixWall20, glm::vec3(75.6, -50.2, 2.1));
	modelMatrixWall20 = glm::scale(modelMatrixWall20, glm::vec3(14, 8, 1));

	modelMatrixWall21 = glm::rotate(modelMatrixWall21, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall21 = glm::scale(modelMatrixWall21, glm::vec3(1, 1, 2));
	modelMatrixWall21 = glm::translate(modelMatrixWall21, glm::vec3(29.4, -51.8, 2.1));
	modelMatrixWall21 = glm::scale(modelMatrixWall21, glm::vec3(8, 18, 1));

	modelMatrixWall22 = glm::rotate(modelMatrixWall22, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall22 = glm::scale(modelMatrixWall22, glm::vec3(1, 1, 2));
	modelMatrixWall22 = glm::translate(modelMatrixWall22, glm::vec3(-46.5, -52.2, 2.1));
	modelMatrixWall22 = glm::scale(modelMatrixWall22, glm::vec3(5, 18, 1));

	modelMatrixWall23 = glm::rotate(modelMatrixWall23, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall23 = glm::scale(modelMatrixWall23, glm::vec3(1, 1, 2));
	modelMatrixWall23 = glm::translate(modelMatrixWall23, glm::vec3(-64.6, -37.8, 2.1));
	modelMatrixWall23 = glm::scale(modelMatrixWall23, glm::vec3(7, 26, 1));

	modelMatrixWall24 = glm::rotate(modelMatrixWall24, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall24 = glm::scale(modelMatrixWall24, glm::vec3(1, 1, 2));
	modelMatrixWall24 = glm::translate(modelMatrixWall24, glm::vec3(-78, -20.2, 2.1));
	modelMatrixWall24 = glm::scale(modelMatrixWall24, glm::vec3(7, 8.5, 1));

	modelMatrixWall25 = glm::rotate(modelMatrixWall25, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall25 = glm::scale(modelMatrixWall25, glm::vec3(1, 1, 2));
	modelMatrixWall25 = glm::translate(modelMatrixWall25, glm::vec3(-84.4, -49.4, 2.1));
	modelMatrixWall25 = glm::scale(modelMatrixWall25, glm::vec3(6, 14, 1));

	modelMatrixWall26 = glm::rotate(modelMatrixWall26, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall26 = glm::scale(modelMatrixWall26, glm::vec3(1, 1, 2));
	modelMatrixWall26 = glm::translate(modelMatrixWall26, glm::vec3(-9.8, -73.2, 2.1));
	modelMatrixWall26 = glm::scale(modelMatrixWall26, glm::vec3(9, 9, 1));

	modelMatrixWall27 = glm::rotate(modelMatrixWall27, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall27 = glm::scale(modelMatrixWall27, glm::vec3(1, 1, 2));
	modelMatrixWall27 = glm::translate(modelMatrixWall27, glm::vec3(14,-76.4, 2.1));
	modelMatrixWall27 = glm::scale(modelMatrixWall27, glm::vec3(8.3, 7, 1));

	modelMatrixWall28 = glm::rotate(modelMatrixWall28, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall28 = glm::scale(modelMatrixWall28, glm::vec3(1, 1, 2));
	modelMatrixWall28 = glm::translate(modelMatrixWall28, glm::vec3(49.2, -47, 2.1));
	modelMatrixWall28 = glm::scale(modelMatrixWall28, glm::vec3(7, 10, 1));

	modelMatrixWall29 = glm::rotate(modelMatrixWall29, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall29 = glm::scale(modelMatrixWall29, glm::vec3(1, 1, 2));
	modelMatrixWall29 = glm::translate(modelMatrixWall29, glm::vec3(28.2, 14, 2.1));
	modelMatrixWall29 = glm::scale(modelMatrixWall29, glm::vec3(4, 13.3, 1));

	modelMatrixWall30 = glm::rotate(modelMatrixWall30, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall30 = glm::scale(modelMatrixWall30, glm::vec3(1, 1, 2));
	modelMatrixWall30 = glm::translate(modelMatrixWall30, glm::vec3(-43.6, 14, 2.1));
	modelMatrixWall30 = glm::scale(modelMatrixWall30, glm::vec3(6, 13.3, 1));

	modelMatrixWall31 = glm::rotate(modelMatrixWall31, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall31 = glm::scale(modelMatrixWall31, glm::vec3(1, 1, 2));
	modelMatrixWall31 = glm::translate(modelMatrixWall31, glm::vec3(-28.8, 29, 2.1));
	modelMatrixWall31 = glm::scale(modelMatrixWall31, glm::vec3(8, 1.5, 1));

	modelMatrixWall32 = glm::rotate(modelMatrixWall32, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall32 = glm::scale(modelMatrixWall32, glm::vec3(1, 1, 2));
	modelMatrixWall32 = glm::translate(modelMatrixWall32, glm::vec3(13.4, 29.4, 2.1));
	modelMatrixWall32 = glm::scale(modelMatrixWall32, glm::vec3(8, 1.5, 1));

	modelMatrixWall34 = glm::rotate(modelMatrixWall34, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall34 = glm::scale(modelMatrixWall34, glm::vec3(1, 1, 2));
	modelMatrixWall34 = glm::translate(modelMatrixWall34, glm::vec3(0, 93.5, 2.1));
	modelMatrixWall34 = glm::scale(modelMatrixWall34, glm::vec3(100, 4, 1));

	modelMatrixWall35 = glm::rotate(modelMatrixWall35, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall35 = glm::scale(modelMatrixWall35, glm::vec3(1, 1, 2));
	modelMatrixWall35 = glm::translate(modelMatrixWall35, glm::vec3(0, -92.5, 2.1));
	modelMatrixWall35 = glm::scale(modelMatrixWall35, glm::vec3(100, 4, 1));

	modelMatrixWall36 = glm::rotate(modelMatrixWall36, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall36 = glm::scale(modelMatrixWall36, glm::vec3(1, 1, 2));
	modelMatrixWall36 = glm::translate(modelMatrixWall36, glm::vec3(-93.5, 0, 2.1));
	modelMatrixWall36 = glm::scale(modelMatrixWall36, glm::vec3(4, 100, 1));

	modelMatrixWall37 = glm::rotate(modelMatrixWall37, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall37 = glm::scale(modelMatrixWall37, glm::vec3(1, 1, 2));
	modelMatrixWall37 = glm::translate(modelMatrixWall37, glm::vec3(93.5, 0, 2.1));
	modelMatrixWall37 = glm::scale(modelMatrixWall37, glm::vec3(4, 100, 1));
	
    modelMatrixWall33 = glm::rotate(modelMatrixWall33, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall33 = glm::scale(modelMatrixWall33, glm::vec3(1, 1, 2));
	modelMatrixWall33 = glm::translate(modelMatrixWall33, glm::vec3(18.9, 11.2, 2.1));
	modelMatrixWall33 = glm::scale(modelMatrixWall33, glm::vec3(0.5, 10, 1));

    modelMatrixWall38 = glm::rotate(modelMatrixWall38, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall38 = glm::scale(modelMatrixWall38, glm::vec3(1, 1, 2));
	modelMatrixWall38 = glm::translate(modelMatrixWall38, glm::vec3(-6.2, 1.5, 2.1));
	modelMatrixWall38 = glm::scale(modelMatrixWall38, glm::vec3(25.6, 0.5, 1));

	modelMatrixWall39 = glm::rotate(modelMatrixWall39, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall39 = glm::scale(modelMatrixWall39, glm::vec3(1, 1, 2));
	modelMatrixWall39 = glm::translate(modelMatrixWall39, glm::vec3(-31, 11.2, 2.1));
	modelMatrixWall39 = glm::scale(modelMatrixWall39, glm::vec3(0.5, 10, 1));

	modelMatrixWall40 = glm::rotate(modelMatrixWall40, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall40 = glm::scale(modelMatrixWall40, glm::vec3(1, 1, 2));
	modelMatrixWall40 = glm::translate(modelMatrixWall40, glm::vec3(11.6, 20.8, 2.1));
	modelMatrixWall40 = glm::scale(modelMatrixWall40, glm::vec3(7, 0.5, 1));

    modelMatrixWall41 = glm::rotate(modelMatrixWall41, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixWall41 = glm::scale(modelMatrixWall41, glm::vec3(1, 1, 2));
	modelMatrixWall41 = glm::translate(modelMatrixWall41, glm::vec3(-23.6, 20.8, 2.1));
	modelMatrixWall41 = glm::scale(modelMatrixWall41, glm::vec3(8, 0.5, 1));


    //Ghosts

	modelMatrixGhostRed = glm::translate(modelMatrixGhostRed, glm::vec3(13.6, 2.2, -12.8));
	modelMatrixGhostRed = glm::scale(modelMatrixGhostRed, glm::vec3(1.4, 1.4, 1.4));
	modelMatrixGhostRed = glm::rotate(modelMatrixGhostRed, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixGhostRed = glm::rotate(modelMatrixGhostRed, glm::radians(90.0f), glm::vec3(0, 0, 1));

	modelMatrixGhostPink = glm::translate(modelMatrixGhostPink, glm::vec3(-13.6, 2.2, -12.8));
	modelMatrixGhostPink = glm::scale(modelMatrixGhostPink, glm::vec3(1.4, 1.4, 1.4));
	modelMatrixGhostPink = glm::rotate(modelMatrixGhostPink, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixGhostPink = glm::rotate(modelMatrixGhostPink, glm::radians(90.0f), glm::vec3(0, 0, -1));

	modelMatrixGhostBlue = glm::translate(modelMatrixGhostBlue, glm::vec3(13.6, 2.2, -6.4));
	modelMatrixGhostBlue = glm::scale(modelMatrixGhostBlue, glm::vec3(1.4, 1.4, 1.4));
	modelMatrixGhostBlue = glm::rotate(modelMatrixGhostBlue, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixGhostBlue = glm::rotate(modelMatrixGhostBlue, glm::radians(90.0f), glm::vec3(0, 0, 1));

	modelMatrixGhostOrange = glm::translate(modelMatrixGhostOrange, glm::vec3(-13.6, 2.2, -6.4));
	modelMatrixGhostOrange = glm::scale(modelMatrixGhostOrange, glm::vec3(1.4, 1.4, 1.4));
	modelMatrixGhostOrange = glm::rotate(modelMatrixGhostOrange, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	modelMatrixGhostOrange = glm::rotate(modelMatrixGhostOrange, glm::radians(90.0f), glm::vec3(0, 0, -1));

	lastTime = TimeManager::Instance().GetTime();

	textureActivaID = textureInit1ID;

	glm::vec3 lightPos = glm::vec3(10.0, 10.0, -10.0);

	shadowBox = new ShadowBox(-lightPos, camera.get(), 15.0f, 0.1f, 45.0f);

	while (psi) {
		currTime = TimeManager::Instance().GetTime();
		if(currTime - lastTime < 0.016666667){
			glfwPollEvents();
			continue;
		}
		lastTime = currTime;
		//currentTime = currTime;

		TimeManager::Instance().CalculateFrameRate(true);
		deltaTime = TimeManager::Instance().DeltaTime;
		psi = processInput(true);

		if(vidas < 0){
			psi = false;
		}

		std::map<std::string, bool> collisionDetection;

		// Variables donde se guardan las matrices de cada articulacion por 1 frame
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
				(float) screenWidth / (float) screenHeight, 0.01f, 100.0f);

		
		axis = glm::axis(glm::quat_cast(modelMatrixMayow));
		angleTarget = glm::angle(glm::quat_cast(modelMatrixMayow));
		target = modelMatrixMayow[3];
		
		if(std::isnan(angleTarget))
			angleTarget = 0.0;
		if(axis.y < 0)
			angleTarget = -angleTarget;
		if(modelSelected == 1)
			angleTarget -= glm::radians(90.0f);
		camera->setCameraTarget(target);
		camera->setAngleTarget(angleTarget);
		camera->updateCamera();
		glm::mat4 view = camera->getViewMatrix();

		shadowBox->update(screenWidth, screenHeight);
		glm::vec3 centerBox = shadowBox->getCenter();

		// Projection light shadow mapping
		glm::mat4 lightProjection = glm::mat4(1.0f), lightView = glm::mat4(1.0f);
		glm::mat4 lightSpaceMatrix;
		lightProjection[0][0] = 2.0f / shadowBox->getWidth();
		lightProjection[1][1] = 2.0f / shadowBox->getHeight();
		lightProjection[2][2] = -2.0f / shadowBox->getLength();
		lightProjection[3][3] = 1.0f;
		lightView = glm::lookAt(centerBox, centerBox + glm::normalize(-lightPos), glm::vec3(0.0, 1.0, 0.0));
		lightSpaceMatrix = lightProjection * lightView;
		shaderDepth.setMatrix4("lightSpaceMatrix", 1, false, glm::value_ptr(lightSpaceMatrix));

		// Settea la matriz de vista y projection al shader con solo color
		shader.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shader.setMatrix4("view", 1, false, glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con skybox
		shaderSkybox.setMatrix4("projection", 1, false,
				glm::value_ptr(projection));
		shaderSkybox.setMatrix4("view", 1, false,
				glm::value_ptr(glm::mat4(glm::mat3(view))));
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderMulLighting.setMatrix4("projection", 1, false,
					glm::value_ptr(projection));
		shaderMulLighting.setMatrix4("view", 1, false,
				glm::value_ptr(view));
		shaderMulLighting.setMatrix4("lightSpaceMatrix", 1, false,
				glm::value_ptr(lightSpaceMatrix));
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderTerrain.setMatrix4("projection", 1, false,
				glm::value_ptr(projection));
		shaderTerrain.setMatrix4("view", 1, false,
				glm::value_ptr(view));
		shaderTerrain.setMatrix4("lightSpaceMatrix", 1, false,
				glm::value_ptr(lightSpaceMatrix));
		// Settea la matriz de vista y projection al shader para el fountain
		/*shaderParticlesFountain.setMatrix4("projection", 1, false,
				glm::value_ptr(projection));
		shaderParticlesFountain.setMatrix4("view", 1, false,
				glm::value_ptr(view));*/

		/*******************************************
		 * Propiedades de neblina
		 *******************************************/
		shaderMulLighting.setVectorFloat3("fogColor", glm::value_ptr(glm::vec3(0.5, 0.5, 0.4)));
		shaderTerrain.setVectorFloat3("fogColor", glm::value_ptr(glm::vec3(0.5, 0.5, 0.4)));
		shaderSkybox.setVectorFloat3("fogColor", glm::value_ptr(glm::vec3(0.5, 0.5, 0.4)));

		/*******************************************
		 * Propiedades Luz direccional
		 *******************************************/
		shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderMulLighting.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
		shaderMulLighting.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-0.707106781, -0.707106781, 0.0)));

		shaderTerrain.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderTerrain.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
		shaderTerrain.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		shaderTerrain.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
		shaderTerrain.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-0.707106781, -0.707106781, 0.0)));

		/*******************************************
		 * Propiedades SpotLights
		 *******************************************/

		/*******************************************
		 * Propiedades PointLights
		 *******************************************/
		
		
		/************Render de imagen de frente**************/
		if(!iniciaPartida){
			shaderTexture.setMatrix4("projection", 1, false, glm::value_ptr(glm::mat4(1.0)));
			shaderTexture.setMatrix4("view", 1, false, glm::value_ptr(glm::mat4(1.0)));
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureActivaID);
			shaderTexture.setInt("outTexture", 0);
			boxIntro.render();
			glfwSwapBuffers(window);
			continue;
		}

		/*******************************************
		 * 1.- We render the depth buffer
		 *******************************************/
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// render scene from light's point of view
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		glCullFace(GL_FRONT);
		prepareDepthScene();
		renderScene();
		glCullFace(GL_BACK);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		/*******************************************
		 * Debug to view the texture view map
		 *******************************************/
		// reset viewport
		/*glViewport(0, 0, screenWidth, screenHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// render Depth map to quad for visual debugging
		shaderViewDepth.setMatrix4("projection", 1, false, glm::value_ptr(glm::mat4(1.0)));
		shaderViewDepth.setMatrix4("view", 1, false, glm::value_ptr(glm::mat4(1.0)));
		shaderViewDepth.setFloat("near_plane", near_plane);
		shaderViewDepth.setFloat("far_plane", far_plane);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		boxViewDepth.setScale(glm::vec3(2.0, 2.0, 1.0));
		boxViewDepth.render();*/

		/*******************************************
		 * 2.- We render the normal objects
		 *******************************************/
		glViewport(0, 0, screenWidth, screenHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		prepareScene();
		glActiveTexture(GL_TEXTURE10);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		shaderMulLighting.setInt("shadowMap", 10);
		shaderTerrain.setInt("shadowMap", 10);
		renderSolidScene();

		/*******************************************
		 * Creacion de colliders
		 * IMPORTANT do this before interpolations
		 *******************************************/

	/*
		AbstractModel::OBB wall1Collider;
		// Set the orientation of collider before doing the scale
		wall1Collider.u = glm::quat_cast(modelMatrixWall1);
		modelMatrixColliderWall1 = glm::translate(
				modelMatrixColliderWall1, modelLargeWall.getObb().c);
		wall1Collider.c = glm::vec3(modelMatrixColliderWall1[3]);
		wall1Collider.e = modelLargeWall.getObb().e * glm::vec3(1.0, 1.0, 1.0);
		addOrUpdateColliders(collidersOBB, "LargeWall", wall1Collider, modelMatrixWall1);
	*/
		glm::mat4 modelMatrixColliderWall1 = glm::mat4(1.0f);
		modelMatrixColliderWall1[3] = modelMatrixWall1[3];
		AbstractModel::OBB wall1Collider;
		// Set the orientation of collider before doing the scale
		wall1Collider.u = glm::quat_cast(modelMatrixColliderWall1);
		modelMatrixColliderWall1 = glm::scale(modelMatrixColliderWall1,
				glm::vec3(16.1, 2, 12.1));
		modelMatrixColliderWall1 = glm::translate(
				modelMatrixColliderWall1, modelLargeWall.getObb().c);
		wall1Collider.c = glm::vec3(modelMatrixColliderWall1[3]);
		wall1Collider.e = modelLargeWall.getObb().e * glm::vec3(16.1, 2, 10.1);
		addOrUpdateColliders(collidersOBB, "pared1", wall1Collider, modelMatrixColliderWall1);

		glm::mat4 modelMatrixColliderWall2 = glm::mat4(1.0f);
		modelMatrixColliderWall2[3] = modelMatrixWall2[3];
		AbstractModel::OBB wall2Collider;
		// Set the orientation of collider before doing the scale
		wall2Collider.u = glm::quat_cast(modelMatrixColliderWall2);
		modelMatrixColliderWall2 = glm::scale(modelMatrixColliderWall2,
				glm::vec3(13.1, 2, 10.1));
		modelMatrixColliderWall2 = glm::translate(
				modelMatrixColliderWall2, modelLargeWall.getObb().c);
		wall2Collider.c = glm::vec3(modelMatrixColliderWall2[3]);
		wall2Collider.e = modelLargeWall.getObb().e * glm::vec3(13.1, 2, 10.1);
		addOrUpdateColliders(collidersOBB, "pared2", wall2Collider, modelMatrixColliderWall2);

		glm::mat4 modelMatrixColliderWall3 = glm::mat4(1.0f);
		modelMatrixColliderWall3[3] = modelMatrixWall3[3];
		AbstractModel::OBB wall3Collider;
		// Set the orientation of collider before doing the scale
		wall3Collider.u = glm::quat_cast(modelMatrixColliderWall3);
		modelMatrixColliderWall3 = glm::scale(modelMatrixColliderWall3,
				glm::vec3(13.1, 2, 10.1));
		modelMatrixColliderWall3 = glm::translate(
				modelMatrixColliderWall3, modelLargeWall.getObb().c);
		wall3Collider.c = glm::vec3(modelMatrixColliderWall3[3]);
		wall3Collider.e = modelLargeWall.getObb().e * glm::vec3(13.1, 2, 10.1);
		addOrUpdateColliders(collidersOBB, "pared3", wall3Collider, modelMatrixColliderWall3);

		glm::mat4 modelMatrixColliderWall4 = glm::mat4(1.0f);
		modelMatrixColliderWall4[3] = modelMatrixWall4[3];
		AbstractModel::OBB wall4Collider;
		// Set the orientation of collider before doing the scale
		wall4Collider.u = glm::quat_cast(modelMatrixColliderWall4);
		modelMatrixColliderWall4 = glm::scale(modelMatrixColliderWall4,
				glm::vec3(10.1, 2, 9.1));
		modelMatrixColliderWall4 = glm::translate(
				modelMatrixColliderWall4, modelLargeWall.getObb().c);
		wall4Collider.c = glm::vec3(modelMatrixColliderWall4[3]);
		wall4Collider.e = modelLargeWall.getObb().e * glm::vec3(10.1, 2, 9.1);
		addOrUpdateColliders(collidersOBB, "pared4", wall4Collider, modelMatrixColliderWall4);

		glm::mat4 modelMatrixColliderWall5 = glm::mat4(1.0f);
		modelMatrixColliderWall5[3] = modelMatrixWall5[3];
		AbstractModel::OBB wall5Collider;
		// Set the orientation of collider before doing the scale
		wall5Collider.u = glm::quat_cast(modelMatrixColliderWall5);
		modelMatrixColliderWall5 = glm::scale(modelMatrixColliderWall5,
				glm::vec3(21.1, 2, 9.1));
		modelMatrixColliderWall5 = glm::translate(
				modelMatrixColliderWall5, modelLargeWall.getObb().c);
		wall5Collider.c = glm::vec3(modelMatrixColliderWall5[3]);
		wall5Collider.e = modelLargeWall.getObb().e * glm::vec3(21.1, 2, 9.1);
		addOrUpdateColliders(collidersOBB, "pared5", wall5Collider, modelMatrixColliderWall5);

		glm::mat4 modelMatrixColliderWall6 = glm::mat4(1.0f);
		modelMatrixColliderWall6[3] = modelMatrixWall6[3];
		AbstractModel::OBB wall6Collider;
		// Set the orientation of collider before doing the scale
		wall6Collider.u = glm::quat_cast(modelMatrixColliderWall6);
		modelMatrixColliderWall6 = glm::scale(modelMatrixColliderWall6,
				glm::vec3(21.1, 2, 7.1));
		modelMatrixColliderWall6 = glm::translate(
				modelMatrixColliderWall6, modelLargeWall.getObb().c);
		wall6Collider.c = glm::vec3(modelMatrixColliderWall6[3]);
		wall6Collider.e = modelLargeWall.getObb().e * glm::vec3(21.1, 2, 6.6);
		addOrUpdateColliders(collidersOBB, "pared6", wall6Collider, modelMatrixColliderWall6);

		glm::mat4 modelMatrixColliderWall7 = glm::mat4(1.0f);
		modelMatrixColliderWall7[3] = modelMatrixWall7[3];
		AbstractModel::OBB wall7Collider;
		// Set the orientation of collider before doing the scale
		wall7Collider.u = glm::quat_cast(modelMatrixColliderWall7);
		modelMatrixColliderWall7 = glm::scale(modelMatrixColliderWall7,
				glm::vec3(21.1, 2, 15.8));
		modelMatrixColliderWall7 = glm::translate(
				modelMatrixColliderWall7, modelLargeWall.getObb().c);
		wall7Collider.c = glm::vec3(modelMatrixColliderWall7[3]);
		wall7Collider.e = modelLargeWall.getObb().e * glm::vec3(21.1, 2, 15.8);
		addOrUpdateColliders(collidersOBB, "pared7", wall7Collider, modelMatrixColliderWall7);

		glm::mat4 modelMatrixColliderWall8 = glm::mat4(1.0f);
		modelMatrixColliderWall8[3] = modelMatrixWall8[3];
		AbstractModel::OBB wall8Collider;
		// Set the orientation of collider before doing the scale
		wall8Collider.u = glm::quat_cast(modelMatrixColliderWall8);
		modelMatrixColliderWall8 = glm::scale(modelMatrixColliderWall8,
				glm::vec3(21.1, 2, 11.1));
		modelMatrixColliderWall8 = glm::translate(
				modelMatrixColliderWall8, modelLargeWall.getObb().c);
		wall8Collider.c = glm::vec3(modelMatrixColliderWall8[3]);
		wall8Collider.e = modelLargeWall.getObb().e * glm::vec3(21.1, 2, 11.1);
		addOrUpdateColliders(collidersOBB, "pared8", wall8Collider, modelMatrixColliderWall8);

		glm::mat4 modelMatrixColliderWall9 = glm::mat4(1.0f);
		modelMatrixColliderWall9[3] = modelMatrixWall9[3];
		AbstractModel::OBB wall9Collider;
		// Set the orientation of collider before doing the scale
		wall9Collider.u = glm::quat_cast(modelMatrixColliderWall9);
		modelMatrixColliderWall9 = glm::scale(modelMatrixColliderWall9,
				glm::vec3(10.1, 2, 6.6));
		modelMatrixColliderWall9 = glm::translate(
				modelMatrixColliderWall9, modelLargeWall.getObb().c);
		wall9Collider.c = glm::vec3(modelMatrixColliderWall9[3]);
		wall9Collider.e = modelLargeWall.getObb().e * glm::vec3(10.1, 2, 6.6);
		addOrUpdateColliders(collidersOBB, "pared9", wall9Collider, modelMatrixColliderWall9);

		glm::mat4 modelMatrixColliderWall10 = glm::mat4(1.0f);
		modelMatrixColliderWall10[3] = modelMatrixWall10[3];
		AbstractModel::OBB wall10Collider;
		// Set the orientation of collider before doing the scale
		wall10Collider.u = glm::quat_cast(modelMatrixColliderWall10);
		modelMatrixColliderWall10 = glm::scale(modelMatrixColliderWall10,
				glm::vec3(18.1, 2, 6.6));
		modelMatrixColliderWall10 = glm::translate(
				modelMatrixColliderWall10, modelLargeWall.getObb().c);
		wall10Collider.c = glm::vec3(modelMatrixColliderWall10[3]);
		wall10Collider.e = modelLargeWall.getObb().e * glm::vec3(18.1, 2, 6.6);
		addOrUpdateColliders(collidersOBB, "pared10", wall10Collider, modelMatrixColliderWall10);

		glm::mat4 modelMatrixColliderWall11 = glm::mat4(1.0f);
		modelMatrixColliderWall11[3] = modelMatrixWall11[3];
		AbstractModel::OBB wall11Collider;
		// Set the orientation of collider before doing the scale
		wall11Collider.u = glm::quat_cast(modelMatrixColliderWall11);
		modelMatrixColliderWall11 = glm::scale(modelMatrixColliderWall11,
				glm::vec3(18.1, 2, 8.1));
		modelMatrixColliderWall11 = glm::translate(
				modelMatrixColliderWall11, modelLargeWall.getObb().c);
		wall11Collider.c = glm::vec3(modelMatrixColliderWall11[3]);
		wall11Collider.e = modelLargeWall.getObb().e * glm::vec3(18.1, 2, 8.1);
		addOrUpdateColliders(collidersOBB, "pared11", wall11Collider, modelMatrixColliderWall11);

		glm::mat4 modelMatrixColliderWall12 = glm::mat4(1.0f);
		modelMatrixColliderWall12[3] = modelMatrixWall12[3];
		AbstractModel::OBB wall12Collider;
		// Set the orientation of collider before doing the scale
		wall12Collider.u = glm::quat_cast(modelMatrixColliderWall12);
		modelMatrixColliderWall12 = glm::scale(modelMatrixColliderWall12,
				glm::vec3(9.1, 2, 12));
		modelMatrixColliderWall12 = glm::translate(
				modelMatrixColliderWall12, modelLargeWall.getObb().c);
		wall12Collider.c = glm::vec3(modelMatrixColliderWall12[3]);
		wall12Collider.e = modelLargeWall.getObb().e * glm::vec3(9.1, 2, 12);
		addOrUpdateColliders(collidersOBB, "pared12", wall12Collider, modelMatrixColliderWall12);

		glm::mat4 modelMatrixColliderWall13 = glm::mat4(1.0f);
		modelMatrixColliderWall13[3] = modelMatrixWall13[3];
		AbstractModel::OBB wall13Collider;
		// Set the orientation of collider before doing the scale
		wall13Collider.u = glm::quat_cast(modelMatrixColliderWall13);
		modelMatrixColliderWall13 = glm::scale(modelMatrixColliderWall13,
				glm::vec3(9.1, 2, 12.1));
		modelMatrixColliderWall13 = glm::translate(
				modelMatrixColliderWall13, modelLargeWall.getObb().c);
		wall13Collider.c = glm::vec3(modelMatrixColliderWall13[3]);
		wall13Collider.e = modelLargeWall.getObb().e * glm::vec3(9.1, 2, 12.1);
		addOrUpdateColliders(collidersOBB, "pared13", wall13Collider, modelMatrixColliderWall13);

		glm::mat4 modelMatrixColliderWall14 = glm::mat4(1.0f);
		modelMatrixColliderWall14[3] = modelMatrixWall14[3];
		AbstractModel::OBB wall14Collider;
		// Set the orientation of collider before doing the scale
		wall14Collider.u = glm::quat_cast(modelMatrixColliderWall14);
		modelMatrixColliderWall14 = glm::scale(modelMatrixColliderWall14,
				glm::vec3(25.1, 2, 12.5));
		modelMatrixColliderWall14 = glm::translate(
				modelMatrixColliderWall14, modelLargeWall.getObb().c);
		wall14Collider.c = glm::vec3(modelMatrixColliderWall14[3]);
		wall14Collider.e = modelLargeWall.getObb().e * glm::vec3(25.1, 2, 12.5);
		addOrUpdateColliders(collidersOBB, "pared14", wall14Collider, modelMatrixColliderWall14);

		glm::mat4 modelMatrixColliderWall15 = glm::mat4(1.0f);
		modelMatrixColliderWall15[3] = modelMatrixWall15[3];
		AbstractModel::OBB wall15Collider;
		// Set the orientation of collider before doing the scale
		wall15Collider.u = glm::quat_cast(modelMatrixColliderWall15);
		modelMatrixColliderWall15 = glm::scale(modelMatrixColliderWall15,
				glm::vec3(29.1, 2, 5.9));
		modelMatrixColliderWall15 = glm::translate(
				modelMatrixColliderWall15, modelLargeWall.getObb().c);
		wall15Collider.c = glm::vec3(modelMatrixColliderWall15[3]);
		wall15Collider.e = modelLargeWall.getObb().e * glm::vec3(29.1, 2, 5.9);
		addOrUpdateColliders(collidersOBB, "pared15", wall15Collider, modelMatrixColliderWall15);

		glm::mat4 modelMatrixColliderWall16 = glm::mat4(1.0f);
		modelMatrixColliderWall16[3] = modelMatrixWall16[3];
		AbstractModel::OBB wall16Collider;
		// Set the orientation of collider before doing the scale
		wall16Collider.u = glm::quat_cast(modelMatrixColliderWall16);
		modelMatrixColliderWall16 = glm::scale(modelMatrixColliderWall16,
				glm::vec3(31.1, 2, 8.1));
		modelMatrixColliderWall16 = glm::translate(
				modelMatrixColliderWall16, modelLargeWall.getObb().c);
		wall16Collider.c = glm::vec3(modelMatrixColliderWall16[3]);
		wall16Collider.e = modelLargeWall.getObb().e * glm::vec3(31.1, 2, 8.1);
		addOrUpdateColliders(collidersOBB, "pared16", wall16Collider, modelMatrixColliderWall16);

		glm::mat4 modelMatrixColliderWall17 = glm::mat4(1.0f);
		modelMatrixColliderWall17[3] = modelMatrixWall17[3];
		AbstractModel::OBB wall17Collider;
		// Set the orientation of collider before doing the scale
		wall17Collider.u = glm::quat_cast(modelMatrixColliderWall17);
		modelMatrixColliderWall17 = glm::scale(modelMatrixColliderWall17,
				glm::vec3(16.7, 2, 14.6));
		modelMatrixColliderWall17 = glm::translate(
				modelMatrixColliderWall17, modelLargeWall.getObb().c);
		wall17Collider.c = glm::vec3(modelMatrixColliderWall17[3]);
		wall17Collider.e = modelLargeWall.getObb().e * glm::vec3(16.7, 2, 14.6);
		addOrUpdateColliders(collidersOBB, "pared17", wall17Collider, modelMatrixColliderWall17);

		glm::mat4 modelMatrixColliderWall18 = glm::mat4(1.0f);
		modelMatrixColliderWall18[3] = modelMatrixWall18[3];
		AbstractModel::OBB wall18Collider;
		// Set the orientation of collider before doing the scale
		wall18Collider.u = glm::quat_cast(modelMatrixColliderWall18);
		modelMatrixColliderWall18 = glm::scale(modelMatrixColliderWall18,
				glm::vec3(11.1, 2, 11.2));
		modelMatrixColliderWall18 = glm::translate(
				modelMatrixColliderWall18, modelLargeWall.getObb().c);
		wall18Collider.c = glm::vec3(modelMatrixColliderWall18[3]);
		wall18Collider.e = modelLargeWall.getObb().e * glm::vec3(11.1, 2, 11.2);
		addOrUpdateColliders(collidersOBB, "pared18", wall18Collider, modelMatrixColliderWall18);

		glm::mat4 modelMatrixColliderWall19 = glm::mat4(1.0f);
		modelMatrixColliderWall19[3] = modelMatrixWall19[3];
		AbstractModel::OBB wall19Collider;
		// Set the orientation of collider before doing the scale
		wall19Collider.u = glm::quat_cast(modelMatrixColliderWall19);
		modelMatrixColliderWall19 = glm::scale(modelMatrixColliderWall19,
				glm::vec3(3.1, 2, 3.3));
		modelMatrixColliderWall19 = glm::translate(
				modelMatrixColliderWall19, modelLargeWall.getObb().c);
		wall19Collider.c = glm::vec3(modelMatrixColliderWall19[3]);
		wall19Collider.e = modelLargeWall.getObb().e * glm::vec3(3.1, 2, 3.3);
		addOrUpdateColliders(collidersOBB, "pared19", wall19Collider, modelMatrixColliderWall19);

		glm::mat4 modelMatrixColliderWall20 = glm::mat4(1.0f);
		modelMatrixColliderWall20[3] = modelMatrixWall20[3];
		AbstractModel::OBB wall20Collider;
		// Set the orientation of collider before doing the scale
		wall20Collider.u = glm::quat_cast(modelMatrixColliderWall20);
		modelMatrixColliderWall20 = glm::scale(modelMatrixColliderWall20,
				glm::vec3(14.1, 2, 6.4));
		modelMatrixColliderWall20 = glm::translate(
				modelMatrixColliderWall20, modelLargeWall.getObb().c);
		wall20Collider.c = glm::vec3(modelMatrixColliderWall20[3]);
		wall20Collider.e = modelLargeWall.getObb().e * glm::vec3(14.1, 2, 6.4);
		addOrUpdateColliders(collidersOBB, "pared20", wall20Collider, modelMatrixColliderWall20);

		glm::mat4 modelMatrixColliderWall21 = glm::mat4(1.0f);
		modelMatrixColliderWall21[3] = modelMatrixWall21[3];
		AbstractModel::OBB wall21Collider;
		// Set the orientation of collider before doing the scale
		wall21Collider.u = glm::quat_cast(modelMatrixColliderWall21);
		modelMatrixColliderWall21 = glm::scale(modelMatrixColliderWall21,
				glm::vec3(8.1, 2, 15.1));
		modelMatrixColliderWall21 = glm::translate(
				modelMatrixColliderWall21, modelLargeWall.getObb().c);
		wall21Collider.c = glm::vec3(modelMatrixColliderWall21[3]);
		wall21Collider.e = modelLargeWall.getObb().e * glm::vec3(8.1, 2, 15.1);
		addOrUpdateColliders(collidersOBB, "pared21", wall21Collider, modelMatrixColliderWall21);

		glm::mat4 modelMatrixColliderWall22 = glm::mat4(1.0f);
		modelMatrixColliderWall22[3] = modelMatrixWall22[3];
		AbstractModel::OBB wall22Collider;
		// Set the orientation of collider before doing the scale
		wall22Collider.u = glm::quat_cast(modelMatrixColliderWall22);
		modelMatrixColliderWall22 = glm::scale(modelMatrixColliderWall22,
				glm::vec3(5.1, 2, 15.2));
		modelMatrixColliderWall22 = glm::translate(
				modelMatrixColliderWall22, modelLargeWall.getObb().c);
		wall22Collider.c = glm::vec3(modelMatrixColliderWall22[3]);
		wall22Collider.e = modelLargeWall.getObb().e * glm::vec3(5.1, 2, 15.2);
		addOrUpdateColliders(collidersOBB, "pared22", wall22Collider, modelMatrixColliderWall22);

		glm::mat4 modelMatrixColliderWall23 = glm::mat4(1.0f);
		modelMatrixColliderWall23[3] = modelMatrixWall23[3];
		AbstractModel::OBB wall23Collider;
		// Set the orientation of collider before doing the scale
		wall23Collider.u = glm::quat_cast(modelMatrixColliderWall23);
		modelMatrixColliderWall23 = glm::scale(modelMatrixColliderWall23,
				glm::vec3(7.1, 2, 21.7));
		modelMatrixColliderWall23 = glm::translate(
				modelMatrixColliderWall23, modelLargeWall.getObb().c);
		wall23Collider.c = glm::vec3(modelMatrixColliderWall23[3]);
		wall23Collider.e = modelLargeWall.getObb().e * glm::vec3(7.1, 2, 21.7);
		addOrUpdateColliders(collidersOBB, "pared23", wall23Collider, modelMatrixColliderWall23);

		glm::mat4 modelMatrixColliderWall24 = glm::mat4(1.0f);
		modelMatrixColliderWall24[3] = modelMatrixWall24[3];
		AbstractModel::OBB wall24Collider;
		// Set the orientation of collider before doing the scale
		wall24Collider.u = glm::quat_cast(modelMatrixColliderWall24);
		modelMatrixColliderWall24 = glm::scale(modelMatrixColliderWall24,
				glm::vec3(7.1, 2, 7));
		modelMatrixColliderWall24 = glm::translate(
				modelMatrixColliderWall24, modelLargeWall.getObb().c);
		wall24Collider.c = glm::vec3(modelMatrixColliderWall24[3]);
		wall24Collider.e = modelLargeWall.getObb().e * glm::vec3(7.1, 2, 7.1);
		addOrUpdateColliders(collidersOBB, "pared24", wall24Collider, modelMatrixColliderWall24);

		glm::mat4 modelMatrixColliderWall25 = glm::mat4(1.0f);
		modelMatrixColliderWall25[3] = modelMatrixWall25[3];
		AbstractModel::OBB wall25Collider;
		// Set the orientation of collider before doing the scale
		wall25Collider.u = glm::quat_cast(modelMatrixColliderWall25);
		modelMatrixColliderWall25 = glm::scale(modelMatrixColliderWall25,
				glm::vec3(6.1, 2, 11.6));
		modelMatrixColliderWall25 = glm::translate(
				modelMatrixColliderWall25, modelLargeWall.getObb().c);
		wall25Collider.c = glm::vec3(modelMatrixColliderWall25[3]);
		wall25Collider.e = modelLargeWall.getObb().e * glm::vec3(6.1, 2, 11.6);
		addOrUpdateColliders(collidersOBB, "pared25", wall25Collider, modelMatrixColliderWall25);

		glm::mat4 modelMatrixColliderWall26 = glm::mat4(1.0f);
		modelMatrixColliderWall26[3] = modelMatrixWall26[3];
		AbstractModel::OBB wall26Collider;
		// Set the orientation of collider before doing the scale
		wall26Collider.u = glm::quat_cast(modelMatrixColliderWall26);
		modelMatrixColliderWall26 = glm::scale(modelMatrixColliderWall26,
				glm::vec3(9.1, 2, 7.5));
		modelMatrixColliderWall26 = glm::translate(
				modelMatrixColliderWall26, modelLargeWall.getObb().c);
		wall26Collider.c = glm::vec3(modelMatrixColliderWall26[3]);
		wall26Collider.e = modelLargeWall.getObb().e * glm::vec3(9.1, 2, 7.5);
		addOrUpdateColliders(collidersOBB, "pared26", wall26Collider, modelMatrixColliderWall26);

		glm::mat4 modelMatrixColliderWall27 = glm::mat4(1.0f);
		modelMatrixColliderWall27[3] = modelMatrixWall27[3];
		AbstractModel::OBB wall27Collider;
		// Set the orientation of collider before doing the scale
		wall27Collider.u = glm::quat_cast(modelMatrixColliderWall27);
		modelMatrixColliderWall27 = glm::scale(modelMatrixColliderWall27,
				glm::vec3(8.4, 2, 5.7));
		modelMatrixColliderWall27 = glm::translate(
				modelMatrixColliderWall27, modelLargeWall.getObb().c);
		wall27Collider.c = glm::vec3(modelMatrixColliderWall27[3]);
		wall27Collider.e = modelLargeWall.getObb().e * glm::vec3(8.4, 2, 5.7);
		addOrUpdateColliders(collidersOBB, "pared27", wall27Collider, modelMatrixColliderWall27);

		glm::mat4 modelMatrixColliderWall28 = glm::mat4(1.0f);
		modelMatrixColliderWall28[3] = modelMatrixWall28[3];
		AbstractModel::OBB wall28Collider;
		// Set the orientation of collider before doing the scale
		wall28Collider.u = glm::quat_cast(modelMatrixColliderWall28);
		modelMatrixColliderWall28 = glm::scale(modelMatrixColliderWall28,
				glm::vec3(7.1, 2, 8.3));
		modelMatrixColliderWall28 = glm::translate(
				modelMatrixColliderWall28, modelLargeWall.getObb().c);
		wall28Collider.c = glm::vec3(modelMatrixColliderWall28[3]);
		wall28Collider.e = modelLargeWall.getObb().e * glm::vec3(7.1, 2, 8.3);
		addOrUpdateColliders(collidersOBB, "pared28", wall28Collider, modelMatrixColliderWall28);

		glm::mat4 modelMatrixColliderWall29 = glm::mat4(1.0f);
		modelMatrixColliderWall29[3] = modelMatrixWall29[3];
		AbstractModel::OBB wall29Collider;
		// Set the orientation of collider before doing the scale
		wall29Collider.u = glm::quat_cast(modelMatrixColliderWall29);
		modelMatrixColliderWall29 = glm::scale(modelMatrixColliderWall29,
				glm::vec3(4.1, 2, 11.1));
		modelMatrixColliderWall29 = glm::translate(
				modelMatrixColliderWall29, modelLargeWall.getObb().c);
		wall29Collider.c = glm::vec3(modelMatrixColliderWall29[3]);
		wall29Collider.e = modelLargeWall.getObb().e * glm::vec3(4.1, 2, 11.1);
		addOrUpdateColliders(collidersOBB, "pared29", wall29Collider, modelMatrixColliderWall29);

		glm::mat4 modelMatrixColliderWall30 = glm::mat4(1.0f);
		modelMatrixColliderWall30[3] = modelMatrixWall30[3];
		AbstractModel::OBB wall30Collider;
		// Set the orientation of collider before doing the scale
		wall30Collider.u = glm::quat_cast(modelMatrixColliderWall30);
		modelMatrixColliderWall30 = glm::scale(modelMatrixColliderWall30,
				glm::vec3(4.1, 2, 11.1));
		modelMatrixColliderWall30 = glm::translate(
				modelMatrixColliderWall30, modelLargeWall.getObb().c);
		wall30Collider.c = glm::vec3(modelMatrixColliderWall30[3]);
		wall30Collider.e = modelLargeWall.getObb().e * glm::vec3(6.1, 2, 11.1);
		addOrUpdateColliders(collidersOBB, "pared30", wall30Collider, modelMatrixColliderWall30);

		glm::mat4 modelMatrixColliderWall31 = glm::mat4(1.0f);
		modelMatrixColliderWall31[3] = modelMatrixWall31[3];
		AbstractModel::OBB wall31Collider;
		// Set the orientation of collider before doing the scale
		wall31Collider.u = glm::quat_cast(modelMatrixColliderWall31);
		modelMatrixColliderWall31 = glm::scale(modelMatrixColliderWall31,
				glm::vec3(8.1, 2, 1.2));
		modelMatrixColliderWall31 = glm::translate(
				modelMatrixColliderWall31, modelLargeWall.getObb().c);
		wall31Collider.c = glm::vec3(modelMatrixColliderWall31[3]);
		wall31Collider.e = modelLargeWall.getObb().e * glm::vec3(8.1, 2, 1.2);
		addOrUpdateColliders(collidersOBB, "pared31", wall31Collider, modelMatrixColliderWall31);

		glm::mat4 modelMatrixColliderWall32 = glm::mat4(1.0f);
		modelMatrixColliderWall32[3] = modelMatrixWall32[3];
		AbstractModel::OBB wall32Collider;
		// Set the orientation of collider before doing the scale
		wall32Collider.u = glm::quat_cast(modelMatrixColliderWall32);
		modelMatrixColliderWall32 = glm::scale(modelMatrixColliderWall32,
				glm::vec3(8.1, 2, 1.2));
		modelMatrixColliderWall32 = glm::translate(
				modelMatrixColliderWall32, modelLargeWall.getObb().c);
		wall32Collider.c = glm::vec3(modelMatrixColliderWall32[3]);
		wall32Collider.e = modelLargeWall.getObb().e * glm::vec3(8.1, 2, 1.2);
		addOrUpdateColliders(collidersOBB, "pared32", wall32Collider, modelMatrixColliderWall32);

		glm::mat4 modelMatrixColliderWall33 = glm::mat4(1.0f);
		modelMatrixColliderWall33[3] = modelMatrixWall33[3];
		AbstractModel::OBB wall33Collider;
		// Set the orientation of collider before doing the scale
		wall33Collider.u = glm::quat_cast(modelMatrixColliderWall33);
		modelMatrixColliderWall33 = glm::scale(modelMatrixColliderWall33,
				glm::vec3(0.6, 2, 7.1));
		modelMatrixColliderWall33 = glm::translate(
				modelMatrixColliderWall33, modelLargeWall.getObb().c);
		wall33Collider.c = glm::vec3(modelMatrixColliderWall33[3]);
		wall33Collider.e = modelLargeWall.getObb().e * glm::vec3(0.6, 2, 7.1);
		addOrUpdateColliders(collidersOBB, "pared33", wall33Collider, modelMatrixColliderWall33);

		glm::mat4 modelMatrixColliderWall34 = glm::mat4(1.0f);
		modelMatrixColliderWall34[3] = modelMatrixWall34[3];
		AbstractModel::OBB wall34Collider;
		// Set the orientation of collider before doing the scale
		wall34Collider.u = glm::quat_cast(modelMatrixColliderWall34);
		modelMatrixColliderWall34 = glm::scale(modelMatrixColliderWall34,
				glm::vec3(100.1, 2, 3.1));
		modelMatrixColliderWall34 = glm::translate(
				modelMatrixColliderWall34, modelLargeWall.getObb().c);
		wall34Collider.c = glm::vec3(modelMatrixColliderWall34[3]);
		wall34Collider.e = modelLargeWall.getObb().e * glm::vec3(100.1, 2, 3.1);
		addOrUpdateColliders(collidersOBB, "pared34", wall34Collider, modelMatrixColliderWall34);

		glm::mat4 modelMatrixColliderWall35 = glm::mat4(1.0f);
		modelMatrixColliderWall35[3] = modelMatrixWall35[3];
		AbstractModel::OBB wall35Collider;
		// Set the orientation of collider before doing the scale
		wall35Collider.u = glm::quat_cast(modelMatrixColliderWall35);
		modelMatrixColliderWall35 = glm::scale(modelMatrixColliderWall35,
				glm::vec3(100.1, 2, 3.1));
		modelMatrixColliderWall35 = glm::translate(
				modelMatrixColliderWall35, modelLargeWall.getObb().c);
		wall35Collider.c = glm::vec3(modelMatrixColliderWall35[3]);
		wall35Collider.e = modelLargeWall.getObb().e * glm::vec3(100.1, 2, 3.1);
		addOrUpdateColliders(collidersOBB, "pared35", wall35Collider, modelMatrixColliderWall35);

		glm::mat4 modelMatrixColliderWall36 = glm::mat4(1.0f);
		modelMatrixColliderWall36[3] = modelMatrixWall36[3];
		AbstractModel::OBB wall36Collider;
		// Set the orientation of collider before doing the scale
		wall36Collider.u = glm::quat_cast(modelMatrixColliderWall36);
		modelMatrixColliderWall36 = glm::scale(modelMatrixColliderWall36,
				glm::vec3(4.1, 2, 100.1));
		modelMatrixColliderWall36 = glm::translate(
				modelMatrixColliderWall36, modelLargeWall.getObb().c);
		wall36Collider.c = glm::vec3(modelMatrixColliderWall36[3]);
		wall36Collider.e = modelLargeWall.getObb().e * glm::vec3(4.1, 2, 100.1);
		addOrUpdateColliders(collidersOBB, "pared36", wall36Collider, modelMatrixColliderWall36);

		glm::mat4 modelMatrixColliderWall37 = glm::mat4(1.0f);
		modelMatrixColliderWall37[3] = modelMatrixWall37[3];
		AbstractModel::OBB wall37Collider;
		// Set the orientation of collider before doing the scale
		wall37Collider.u = glm::quat_cast(modelMatrixColliderWall37);
		modelMatrixColliderWall37 = glm::scale(modelMatrixColliderWall37,
				glm::vec3(4.1, 2, 100.1));
		modelMatrixColliderWall37 = glm::translate(
				modelMatrixColliderWall37, modelLargeWall.getObb().c);
		wall37Collider.c = glm::vec3(modelMatrixColliderWall37[3]);
		wall37Collider.e = modelLargeWall.getObb().e * glm::vec3(4.1, 2, 100.1);
		addOrUpdateColliders(collidersOBB, "pared37", wall37Collider, modelMatrixColliderWall37);
        
		glm::mat4 modelMatrixColliderWall38 = glm::mat4(1.0f);
		modelMatrixColliderWall38[3] = modelMatrixWall38[3];
		AbstractModel::OBB wall38Collider;
		// Set the orientation of collider before doing the scale
		wall38Collider.u = glm::quat_cast(modelMatrixColliderWall38);
		modelMatrixColliderWall38 = glm::scale(modelMatrixColliderWall38,
				glm::vec3(25.6, 2, 0.5));
		modelMatrixColliderWall38 = glm::translate(
				modelMatrixColliderWall38, modelLargeWall.getObb().c);
		wall38Collider.c = glm::vec3(modelMatrixColliderWall38[3]);
		wall38Collider.e = modelLargeWall.getObb().e * glm::vec3(25.6, 2, 0.5);
		addOrUpdateColliders(collidersOBB, "pared38", wall38Collider, modelMatrixColliderWall38);

        glm::mat4 modelMatrixColliderWall39 = glm::mat4(1.0f);
		modelMatrixColliderWall39[3] = modelMatrixWall39[3];
		AbstractModel::OBB wall39Collider;
		// Set the orientation of collider before doing the scale
		wall39Collider.u = glm::quat_cast(modelMatrixColliderWall39);
		modelMatrixColliderWall39 = glm::scale(modelMatrixColliderWall39,
				glm::vec3(10, 2, 0.5));
		modelMatrixColliderWall39 = glm::translate(
				modelMatrixColliderWall39, modelLargeWall.getObb().c);
		wall39Collider.c = glm::vec3(modelMatrixColliderWall39[3]);
		wall39Collider.e = modelLargeWall.getObb().e * glm::vec3(0.5, 2, 8);
		addOrUpdateColliders(collidersOBB, "pared39", wall39Collider, modelMatrixColliderWall39);

        glm::mat4 modelMatrixColliderWall40 = glm::mat4(1.0f);
		modelMatrixColliderWall40[3] = modelMatrixWall40[3];
		AbstractModel::OBB wall40Collider;
		// Set the orientation of collider before doing the scale
		wall40Collider.u = glm::quat_cast(modelMatrixColliderWall40);
		modelMatrixColliderWall40 = glm::scale(modelMatrixColliderWall40,
				glm::vec3(7, 2, 0.5));
		modelMatrixColliderWall40 = glm::translate(
				modelMatrixColliderWall40, modelLargeWall.getObb().c);
		wall40Collider.c = glm::vec3(modelMatrixColliderWall40[3]);
		wall40Collider.e = modelLargeWall.getObb().e * glm::vec3(7, 2, 0.5);
		addOrUpdateColliders(collidersOBB, "pared40", wall40Collider, modelMatrixColliderWall40);

		glm::mat4 modelMatrixColliderWall41 = glm::mat4(1.0f);
		modelMatrixColliderWall41[3] = modelMatrixWall41[3];
		AbstractModel::OBB wall41Collider;
		// Set the orientation of collider before doing the scale
		wall41Collider.u = glm::quat_cast(modelMatrixColliderWall41);
		modelMatrixColliderWall41 = glm::scale(modelMatrixColliderWall41,
				glm::vec3(8, 2, 0.5));
		modelMatrixColliderWall41 = glm::translate(
				modelMatrixColliderWall41, modelLargeWall.getObb().c);
		wall41Collider.c = glm::vec3(modelMatrixColliderWall41[3]);
		wall41Collider.e = modelLargeWall.getObb().e * glm::vec3(8, 2, 0.5);
		addOrUpdateColliders(collidersOBB, "pared41", wall41Collider, modelMatrixColliderWall41);
		
		//sphere colliders

		for (int i = 0; i < spherePosition.size(); i++){
			if(spheresCollisions[i] == false)
			{
			AbstractModel::SBB sphereCollider;
			glm::mat4 modelMatrixColliderSphere = glm::mat4(1.0);
			modelMatrixColliderSphere = glm::translate(modelMatrixColliderSphere, spherePosition[i]);
			addOrUpdateColliders(collidersSBB, "sphere-" + std::to_string(i), sphereCollider, modelMatrixColliderSphere);
			// Set the orientation of collider before doing the scale
			modelMatrixColliderSphere = glm::scale(modelMatrixColliderSphere, glm::vec3(0.5, 0.5, 0.5));
			modelMatrixColliderSphere = glm::translate(modelMatrixColliderSphere, modelSphere.getSbb().c);
			sphereCollider.c = glm::vec3(modelMatrixColliderSphere[3]);
			sphereCollider.ratio = modelSphere.getSbb().ratio * 0.5;
			std::get<0>(collidersSBB.find("sphere-" + std::to_string(i))->second) = sphereCollider;
			}
		}

		for (int i = 0; i < powerUpPosition.size(); i++){
			if(powerUpCollisions[i] == false)
			{
			AbstractModel::SBB powerUpCollider;
			glm::mat4 modelMatrixColliderPowerUp = glm::mat4(1.0);
			modelMatrixColliderPowerUp = glm::translate(modelMatrixColliderPowerUp, powerUpPosition[i]);
			addOrUpdateColliders(collidersSBB, "powerUp-" + std::to_string(i), powerUpCollider, modelMatrixColliderPowerUp);
			// Set the orientation of collider before doing the scale
			modelMatrixColliderPowerUp = glm::scale(modelMatrixColliderPowerUp, glm::vec3(1, 1, 1));
			modelMatrixColliderPowerUp = glm::translate(modelMatrixColliderPowerUp, modelSphere.getSbb().c);
			powerUpCollider.c = glm::vec3(modelMatrixColliderPowerUp[3]);
			powerUpCollider.ratio = modelSphere.getSbb().ratio * 1.0;
			std::get<0>(collidersSBB.find("powerUp-" + std::to_string(i))->second) = powerUpCollider;
			}
		}


		// Collider de pacman
		AbstractModel::OBB mayowCollider;
		glm::mat4 modelmatrixColliderMayow = glm::mat4(modelMatrixMayow);
		modelmatrixColliderMayow = glm::rotate(modelmatrixColliderMayow,
				glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Set the orientation of collider before doing the scale
		mayowCollider.u = glm::quat_cast(modelmatrixColliderMayow);
		//modelmatrixColliderMayow = glm::scale(modelmatrixColliderMayow, glm::vec3(0.021, 0.021, 0.021));
		modelmatrixColliderMayow = glm::scale(modelmatrixColliderMayow, glm::vec3(0.25, 0.4, 0.5));
		modelmatrixColliderMayow = glm::translate(modelmatrixColliderMayow,
				glm::vec3(mayowModelAnimate.getObb().c.x,
						mayowModelAnimate.getObb().c.y,
						mayowModelAnimate.getObb().c.z));
		mayowCollider.e = mayowModelAnimate.getObb().e * glm::vec3(0.25, 0.4, 0.5) * glm::vec3(0.787401574, 0.787401574, 0.787401574);
		mayowCollider.c = glm::vec3(modelmatrixColliderMayow[3]);
		addOrUpdateColliders(collidersOBB, "mayow", mayowCollider, modelMatrixMayow);

		// Collider de Blinky
		AbstractModel::SBB GhostRedCollider;
		glm::mat4 modelmatrixColliderGhostRed = glm::mat4(modelMatrixGhostRed);
		modelmatrixColliderGhostRed[3][1] -= 0.3;
		// Set the orientation of collider before doing the scale
		modelmatrixColliderGhostRed = glm::scale(modelmatrixColliderGhostRed, glm::vec3(1.4, 1.4, 1.4));
		modelmatrixColliderGhostRed = glm::translate(modelmatrixColliderGhostRed,
				glm::vec3(modelGhostRed.getSbb().c.x,
						modelGhostRed.getSbb().c.y,
						modelGhostRed.getSbb().c.z));
		GhostRedCollider.ratio = modelGhostRed.getSbb().ratio * 1.4;
		GhostRedCollider.c = glm::vec3(modelmatrixColliderGhostRed[3]);
		addOrUpdateColliders(collidersSBB, "blinky", GhostRedCollider, modelMatrixGhostRed);

		// Collider de Pinky
		AbstractModel::SBB GhostPinkCollider;
		glm::mat4 modelmatrixColliderGhostPink = glm::mat4(modelMatrixGhostPink);
		modelmatrixColliderGhostPink[3][1] -= 0.3;
		// Set the orientation of collider before doing the scale
		modelmatrixColliderGhostPink = glm::scale(modelmatrixColliderGhostPink, glm::vec3(1.4, 1.4, 1.4));
		modelmatrixColliderGhostPink = glm::translate(modelmatrixColliderGhostPink,
				glm::vec3(modelGhostPink.getSbb().c.x,
						modelGhostPink.getSbb().c.y,
						modelGhostPink.getSbb().c.z));
		GhostPinkCollider.ratio = modelGhostPink.getSbb().ratio * 1.4;
		GhostPinkCollider.c = glm::vec3(modelmatrixColliderGhostPink[3]);
		addOrUpdateColliders(collidersSBB, "pinky", GhostPinkCollider, modelMatrixGhostPink);

		// Collider de Inky
		AbstractModel::SBB GhostBlueCollider;
		glm::mat4 modelmatrixColliderGhostBlue = glm::mat4(modelMatrixGhostBlue);
		modelmatrixColliderGhostBlue[3][1] -= 0.3;
		// Set the orientation of collider before doing the scale
		modelmatrixColliderGhostBlue = glm::scale(modelmatrixColliderGhostBlue, glm::vec3(1.4, 1.4, 1.4));
		modelmatrixColliderGhostBlue = glm::translate(modelmatrixColliderGhostBlue,
				glm::vec3(modelGhostBlue.getSbb().c.x,
						modelGhostBlue.getSbb().c.y,
						modelGhostBlue.getSbb().c.z));
		GhostBlueCollider.ratio = modelGhostBlue.getSbb().ratio * 1.4;
		GhostBlueCollider.c = glm::vec3(modelmatrixColliderGhostBlue[3]);
		addOrUpdateColliders(collidersSBB, "inky", GhostBlueCollider, modelMatrixGhostBlue);

		// Collider de Clyde
		AbstractModel::SBB GhostOrangeCollider;
		glm::mat4 modelmatrixColliderGhostOrange = glm::mat4(modelMatrixGhostOrange);
		modelmatrixColliderGhostOrange[3][1] -= 0.3;
		// Set the orientation of collider before doing the scale
		modelmatrixColliderGhostOrange = glm::scale(modelmatrixColliderGhostOrange, glm::vec3(1.4, 1.4, 1.4));
		modelmatrixColliderGhostOrange = glm::translate(modelmatrixColliderGhostOrange,
				glm::vec3(modelGhostOrange.getSbb().c.x,
						modelGhostOrange.getSbb().c.y,
						modelGhostOrange.getSbb().c.z));
		GhostOrangeCollider.ratio = modelGhostOrange.getSbb().ratio * 1.4;
		GhostOrangeCollider.c = glm::vec3(modelmatrixColliderGhostOrange[3]);
		addOrUpdateColliders(collidersSBB, "clyde", GhostOrangeCollider, modelMatrixGhostOrange);

		/*******************************************
		 * Render de colliders
		 *******************************************/
		/*
		for (std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator it =
				collidersOBB.begin(); it != collidersOBB.end(); it++) {
			glm::mat4 matrixCollider = glm::mat4(1.0);
			matrixCollider = glm::translate(matrixCollider, std::get<0>(it->second).c);
			matrixCollider = matrixCollider * glm::mat4(std::get<0>(it->second).u);
			matrixCollider = glm::scale(matrixCollider, std::get<0>(it->second).e * 2.0f);
			boxCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
			boxCollider.enableWireMode();
			boxCollider.render(matrixCollider);
		}
		
		for (std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it =
				collidersSBB.begin(); it != collidersSBB.end(); it++) {
			glm::mat4 matrixCollider = glm::mat4(1.0);
			matrixCollider = glm::translate(matrixCollider, std::get<0>(it->second).c);
			matrixCollider = glm::scale(matrixCollider, glm::vec3(std::get<0>(it->second).ratio * 2.0f));
			sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
			sphereCollider.enableWireMode();
			sphereCollider.render(matrixCollider);
		}*/

		/**********Render de transparencias***************/
		renderAlphaScene();

		/*********************Prueba de colisiones****************************/
		for (std::map<std::string,
			std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4>>::iterator it =
			collidersSBB.begin(); it != collidersSBB.end(); it++) {
			bool isCollision = false;
			for (std::map<std::string,
				std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4>>::iterator jt =
				collidersSBB.begin(); jt != collidersSBB.end(); jt++) {
				if (it != jt && testSphereSphereIntersection(
					std::get<0>(it->second), std::get<0>(jt->second))) {
					//std::cout << "Hay collision entre " << it->first <<
					//	" y el modelo " << jt->first << std::endl;
					isCollision = true;
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isCollision);
		}

		for (std::map<std::string,
			std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4>>::iterator it =
			collidersOBB.begin(); it != collidersOBB.end(); it++) {
			bool isColision = false;
			for (std::map<std::string,
				std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4>>::iterator jt =
				collidersOBB.begin(); jt != collidersOBB.end(); jt++) {
				if (it != jt && 
					testOBBOBB(std::get<0>(it->second), std::get<0>(jt->second))) {
					//std::cout << "Hay colision entre " << it->first << " y el modelo" <<
					//	jt->first << std::endl;
					isColision = true;
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isColision);
		}

		for (std::map<std::string,
			std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4>>::iterator it =
			collidersSBB.begin(); it != collidersSBB.end(); it++) {
			bool isCollision = false;
			for (std::map<std::string,
				std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4>>::iterator jt =
				collidersOBB.begin(); jt != collidersOBB.end(); jt++) {
				if (testSphereOBox(std::get<0>(it->second), std::get<0>(jt->second))) {
					if(it->first == "blinky" || it->first == "pinky" || it->first == "inky" || it->first == "clyde"){
						if(jt->first == "mayow" && !powerUp){
							reset_player = true;
							alSourcePlay(source[2]);
						}
						else{
							if(jt->first == "mayow" && powerUp && it->first == "blinky")
								{
									reset_blinky = true;
									score += 300;
									alSourcePlay(source[3]);
									powerUp = false;
								}
							if(jt->first == "mayow" && powerUp && it->first == "pinky")
								{
									reset_pinky = true;
									score += 300;
									alSourcePlay(source[3]);
									powerUp = false;
								}
							if(jt->first == "mayow" && powerUp && it->first == "inky")
								{
									reset_inky = true;
									score += 300;
									alSourcePlay(source[3]);
									powerUp = false;
								}
							if(jt->first == "mayow" && powerUp && it->first == "clyde")
								{
									reset_clyde = true;
									score += 300;
									alSourcePlay(source[3]);
									powerUp = false;
								}		
						}
					}
					else{
						    //std::cout << "ELSE" << std::endl;
							std::regex regex(R"((\w+)-(\d+))");
							std::smatch match;
							std::string palabra;
							int posicion;
							if(std::regex_search(it->first, match, regex))
							{
								palabra = match[1].str();
								posicion = std::stoi(match[2].str());
							}
							//std::cout << palabra << " Palabra" << std::endl;
							//std::cout << posicion << " Posicion" << std::endl;
							if(palabra == "powerUp"){
								if(jt->first == "mayow"){
									powerUp = true;
									score += 200;
									powerUpCollisions[posicion] = true;
									collidersSBB.erase(it);
									spheres_to_win--;
									std::cout << spheres_to_win << std::endl;
								}
							}
							else if(palabra == "sphere"){
								if(jt->first == "mayow"){
									std::cout << posicion << " Posicion" << std::endl;
									//std::cout << it->first << " Nombre de IT" << std::endl;
									//isCollision = false;
							    	score += 100;
									spheresCollisions[posicion] = true;
									collidersSBB.erase(it);
									spheres_to_win--;
									std::cout << spheres_to_win << std::endl;
							    	//collidersSBB.empty(it);
								}
							}
					}
					addOrUpdateCollisionDetection(collisionDetection, jt->first, true);
				}
			}
			isCollision = false;
			addOrUpdateCollisionDetection(collisionDetection, it->first, isCollision);
		}

		std::map<std::string, bool>::iterator itCollision;
		for (itCollision = collisionDetection.begin(); 
			itCollision != collisionDetection.end(); itCollision++) {
			std::map<std::string, std::tuple<AbstractModel::SBB, 
				glm::mat4, glm::mat4>>::iterator sbbBuscado = 
				collidersSBB.find(itCollision->first);
			std::map<std::string, std::tuple<AbstractModel::OBB,
				glm::mat4, glm::mat4>>::iterator obbBuscado =
				collidersOBB.find(itCollision->first);
			if (sbbBuscado != collidersSBB.end()) {
				if (!itCollision->second) 
					addOrUpdateColliders(collidersSBB, itCollision->first);
			}
			if (obbBuscado != collidersOBB.end()) {
				if (!itCollision->second) 
					addOrUpdateColliders(collidersOBB, itCollision->first);
				else {
					if (itCollision->first.compare("mayow") == 0)
						modelMatrixMayow = std::get<1>(obbBuscado->second);
				}
			}
		}

		/*std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4>>::
			iterator itOBB;
		for (itOBB = collidersOBB.begin(); itOBB != collidersOBB.end(); itOBB++) {
			if (testRayOBB(ori, targetRay, std::get<0>(itOBB->second))) {
				std::cout << "Collision del rayo con el modelo " << itOBB->first
					<< std::endl;
			}
		}*/

		// Esto es para ilustrar la transformacion inversa de los coliders
		/*glm::vec3 cinv = glm::inverse(mayowCollider.u) * glm::vec4(rockCollider.c, 1.0);
		glm::mat4 invColliderS = glm::mat4(1.0);
		invColliderS = glm::translate(invColliderS, cinv);
		invColliderS =  invColliderS * glm::mat4(mayowCollider.u);
		invColliderS = glm::scale(invColliderS, glm::vec3(rockCollider.ratio * 2.0, rockCollider.ratio * 2.0, rockCollider.ratio * 2.0));
		sphereCollider.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		sphereCollider.enableWireMode();
		sphereCollider.render(invColliderS);
		glm::vec3 cinv2 = glm::inverse(mayowCollider.u) * glm::vec4(mayowCollider.c, 1.0);
		glm::mat4 invColliderB = glm::mat4(1.0);
		invColliderB = glm::translate(invColliderB, cinv2);
		invColliderB = glm::scale(invColliderB, mayowCollider.e * 2.0f);
		boxCollider.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		boxCollider.enableWireMode();
		boxCollider.render(invColliderB);
		// Se regresa el color blanco
		sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
		boxCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));*/
		
		// Animaciones por keyframes dart Vader
		// Para salvar los keyframes
		
		/**********Maquinas de estado*************/
		// Maquina de estados para el carro eclipse

		switch (state){
		case 0:
			if(numberAdvance == 0){
				maxAdvance = 13.6;
				direction = -1;
			}
			else if(numberAdvance == 1){
				maxAdvance = 8.6;
				direction = -1;
			}
			else if(numberAdvance == 2){
				maxAdvance = 19;
				direction = -1;
			}
			else if(numberAdvance == 3){
				maxAdvance = 23.5;
				direction = 1;
			}
			else if(numberAdvance == 4){
				maxAdvance = 11.2;
				direction = 1;
			}
			else if(numberAdvance == 5){
				maxAdvance = 68.7;
				direction = -1;
			}
			else if(numberAdvance == 6){
				maxAdvance = 35.2;
				direction = -1;
			}
			else if(numberAdvance == 7){
				maxAdvance = 20.2;
				direction = -1;
			}
			else if(numberAdvance == 8){
				maxAdvance = 54.2;
				direction = -1;
			}
			else if(numberAdvance == 9){
				maxAdvance = 20.2;
				direction = -1;
			}
			else if(numberAdvance == 10){
				maxAdvance = 18.2;
				direction = -1;
			}
			else if(numberAdvance == 11){
				maxAdvance = 36.8;
				direction = 1;
			}
			else if(numberAdvance == 12){
				maxAdvance = 34.2;
				direction = 1;
			}
			else if(numberAdvance == 13){
				maxAdvance = 16.2;
				direction = 1;
			}
			else if(numberAdvance == 14){
				maxAdvance = 54.2;
				direction = -1;
			}
			else if(numberAdvance == 15){
				maxAdvance = 20.2;
				direction = -1;
			}
			else if(numberAdvance == 16){
				maxAdvance = 19.8;
				direction = -1;
			}
			else if(numberAdvance == 17){
				maxAdvance = 85.4;
				direction = -1;
			}
			else if(numberAdvance == 18){
				maxAdvance = 20.2;
				direction = -1;
			}
			else if(numberAdvance == 19){
				maxAdvance = 16.2;
				direction = -1;
			}
			else if(numberAdvance == 20){
				maxAdvance = 21.6;
				direction = 1;
			}
			state = 1;
			break;
		case 1:
			modelMatrixGhostRed = glm::translate(modelMatrixGhostRed, glm::vec3(0.0f, 0.45f, 0.0f));
			//modelMatrixGhostRed = glm::rotate(modelMatrixGhostRed, glm::radians(-90.0f), glm::vec3(0, 1, 0));
			advanceCount += 0.45;
			if(advanceCount > maxAdvance){
				advanceCount = 0;
				numberAdvance++;
				state = 2;
			}
			break;
		case 2:
			modelMatrixGhostRed = glm::rotate(modelMatrixGhostRed, glm::radians(giroFantasma), glm::vec3(0, 0, 1 * direction));
			rotCount += giroFantasma;
			if(rotCount >= 90.0f){
				rotCount = 0;
				state = 0;
				if(numberAdvance > 20)
					numberAdvance = 5;
			}
			break;
		
		default:
			break;
		}

		switch (Inky){
		case 0:
			if(numberAdvanceI == 0){
				maxAdvanceI = 13.6;
				directionI = -1;
			}
			else if(numberAdvanceI == 1){
				maxAdvanceI = 13.6;
				directionI = -1;
			}
			else if(numberAdvanceI == 2){
				maxAdvanceI = 19;
				directionI = -1;
			}
			else if(numberAdvanceI == 3){
				maxAdvanceI = 23.5;
				directionI = 1;
			}
			else if(numberAdvanceI == 4){
				maxAdvanceI = 12.5;
				directionI = -1;
			}
			else if(numberAdvanceI == 5){
				maxAdvanceI = 37;
				directionI = 1;
			}
			else if(numberAdvanceI == 6){
				maxAdvanceI = 14.4;
				directionI = 1;
			}
			else if(numberAdvanceI == 7){
				maxAdvanceI = 14;
				directionI = -1;
			}
			else if(numberAdvanceI == 8){
				maxAdvanceI = 19.8;
				directionI = 1;
			}
			else if(numberAdvanceI == 9){
				maxAdvanceI = 23;
				directionI = 1;
			}
			else if(numberAdvanceI == 10){
				maxAdvanceI = 55.4;
				directionI = 1;
			}
			else if(numberAdvanceI == 11){
				maxAdvanceI = 16.8;
				directionI = 1;
			}
			else if(numberAdvanceI == 12){
				maxAdvanceI = 7.2;
				directionI = -1;
			}
			else if(numberAdvanceI == 13){
				maxAdvanceI = 26.2;
				directionI = -1;
			}
			else if(numberAdvanceI == 14){
				maxAdvanceI = 12.2;
				directionI = 1;
			}
			else if(numberAdvanceI == 15){
				maxAdvanceI = 14.2;
				directionI = 1;
			}
			else if(numberAdvanceI == 16){
				maxAdvanceI = 60.4;
				directionI = 1;
			}
			else if(numberAdvanceI == 17){
				maxAdvanceI = 19;
				directionI = 1;
			}
			else if(numberAdvanceI == 18){
				maxAdvanceI = 33.2;
				directionI = -1;
			}
			else if(numberAdvanceI == 19){
				maxAdvanceI = 20.2;
				directionI = 1;
			}
			else if(numberAdvanceI == 20){
				maxAdvanceI = 22.6;
				directionI = -1;
			}
			else if(numberAdvanceI == 21){
				maxAdvanceI = 17;
				directionI = -1;
			}
			else if(numberAdvanceI == 22){
				maxAdvanceI = 22;
				directionI = -1;
			}
			Inky = 1;
			break;
		case 1:
			modelMatrixGhostBlue = glm::translate(modelMatrixGhostBlue, glm::vec3(0.0f, 0.4f, 0.0f));
			//modelMatrixGhostRed = glm::rotate(modelMatrixGhostRed, glm::radians(-90.0f), glm::vec3(0, 1, 0));
			advanceCountI += 0.4;
			if(advanceCountI > maxAdvanceI){
				advanceCountI = 0;
				numberAdvanceI++;
				Inky = 2;
			}
			break;
		case 2:
			modelMatrixGhostBlue = glm::rotate(modelMatrixGhostBlue, glm::radians(giroFantasma), glm::vec3(0, 0, 1 * directionI));
			rotCountI += giroFantasma;
			if(rotCountI >= 90.0f){
				rotCountI = 0;
				Inky = 0;
				if(numberAdvanceI > 22)
					numberAdvanceI = 5;
			}
			break;
		
		default:
			break;
		}

		switch (Pinky){
		case 0:
			if(numberAdvanceP == 0){
				maxAdvanceP = 3.6;
				directionP = 1;
			}
			else if(numberAdvanceP == 1){
				maxAdvanceP = 8.6;
				directionP = 1;
			}
			else if(numberAdvanceP == 2){
				maxAdvanceP = 18.9;
				directionP = 1;
			}
			else if(numberAdvanceP == 3){
				maxAdvanceP = 23.5;
				directionP = -1;
			}
			else if(numberAdvanceP == 4){
				maxAdvanceP = 14.95;
				directionP = -1;
			}
			else if(numberAdvanceP == 5){
				maxAdvanceP = 48.7;
				directionP = -1;
			}
			else if(numberAdvanceP == 6){
				maxAdvanceP = 48.2;
				directionP = -1;
			}
			else if(numberAdvanceP == 7){
				maxAdvanceP = 18;
				directionP = -1;
			}
			else if(numberAdvanceP == 8){
				maxAdvanceP = 10;
				directionP = 1;
			}
			else if(numberAdvanceP == 9){
				maxAdvanceP = 7;
				directionP = -1;
			}
			else if(numberAdvanceP == 10){
				maxAdvanceP = 10;
				directionP = -1;
			}
			else if(numberAdvanceP == 11){
				maxAdvanceP = 7;
				directionP = 1;
			}
			else if(numberAdvanceP == 12){
				maxAdvanceP = 11.5;
				directionP = -1;
			}
			else if(numberAdvanceP == 13){
				maxAdvanceP = 18.4;
				directionP = 1;
			}
			else if(numberAdvanceP == 14){
				maxAdvanceP = 40.2;
				directionP = -1;
			}
			else if(numberAdvanceP == 15){
				maxAdvanceP = 20.2;
				directionP = -1;
			}
			else if(numberAdvanceP == 16){
				maxAdvanceP = 23;
				directionP = -1;
			}
			else if(numberAdvanceP == 17){
				maxAdvanceP = 40;
				directionP = -1;
			}
			else if(numberAdvanceP == 18){
				maxAdvanceP = 23.7;
				directionP = -1;
			}
			else if(numberAdvanceP == 19){
				maxAdvanceP = 40.5;
				directionP = -1;
			}
			else if(numberAdvanceP == 20){
				maxAdvanceP = 49.2;
				directionP = -1;
			}
			else if(numberAdvanceP == 21){
				maxAdvanceP = 20.2;
				directionP = -1;
			}
			else if(numberAdvanceP == 22){
				maxAdvanceP = 9.2;
				directionP = 1;
			}
			else if(numberAdvanceP == 23){
				maxAdvanceP = 18.4;
				directionP = 1;
			}
			else if(numberAdvanceP == 24){
				maxAdvanceP = 10;
				directionP = -1;
			}
			else if(numberAdvanceP == 25){
				maxAdvanceP = 7.2;
				directionP = -1;
			}
			else if(numberAdvanceP == 26){
				maxAdvanceP = 13;
				directionP = 1;
			}
			Pinky = 1;
			break;
		case 1:
			modelMatrixGhostPink = glm::translate(modelMatrixGhostPink, glm::vec3(0.0f, 0.3f, 0.0f));
			//modelMatrixGhostRed = glm::rotate(modelMatrixGhostRed, glm::radians(-90.0f), glm::vec3(0, 1, 0));
			advanceCountP += 0.3;
			if(advanceCountP > maxAdvanceP){
				advanceCountP = 0;
				numberAdvanceP++;
				Pinky = 2;
			}
			break;
		case 2:
			modelMatrixGhostPink = glm::rotate(modelMatrixGhostPink, glm::radians(giroFantasma), glm::vec3(0, 0, 1 * directionP));
			rotCountP += giroFantasma;
			if(rotCountP >= 90.0f){
				rotCountP = 0;
				Pinky = 0;
				if(numberAdvanceP > 26)
					numberAdvanceP = 3;
			}
			break;
		
		default:
			break;
		}
		

		switch (Clyde){
		case 0:
			if(numberAdvanceC == 0){
				maxAdvanceC = 3.5;
				directionC = 1;
			}
			else if(numberAdvanceC == 1){
				maxAdvanceC = 13.5;
				directionC = 1;
			}
			else if(numberAdvanceC == 2){
				maxAdvanceC = 19;
				directionC = 1;
			}
			else if(numberAdvanceC == 3){
				maxAdvanceC = 24;
				directionC = -1;
			}
			else if(numberAdvanceC == 4){
				maxAdvanceC = 13.95;
				directionC = 1;
			}
			else if(numberAdvanceC == 5){
				maxAdvanceC = 40.7;
				directionC = -1;
			}
			else if(numberAdvanceC == 6){
				maxAdvanceC = 22.5;
				directionC = 1;
			}
			else if(numberAdvanceC == 7){
				maxAdvanceC = 14;
				directionC = 1;
			}
			else if(numberAdvanceC == 8){
				maxAdvanceC = 45;
				directionC = 1;
			}
			else if(numberAdvanceC == 9){
				maxAdvanceC = 13;
				directionC = 1;
			}
			else if(numberAdvanceC == 10){
				maxAdvanceC = 10.5;
				directionC = -1;
			}
			else if(numberAdvanceC == 11){
				maxAdvanceC = 25;
				directionC = -1;
			}
			else if(numberAdvanceC == 12){
				maxAdvanceC = 18.7;
				directionC = 1;
			}
			else if(numberAdvanceC == 13){
				maxAdvanceC = 16.5;
				directionC = 1;
			}
			else if(numberAdvanceC == 14){
				maxAdvanceC = 54;
				directionC = 1;
			}
			else if(numberAdvanceC == 15){
				maxAdvanceC = 16;
				directionC = 1;
			}
			else if(numberAdvanceC == 16){
				maxAdvanceC = 9;
				directionC = -1;
			}
			else if(numberAdvanceC == 17){
				maxAdvanceC = 25;
				directionC = 1;
			}
			else if(numberAdvanceC == 18){
				maxAdvanceC = 14;
				directionC = 1;
			}
			else if(numberAdvanceC == 19){
				maxAdvanceC = 25;
				directionC = -1;
			}
			else if(numberAdvanceC == 20){
				maxAdvanceC = 30;
				directionC = 1;
			}
			else if(numberAdvanceC == 21){
				maxAdvanceC = 16;
				directionC = 1;
			}
			else if(numberAdvanceC == 22){
				maxAdvanceC = 31.5;
				directionC = 1;
			}
			Clyde = 1;
			break;
		case 1:
			modelMatrixGhostOrange = glm::translate(modelMatrixGhostOrange, glm::vec3(0.0f, 0.45f, 0.0f));
			//modelMatrixGhostRed = glm::rotate(modelMatrixGhostRed, glm::radians(-90.0f), glm::vec3(0, 1, 0));
			advanceCountC += 0.45;
			if(advanceCountC > maxAdvanceC){
				advanceCountC = 0;
				numberAdvanceC++;
				Clyde = 2;
			}
			break;
		case 2:
			modelMatrixGhostOrange = glm::rotate(modelMatrixGhostOrange, glm::radians(giroFantasma), glm::vec3(0, 0, 1 * directionC));
			rotCountC += giroFantasma;
			if(rotCountC >= 90.0f){
				rotCountC = 0;
				Clyde = 0;
				if(numberAdvanceC > 22)
					numberAdvanceC = 5;
			}
			break;
		
		default:
			break;
		}
		


		// Constantes de animaciones
		animationMayowIndex = 1;

		glfwSwapBuffers(window);

		/****************************+
		 * Open AL sound data
		 */

		source1Pos[0] = modelMatrixMayow[3].x;
		source1Pos[1] = modelMatrixMayow[3].y;
		source1Pos[2] = modelMatrixMayow[3].z;
		alSourcefv(source[1], AL_POSITION, source1Pos);

		// Listener for the Thris person camera
		listenerPos[0] = modelMatrixMayow[3].x;
		listenerPos[1] = modelMatrixMayow[3].y;
		listenerPos[2] = modelMatrixMayow[3].z;
		alListenerfv(AL_POSITION, listenerPos);

		glm::vec3 upModel = glm::normalize(modelMatrixMayow[1]);
		glm::vec3 frontModel = glm::normalize(modelMatrixMayow[2]);

		listenerOri[0] = frontModel.x;
		listenerOri[1] = frontModel.y;
		listenerOri[2] = frontModel.z;
		listenerOri[3] = upModel.x;
		listenerOri[4] = upModel.y;
		listenerOri[5] = upModel.z;

		// Listener for the First person camera
		// listenerPos[0] = camera->getPosition().x;
		// listenerPos[1] = camera->getPosition().y;
		// listenerPos[2] = camera->getPosition().z;
		// alListenerfv(AL_POSITION, listenerPos);
		// listenerOri[0] = camera->getFront().x;
		// listenerOri[1] = camera->getFront().y;
		// listenerOri[2] = camera->getFront().z;
		// listenerOri[3] = camera->getUp().x;
		// listenerOri[4] = camera->getUp().y;
		// listenerOri[5] = camera->getUp().z;
		alListenerfv(AL_ORIENTATION, listenerOri);

		//alSourcePlay(source[0]);
		//alSourcePlay(source[1]);
	}
}

int main(int argc, char **argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}
