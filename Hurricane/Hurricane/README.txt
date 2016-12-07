Welcome to Hurricane!

Date Created: Jan 20, 2016
Last Updated: Dec 05, 2016

Primary Author: Edwin Chen

*Special Thanks: Scott Fielder
				 Mathieu Violette
				 James Sholdice
				 Nathan Senter
				 Nick Whalen
				 Raymond Micheau
				 Mark Seaman
				 Rob Spongale
				 Adam Hermosa
				 Aiden Dearing
				 Domenic Caronzo
				 Kris Alexander
				 House Yokeswaran
				 Nicco Jacinto
				 Adam Hoang

Introduction:
This is my first ever game engine. It is mainly focused on building 3rd person platformer-like games.
Hurricane is programmed purely in C++ to allow for fast memory management and efficiency.


Dependencies:
Hurricane makes use of many different 3rd party APIs to allow for ease of use, production time reduction, etc.
I do not own any of the APIs listed below and all rights and credits belong to their repsective owners.

Dependency				Purpose in Engine
----------------------------------------------------------------------------------------------------------------
TinyXML					- XML parsing, loading in properties and information for games
SDL2					- Window creation, event handling
SDL2 Image				- Texture loading, rendering
OpenGL (GLEW)			- 3D Graphics
OpenAL					- Audio
Assimp					- Model loading (.fbx, .obj, etc.)
						- Skeletal animation (very important for this engine!)


Notes:
*Thank you to everybody mentioned in the list above! Without you guys, Hurricane would not be possible!