#include "CameraView.h"
#include <iostream>

CameraView::CameraView(size_t id, std::vector<std::string> view) : _id(id), _edges(Direction::NR_DIRECTIONS), View(view)
{
	_edges[Direction::UP] = view.front();
	_edges[Direction::DOWN] = view.back();

	for (auto v : view)
	{
		_edges[Direction::LEFT] += v[0];
		_edges[Direction::RIGHT] += v[v.length() - 1];
	}
}

CameraView::CameraView() : _id(0), _edges(Direction::NR_DIRECTIONS)
{
}

void CameraView::RotateLeft()
{
	std::string temp;
	temp = _edges[Direction::RIGHT];

	_edges[Direction::RIGHT] = _edges[Direction::DOWN];
	_edges[Direction::DOWN] = _edges[Direction::LEFT];
	_edges[Direction::LEFT] = _edges[Direction::UP];
	_edges[Direction::UP] = temp;

	std::vector<std::string> tempMap = View;

	for (int x = 0; x < tempMap.size(); ++x)
	{
		for (int i = 0; i < tempMap[x].length(); ++i)
		{
			View[View.size() - i - 1][x] = tempMap[x][i];
		}
	}
}

Direction CameraView::HaveEdge(std::string edge)
{
	std::string reverse = "";
	for (int i = edge.length() - 1; i >= 0; i--)
	{
		reverse += edge[i];
	}

	auto one = std::find(_edges.begin(), _edges.end(), edge); 
	auto two = std::find(_edges.begin(), _edges.end(), reverse);

	auto success = one != _edges.end() || two != _edges.end();

	Direction dir = NR_DIRECTIONS;

	if (success)
	{
		if (one != _edges.end())
		{
			dir = (Direction)(one - _edges.begin());
		}
		else
		{
			dir = (Direction)(two - _edges.begin());
		}
	}
	

	return dir;
}

size_t CameraView::HavePotentialConnection(CameraView& camera)
{
	size_t returnValue = 0;

	for (auto edge : camera.Edges())
	{
		if (HaveEdge(edge) != Direction::NR_DIRECTIONS)
		{
			returnValue++;
		}
	}

	if (returnValue > 0 && std::find(PotentialConnections.begin(), PotentialConnections.end(), camera.ID()) == PotentialConnections.end())
	{
		PotentialConnections.push_back(camera.ID());
	}

	return returnValue;
}

Direction CameraView::ConnectionSide(CameraView camera)
{
	for (auto edge : camera.Edges())
	{
		auto dir = HaveEdge(edge);
		if (dir != Direction::NR_DIRECTIONS)
		{
			return dir;
		}
	}

	return Direction::NR_DIRECTIONS;
}

bool CameraView::Connect(CameraView& camera)
{
	auto found = std::find(PotentialConnections.begin(), PotentialConnections.end(), camera.ID());

	if (found != PotentialConnections.end())
	{
		PotentialConnections.erase(found);
		auto dirOne = ConnectionSide(camera);
		while ((camera.ConnectionSide(*this) + 2) % NR_DIRECTIONS != dirOne)
		{
			camera.RotateLeft();
		}
		ConnectedDirection.push_back(dirOne);
		Connected.push_back(camera.ID());
		camera.DirectConnect(*this);
	}
	return false;
}

bool CameraView::DirectConnect(CameraView& camera)
{
	auto found = std::find(PotentialConnections.begin(), PotentialConnections.end(), camera.ID());

	if (found != PotentialConnections.end())
	{
		PotentialConnections.erase(found);
		auto dirOne = ConnectionSide(camera);
		ConnectedDirection.push_back(dirOne);
		Connected.push_back(camera.ID());
	}
	return false;
}
size_t CameraView::NextRight()
{
	auto found = std::find(ConnectedDirection.begin(), ConnectedDirection.end(), Direction::RIGHT);
	
	if (found != ConnectedDirection.end())
	{
		auto index = found - ConnectedDirection.begin();
		return Connected[index];
	}
	else
	{
		return 0;
	}
}
size_t CameraView::NextDown()
{
	auto found = std::find(ConnectedDirection.begin(), ConnectedDirection.end(), Direction::DOWN);
	
	if (found != ConnectedDirection.end())
	{
		auto index = found - ConnectedDirection.begin();
		return Connected[index];
	}
	else
	{
		return 0;
	}
}

//***/// sad asd 

bool Camera::ValidEdgeConnection(std::string& edge, bool strict)
{
	auto myEdges = Edges();
	std::string reverseEdge = "";

	for (int i = edge.length() - 1; i >= 0; i--)
	{
		reverseEdge += edge[i];
	}

	auto edgeFound = std::find(myEdges.begin(), myEdges.end(), edge);
	auto revereseEdgeFound = std::find(myEdges.begin(), myEdges.end(), reverseEdge);

	return edgeFound != myEdges.end() || ( revereseEdgeFound != myEdges.end() && !strict);
}

bool Camera::ValidEdgeConnection(Direction d, std::vector<std::string>& edges, bool strict)
{
	auto myEdges = Edges();

	switch (d)
	{
	case UP:
		return (myEdges[0] == edges[2]);
	case RIGHT:
		return (myEdges[1] == edges[3]);
	case DOWN:
		return (myEdges[2] == edges[0]);
	case LEFT:
		return (myEdges[3] == edges[1]);
	case NR_DIRECTIONS:
		break;
	default:
		break;
	}
}

std::vector<std::string> Camera::Edges()
{
	std::vector<std::string> edges;
	edges.push_back(view.front());

	std::string left = "";
	std::string right = "";

	for (auto v : view)
	{
		left += v[0];
		right += v[v.length() - 1];
	}

	edges.push_back(right);
	edges.push_back(view.back());
	edges.push_back(left);

	return edges;
}

bool Camera::ValidConnection(Camera* camera)
{
	auto valid = false;

	for (auto edge : camera->Edges())
	{
		if (ValidEdgeConnection(edge))
		{
			valid = true;
			PotentialConnections.push_back(camera);
			break;
		}
	}

	return valid;
}

void Camera::RotateLeft()
{
	auto tempMap = view;

	for (int x = 0; x < tempMap.size(); ++x)
	{
		for (int i = 0; i < tempMap[x].length(); ++i)
		{
			view[view.size() - i - 1][x] = tempMap[x][i];
		}
	}
}

void Camera::FlipHorizontaly()
{
	auto temp = view;
	for (int i = 0; i < temp.size() / 2; ++i)
	{
		view[i] = temp[temp.size() - i - 1];
		view[temp.size() - i - 1] = temp[i];
	}
}

void Camera::FlipVerticly()
{
	auto temp = view;
	for (int row = 0; row < temp.size(); row++)
	{
		for (int i = 0; i < temp[row].size() / 2; ++i)
		{
			view[row][i] = temp[row][temp[row].size() - i - 1];
			view[row][temp[row].size() - i - 1] = temp[row][i];
		}
	}
}

void Camera::Connect(bool rootNode)
{
	if (rootNode)
	{
		connections.push_back({ PotentialConnections[0], Direction::RIGHT });
		connections.push_back({ PotentialConnections[1], Direction::DOWN });

		auto myEdges = Edges();
		auto rightCamera = PotentialConnections[0];
		auto downCamera = PotentialConnections[1];

		while (!rightCamera->ValidEdgeConnection(myEdges[Direction::RIGHT]))
		{
			RotateLeft();
			myEdges = Edges();
		}

		while (!ValidEdgeConnection(rightCamera->Edges()[Direction::LEFT]))
		{
			rightCamera->RotateLeft();
		}

		if (!(myEdges[Direction::RIGHT] == rightCamera->Edges()[Direction::LEFT]))
		{
			rightCamera->FlipHorizontaly();
		}

		if (!downCamera->ValidEdgeConnection(myEdges[Direction::DOWN]))
		{
			for (auto s : view)
			{
				std::cout << s << std::endl;
			}
			std::cout << "" << std::endl;

			rightCamera->FlipHorizontaly();
			FlipHorizontaly();
			myEdges = Edges();
			for (auto s : view)
			{
				std::cout << s << std::endl;
			}
		}

		while (!ValidEdgeConnection(downCamera->Edges()[Direction::UP]))
		{
			PotentialConnections[1]->RotateLeft();
			//edges = PotentialConnections[1]->Edges();
		}

		/*
		while (!ValidEdgeConnection(edges[Direction::UP]))
		{
			PotentialConnections[1]->RotateLeft();
			edges = PotentialConnections[1]->Edges();
		}
		
		while (!ValidEdgeConnection(edges[0], true))
		{
			PotentialConnections[1]->FlipVerticly();
			edges = PotentialConnections[1]->Edges();
		}
		
		for (auto s : view)
		{
			std::cout << s << std::endl;
		}

		std::cout << std::endl;
		for (auto s : PotentialConnections[0]->view)
		{
			std::cout << s << std::endl;
		}

		std::cout << std::endl;
		for (auto s : PotentialConnections[1]->view)
		{
			std::cout << s << std::endl;
		}
*/
		PotentialConnections.clear();
	}
	else
	{
		auto myEdge = Edges();

		for (auto con : PotentialConnections)
		{
			if (con->ValidEdgeConnection(myEdge[0])) // UP
			{

			}
			else if (con->ValidEdgeConnection(myEdge[1])) // RIGHT
			{

			}
			else if (con->ValidEdgeConnection(myEdge[2])) // DOWN
			{

			}
			else if (con->ValidEdgeConnection(myEdge[3])) // LEFT
			{

			}
		}
	}
}

void Camera::RemovePotentialConnection(Camera* cam)
{
	auto found = std::find(PotentialConnections.begin(), PotentialConnections.end(), cam);

	if (found != PotentialConnections.end())
	{
		PotentialConnections.erase(found);
	}

}

Camera::Camera(const std::vector<std::string>& view, size_t id) : view(view), ID(id)
{

}

Camera::Camera()
{

}
