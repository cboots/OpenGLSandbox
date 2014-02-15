#pragma once
#include "../glm/glm.hpp"

using namespace glm;

struct BoundingBox
{
public:
	vec4 corners[8];

	BoundingBox()
	{
		for(int i = 0; i < 8; ++i)
		{
			corners[i] = vec4(0,0,0,1);
		}
	}

	BoundingBox(const BoundingBox& old)
	{
		for(int i = 0; i < 8; ++i)
		{
			corners[i] = old.corners[i];
		}
	}

	 BoundingBox& BoundingBox::operator=( const BoundingBox& rhs )
	 {
		for(int i = 0; i < 8; ++i)
		{
			corners[i] = rhs.corners[i];
		}
		 return *this;
	 }

	vec4 getAABBMax()
	{
		vec4 largest = corners[0];
		for(int i = 1; i < 8; ++i)
		{
			largest = glm::max(largest, corners[i]);
		}
		return largest;
	}

	vec4 getAABBMin()
	{
		vec4 smallest = corners[0];
		for(int i = 1; i < 8; ++i)
		{
			smallest = glm::min(smallest, corners[i]);
		}
		return smallest;
	}
	
	//corner = T*corner
	BoundingBox preMultiplyBy(mat4 transform)
	{
		for(int i = 0; i < 8; ++i)
		{
			corners[i] = transform*corners[i];
		}

		return *this;
	}

	static BoundingBox Merge(BoundingBox box1, BoundingBox box2)
	{
		vec4 AABBMax = glm::max(box1.getAABBMax(), box2.getAABBMax());
		vec4 AABBMin = glm::min(box1.getAABBMin(), box2.getAABBMin());

		BoundingBox merged;
		for(int i = 0; i < 8; i++)
		{
			if(i & 1)//First bit set
				merged.corners[i].x = AABBMax.x;
			else
				merged.corners[i].x = AABBMin.x;
			
			if(i & 2)//Second bit set
				merged.corners[i].y = AABBMax.y;
			else
				merged.corners[i].y = AABBMin.y;
			
			if(i & 4)//third bit set
				merged.corners[i].z = AABBMax.z;
			else
				merged.corners[i].z = AABBMin.z;

			merged.corners[i].w = 1;
		}

		return merged;

	}

	static BoundingBox MakeCenteredUnitBox()
	{
		BoundingBox bb = BoundingBox();
		for(int i = 0; i < 8; i++)
		{
			if(i & 1)//First bit set
				bb.corners[i].x =  0.5;
			else
				bb.corners[i].x = -0.5;
			
			if(i & 2)//Second bit set
				bb.corners[i].y =  0.5;
			else
				bb.corners[i].y = -0.5;
			
			if(i & 4)//third bit set
				bb.corners[i].z =  0.5;
			else
				bb.corners[i].z = -0.5;

		}
		return bb;
	}

};