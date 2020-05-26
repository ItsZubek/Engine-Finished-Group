#include "Physics/PlayerShape.h"
#include "Position.h"
namespace Engine
{
	class Ship : public PlayerShape
	{
	private:
		
	protected:
		Position pos; // current position of tank
		Position oldPos; // Previous Position of tank
		float rotation; //!< Current rotation of ship
		
		bool forward; //!< ship moving forwards
		bool backward; //!< ship moving backwards
		bool left; //!< ship turning left
		bool right; //!< ship turning right
		bool RotateLeft; //!< Turret turning left
		bool RotateRight; //!< Turret turing right

		void clearMovement(); //!< Stop current movement
		//Box2D void update bounding box
		//BOX2D void draw ship 
		
	public:
		Ship();
		//!< BOX2D bounding Box
		//BOX2D Drawship
		//Box2D Reset Position
			// Movement methods
		void goForward(); //!< Set the ship to go forwards
		void goBackward(); //!< Set the ship to go backwards
		void goLeft(); //!< Set the ship to go left
		void goRight(); //!< Set the ship to go right
		void ShipRotateLeft(); //!< Set the ship to go left
		void ShipRotateRight(); //!< Set the ship to go right
		void stop() { clearMovement(); } //!< Stop the ship movement
		void stopRotate(); //!< Stop the turret movement
		//!< Box2D Record the prevoius position
		 //!< Box2D Go back to the prevoius position

		void fireShell(); //!< Fire a shell
		virtual void move() = 0; //?!< Implemented in child classes
		void implementMove();
		

		Position firingPosition() const; //!< Position of the ship as shell is fired
		float getX() const { return pos.getX(); } //!< Position of the ship in x
		float getY() const { return pos.getY(); } //!< Position of the ship in y
		
		bool canSee() const; //!< Can this ship see the bounding box?
		bool canFire() const; //!< Can this ship fire
		
	};


}