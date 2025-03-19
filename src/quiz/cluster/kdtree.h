#ifndef PROJECT_KD_TREE_H_
#define PROJECT_KD_TREE_H_

#include "../../render/render.h"


template <typename PointT>
struct Node
{
	PointT point;
	int id;
	Node* left;
	Node* right;

	Node(PointT arr, int setId):point(arr), id(setId), left(NULL), right(NULL)
	{}

	~Node()
	{
		delete left;
		delete right;
	}
};
template <typename PointT>
struct KdTree
{
	Node<PointT>* root;

	KdTree():root(NULL)	{}

	~KdTree()
	{
		delete root;
	}

	float GetDataPoint (PointT point, uint depth)
	{
		if(depth==0)
		{
			return point.x;
		}
		else if(depth==1)
		{
			return point.y;
		}
		else
		{
			return  point.z;
		}
	}
	void insertHelper(Node<PointT>*&  node, uint depth, PointT point, int id)
	{
		if(node == nullptr)
		{
			node = new Node<PointT>(point,id);
		}
		else
		{
			 uint cd = depth%3;

			 if((GetDataPoint(point,cd)) <(GetDataPoint(node->point,cd)))
			 {
				insertHelper(node->left,   depth+1,  point,  id);
			 }
			 else
			 {
				insertHelper(node->right,   depth+1,  point,  id);
			 }

		}
	}

	float GetDistance(PointT target, PointT nodePoint)
	{
		float np_x=GetDataPoint(nodePoint,0);
		float target_x= GetDataPoint(target,0);
		float np_y=GetDataPoint(nodePoint,1);
		float target_y= GetDataPoint(target,1);
		float np_z=GetDataPoint(nodePoint,2);
		float target_z= GetDataPoint(target,2);
		return sqrt(((np_x - target_x)*(np_x- target_x))
		+ ((np_y - target_y)*(np_y- target_y))+
		((np_z - target_z)*(np_z- target_z)));
	}

	void searchHelper(PointT target, Node<PointT>* node, int depth, float distanceTol, std::vector<int>& ids)
	{
		if (node!=NULL)
		{
			if ((GetDataPoint(node->point,0)>=(GetDataPoint(target,0)-distanceTol) &&(GetDataPoint(node->point,0)<=(GetDataPoint(target,0) + distanceTol))) 
			&& 
			(GetDataPoint(node->point,1)>=(GetDataPoint(target,1)-distanceTol) &&(GetDataPoint(node->point,1)<=(GetDataPoint(target,1) + distanceTol))) 
			&& 
			(GetDataPoint(node->point,2)>=(GetDataPoint(target,2)-distanceTol) &&(GetDataPoint(node->point,2)<=(GetDataPoint(target,2) + distanceTol))) )
			{
				
				float distance = GetDistance(target,node->point);
				if (distance <=distanceTol)
				{
					ids.push_back(node->id);
				}
			}
			float  target_val = GetDataPoint (target,   depth%3);
			float  point_val = GetDataPoint (node->point,   depth%3);
			if((target_val -distanceTol)<(point_val))
			{
				searchHelper(target, node->left,depth+1,distanceTol,ids);
			}
			if((target_val +distanceTol)>(point_val))
			{
				searchHelper(target, node->right,depth+1,distanceTol,ids);
			}
		}
	}

	void insert(PointT point, int id)
	{
		insertHelper(root, 0,  point, id);

	}

	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(PointT target, float distanceTol)
	{
		std::vector<int> ids;
		searchHelper(target, root,0,distanceTol,ids);
		return ids;
	}
	

};

#endif /* PROJECT_KD_TREE_H_ */


