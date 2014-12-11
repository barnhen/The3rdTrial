#include "BoundingBox.h"


BoundingBox::BoundingBox(float x,float y,float width,float height, bool ignoreCollision)
{
	this->position.x = x;
	this->position.y = y;
	this->position.w = width;
	this->position.h = height;
	this->ignoreCollision = ignoreCollision;
}


BoundingBox::~BoundingBox(void)
{
}

//void BoundingBox::init(float x,float y,float width,float height, float velX, float velY)
//{
//
//}

bool BoundingBox::overlapsWith(BoundingBox& OtherBox)
{
	//We don't intersect if...
	//our bottom is higher than their top
	if ( (upperLeftCornerY + height ) < OtherBox.upperLeftCornerY )
		return false;
	//our top is lower than their bottom
	else if ( (upperLeftCornerY) > (OtherBox.upperLeftCornerY + OtherBox.height) )
		return false;
	//our right is more left than their left
	else if ( (upperLeftCornerX + width) < OtherBox.upperLeftCornerX)
		return false;
	//our left is more right than their right 
	else if ( (upperLeftCornerX) > (OtherBox.upperLeftCornerX + OtherBox.width) )
		return false;

	//if we don't fail any of those tests then we're intersecting
	else 
		return true;

}


bool BoundingBox::valueInRange(float value, float min, float max)
{
	return (value >= min) && (value <= max);
}

bool BoundingBox::rectOverlap(Rect box1 , Rect box2)
{
	if(box1.x < box2.x + box2.w && 
	   box1.x + box1.w > box2.x &&
	   box1.y < box2.y + box2.h &&
	   box1.y + box1.h > box2.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BoundingBox::rectTouch(Rect box1 , Rect box2)
{
	bool xOverlap = valueInRange(box1.x ,box2.x ,box2.x + box2.w) ||
					valueInRange(box2.x ,box1.x  ,box1.x + box1.w);

	bool yOverlap = valueInRange(box1.y ,box2.y ,box2.y + box2.w) ||
					valueInRange(box2.y ,box1.y  ,box1.y + box1.w);

	return xOverlap && yOverlap;
}

bool BoundingBox::hasVerticalCollision(Rect box1 , Rect box2)
{
	if (box2.y >= (box1.y + box1.h) - 11)
	{
		return true;
	}
	return false;

}

bool BoundingBox::hasHorizontalCollision(Rect box1 , Rect box2)
{

	if (box1.vX > 0.0f)
	{
		if ((box1.x + box1.w) >= box2.x)
		{
			return true;
		}
	}
	
	if (box1.vX < 0.0f)
	{
		if ((box2.x + box2.w) >= box1.x)
		{
			return true;
		}

	}
	return false;
	//for (int i = 0; i < world.getBlocks().size(); i++)
 //   {
 //       Block block = world.getBlocks().get(i);
 //       if (getRight().intersects(block.getRight()) && velX > 0)
 //       {
 //           return true;
 //       }
 //       if (getLeft().intersects(block.getLeft()) && velX < 0)
 //       {
 //           return true;
 //       }
 //   }
 //   return false;	
}




Rect BoundingBox::getSweptBroadPhaseBox(Rect box)
{
    Rect broadPhaseBox;
	//if box.x is greater than 0 then we set only the box.x, otherwise we calculate box.x + box.velX
    broadPhaseBox.x = box.vX > 0 ? box.x : box.x + box.vX;
    broadPhaseBox.y = box.vY > 0 ? box.y : box.y + box.vY;
    broadPhaseBox.w = box.vX > 0 ? box.vX + box.w : box.w - box.vX;
    broadPhaseBox.h = box.vY > 0 ? box.vY + box.h : box.h - box.vY;

    return broadPhaseBox;
}


// performs collision detection on moving box box1 and static box box2
// returns the time that the collision occured (where 0 is the start of the movement and 1 is the destination)
// getting the new position can be retrieved by box.x = box.x + box.vX * collisiontime
// normalX and normalY return the normal of the collided surface (this can be used to do a response)
//float BoundingBox::sweptAABB(Rect box1, Rect box2, float& normalX, float& normalY)
//{
	////#####################################BEGIN###############################################
	////These values are the inverse time until it hits the other object on the axis. 
 //   float xInvEntry, yInvEntry;
 //   float xInvExit, yInvExit;

	//// find the distance between the objects on the near and far sides for both x and y
	//// i.e. with box1 velX > 0 if box2.x is 30 and box1.x is 10 and box1.width is 10 then xInvEntry is (30-(10+10)) = 10
	//// i.e. with box1 velX > 0 if box2.x is 30 and box2.width is 15 and box1.x is 10 then xInvExit is ((30+15)-10) = 35
 //   if (box1.vX > 0.0f)
 //   {
 //       xInvEntry = box2.x - (box1.x + box1.w);
 //       xInvExit = (box2.x + box2.w) - box1.x;
 //   }
 //   else 
 //   {
 //       xInvEntry = (box2.x + box2.w) - box1.x;
 //       xInvExit = box2.x - (box1.x + box1.w);
 //   }

 //   if (box1.vY > 0.0f)
 //   {
 //       yInvEntry = box2.y - (box1.y + box1.h);
 //       yInvExit = (box2.y + box2.h) - box1.y;
 //   }
 //   else
 //   {
 //       yInvEntry = (box2.y + box2.h) - box1.y;
 //       yInvExit = box2.y - (box1.y + box1.h);
 //   }
	////#######################################END##############################################

	//// We will now use these values to take the velocity into account.

	////#######################################BEGIN#############################################
	//// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
 //   float xEntry, yEntry;
 //   float xExit, yExit;

	////What we are doing here is dividing the xEntry, yEntry, xExit and yExit by the object’s velocity. 
	////Of course, if the velocity is zero on any axis, it will cause a divide-by-zero error. 
	////These new variables will give us our value between 0 and 1 of when each collision occurred on each axis. 
 //   if (box1.vX == 0.0f)
 //   {
 //       xEntry = -std::numeric_limits<float>::infinity();
 //       xExit = std::numeric_limits<float>::infinity();
 //   }
 //   else
 //   {
	//	// i.e. if xInvEntry is 10 and vel is 4 then XEntry is 10/4 = 2.5
	//	// i.e. if xInvExit is 35 and vel is 4 then XEntry is 35/4 = 8.75
 //       xEntry = xInvEntry / box1.vX;
 //       xExit = xInvExit / box1.vX;
 //   }

 //   if (box1.vY == 0.0f)
 //   {
 //       yEntry = -std::numeric_limits<float>::infinity();
 //       yExit = std::numeric_limits<float>::infinity();
 //   }
 //   else
 //   {
 //       yEntry = yInvEntry / box1.vY;
 //       yExit = yInvExit / box1.vY;
 //   }
	////#######################################END###############################################

	////The next step is to find which axis collided first.

	////#######################################BEGIN#############################################
	//// find the earliest/latest times of collision
	////entryTime will tell use when the collision first occurred and exitTime will tell us when it exited the object from the other side. 
	////This can be useful for certain effects, but at the moment, we just need it to calculate if a collision occurred at all.
 //   float entryTime = std::max(xEntry, yEntry); //earliest time
 //   float exitTime = std::min(xExit, yExit); //latest time


	////The if statement below checks to see if there was a collision or not. 
	////If the collision time was not within 0 and 1, then obviously there was no collision during this frame. 
	////Also, the time when the collision first entered should never be after when it exited out the other side. 
	////This is checked, and if it failed, then we assume that there was no collision. We specify 1 to indicate that there was no collision.
	//
	//// if there was no collision
 //   if (entryTime > exitTime || xEntry < 0.0f 
	//	&& yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
 //   {
 //       normalX = 0.0f;
 //       normalY = 0.0f;
 //       return 1.0f;
 //   }

	//// If there was a collision, our last step is to calculate the normal of the edge that was collided with.
	//else // if there was a collision
 //   {        		
 //       // calculate normal of collided surface
 //       if (xEntry > yEntry)
 //       {
 //           if (xInvEntry < 0.0f)
 //           {
 //               normalX = 1.0f;
 //               normalY = 0.0f;
 //           }
	//        else
 //           {
 //               normalX = -1.0f;
 //               normalY = 0.0f;
 //           }
 //       }
 //       else
 //       {
 //           if (yInvEntry < 0.0f)
 //           {
 //               normalX = 0.0f;
 //               normalY = 1.0f;
 //           }
	//        else
 //           {
 //               normalX = 0.0f;
	//	        normalY = -1.0f;
 //           }
 //       }

 //       // return the time of collision
 //       return entryTime;
	////#######################################END###############################################
	//} //else
//}

//
//Rect BoundingBox::getTop(){return false;}
//Rect BoundingBox::getBottom(){return false;}
//Rect BoundingBox::getLeft(){return false;}
//Rect BoundingBox::getRight(){return false;}


/**
* Determines whether or not this <code>Rectangle</code> and the specified
* <code>Rectangle</code> intersect. Two rectangles intersect if
* their intersection is nonempty.
*
* @param r the specified <code>Rectangle</code>
* @return    <code>true</code> if the specified <code>Rectangle</code>
*            and this <code>Rectangle</code> intersect;
*            <code>false</code> otherwise.
*/
//bool intersects(rectangle* s) 
//{
//	int tw = this.w;
//	int th = this.h;
//	int rw = s.w;
//	int rh = s.h;
//        
//	if (rw <= 0 || rh <= 0 || tw <= 0 || th <= 0) 
//	{
//		return false;
//	}
//	int tx = this.x;
//	int ty = this.y;
//	int rx = s.x;
//	int ry = s.y;
//	rw += rx;
//	rh += ry;
//	tw += tx;
//	th += ty;
//	//      overflow || intersect
//	return ((rw < rx || rw > tx) &&
//			(rh < ry || rh > ty) &&
//			(tw < tx || tw > rx) &&
//			(th < ty || th > ry));
//} //end boolean intersects
//
//
//
	

void BoundingBox::setX(float x) 
{
	position.x = x;
	//std::cout<<"bb position.x="<<position.x<<std::endl;

}

void BoundingBox::setY(float y) 
{
	position.y = y;
	//std::cout<<"bb position.y="<<position.y<<std::endl;

}

float BoundingBox::getX() const
{
	//std::cout<<"get position.x="<<position.x<<std::endl;
	return position.x;
}

float BoundingBox::getY() const
{
	//std::cout<<"get position.y="<<position.y<<std::endl;
	return position.y;
}

float BoundingBox::getWidth() const
{
	return position.w;
}

float BoundingBox::getHeight() const
{
	return position.h;
}

//will draw the grid of entire map if toggleGrid funciont is on
void BoundingBox::draw() const {
    al_draw_rectangle(position.x, position.y, position.x + position.w, position.y + position.h, color, 0);
}