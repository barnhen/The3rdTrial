#pragma once
class BoundingBox
{
private:
	float upperLeftCornerX;
	float upperLeftCornerY;
	float height;
	float width;
public:
	BoundingBox(void);
	~BoundingBox(void);

	bool OverlapsWith(BoundingBox& OtherBox);
};

