/**
 * @file game/gameprogram.h
 * @author Marko Silokunnas
 */

#ifndef GAMEPROGRAM_H_
#define GAMEPROGRAM_H_

#include <SDL/SDL.h>
#include "gamewindow.h"
#include "gameobject.h"
#include "keyboardcontroller.h"

#include "configuration/configuration.h"

#include "sound/mixer.h"

#include <geometry/sphere.h>

#include <graphics/resourcemanager.h>
#include <graphics/programmanager.h>
#include <graphics/mesh.h>
#include <graphics/texture.h>
#include <graphics/vertexbuffer.h>

class Device;
class Effect;
class VertexFormat;

class Extents3;

// TODO: quick & dirty
class CameraNode;
class DrawParams;
class Node;

typedef ResourceManager<Mesh> MeshManager;
typedef ResourceManager<Texture> TextureManager;
typedef ResourceManager<VertexBuffer> VertexBufferManager;

struct Bullet
{
    float life;
    Sphere shape;
    Vector3 velocity;
    Node* visual;
};

/**
 * The 'main' class of the game. Does event handling for keyboard and mouse
 * events. Contains the main loop of the game as well.
 */
class GameProgram : public GameWindow {
public:
	GameProgram();

	/**
	 *
	 * Starts executing the main loop of the program.
	 *
	 * @return int returns 0 on clean exit and non-zero on forced exit (eg. an
	 * 			error occured. )
	 */
	int execute();

	/**
	 *
	 * Renders the scene
	 *
	 */
	void render();

	/**
	 *
	 * Event handling. TODO: write a better comment :P
	 *
	 * @param event event to handle
	 */
	void handleEvent( const SDL_Event* const event );

	/**
	 *
	 * handles key presses.
	 *
	 * @param keysym keysym of the pressed key
	 */
	void handleKeyPresses( const SDL_keysym keysym );

	/**
	 *
	 * one 'tick' in the game simulation
	 * @param deltaTime frame independent modifier for movement of
     *                        objects
	 */
	 virtual void tick( const float deltaTime );

	/**
	 *
	 * destructor
	 */
	virtual ~GameProgram();

	/**
	 *
	 * getter for member variable 'running'
	 *
	 * @return bool
	 */
	inline bool isRunning() const { return running; };

	/**
	 *
	 * setter for member variable 'running'
	 *
	 * @param value new value for the member variable.
	 */
	void setRunning( bool value ) { this->running = value; }

    /*
     * Exits the main loop and calls SDL_Quit()
     */
	virtual void onQuit();

	/*
	 * Called when user presses key on the keyboard.
	 *
	 * @param keyboardEvent keyboard event to handle.
	 */
	//virtual void onKeyDown( const SDL_KeyboardEvent& keyboardEvent );

    //virtual void onKeyUp( const SDL_KeyboardEvent& keyboardEvent );

	//virtual void onMouseMoved( const SDL_MouseMotionEvent& mouseMotionEvent );

private:
    void test();
    void drawExtents(const Extents3& extents, const DrawParams& params);
    void initEffects();

	Configuration configuration;
	Mixer mixer_;
	Device* device_;
	Node* ship;
    GameObject* testObject;
    KeyboardController testController;
    CameraNode* camera_;
    Node* rootNode_;
    bool drawShadows_;
    bool drawExtents_;
    bool drawShadowVolumes_;
    bool rotateLights;
    ProgramManager programManager_;
    MeshManager meshManager_;
    TextureManager textureManager_;
    VertexBufferManager vertexBufferManager_;

	bool running;
	Uint32 deltaTicks; /* ticks between last frame and current frame */
	float deltaTime;
	static const Uint32 ticksPerSecond = 1000;
	Vector3 cameraVelocity;
	float cameraSpeedX;
	float cameraSpeedY;
	float cameraSpeedZ;

    VertexFormat* extentsVertexFormat_;
    VertexFormat* meshVertexFormat_;
    VertexFormat* particleVertexFormat_;
    VertexFormat* shadowVertexFormat_;

    VertexBuffer* shadowVertexBuffer_;

    Effect* dgnsTextureMeshEffect_;
    Effect* noTextureMeshEffect_;
    Effect* extentsEffect_;
    Effect* shadowEffect_;

    // TODO: guess who
    typedef std::vector<Bullet*> BulletVector;
    BulletVector bullets_;
};

#endif /* GAMEPROGRAM_H_ */
