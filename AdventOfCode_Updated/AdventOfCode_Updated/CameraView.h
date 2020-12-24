#pragma once
#include <string>
#include <vector>
#include <map>

enum Direction
{
	UP, // 0
	RIGHT, // 1
	DOWN, // 2
	LEFT, // 3
	NR_DIRECTIONS // 4
};

class CameraView
{
private:
	std::vector<std::string> _edges;
	size_t _id;
public:
	std::vector<size_t> PotentialConnections;
	std::vector<size_t> Connected;
	std::vector<Direction> ConnectedDirection;
	std::vector<std::string> View;
	CameraView(size_t, std::vector<std::string>);
	CameraView();
	void RotateLeft();
	Direction HaveEdge(std::string);
	size_t HavePotentialConnection(CameraView&);
	Direction ConnectionSide(CameraView);
	bool Connect(CameraView&);
	bool DirectConnect(CameraView&);
	size_t NextRight();
	size_t NextDown();

	std::vector<std::string> Edges() { return _edges; }
	size_t ID() { return _id; }

	bool operator<(const CameraView& other)
	{
		return _id < other._id;
	}
	bool operator==(const CameraView& other)
	{
		return _id == other._id;
	}
	bool operator==(size_t other)
	{
		return _id == other;
	}
};

struct CameraConnection;

class Camera
{
private:
public:
	size_t ID;
	std::vector<CameraConnection> connections;
	std::vector<Camera*> PotentialConnections;
	std::vector<std::string> view;

	std::vector<std::string> Edges();
	bool ValidEdgeConnection(std::string&, bool = false);
	bool ValidEdgeConnection(Direction, std::vector<std::string>&, bool = false);
	bool ValidConnection(Camera*);
	void RotateLeft();
	void FlipHorizontaly();
	void FlipVerticly();
	void Connect(bool);
	void RemovePotentialConnection(Camera*);

	Camera(const std::vector<std::string>&, size_t);
	Camera();

	bool operator==(const Camera& other)
	{
		return ID == other.ID;
	}
};

struct CameraConnection
{
public:
	Camera* camera;
	Direction direction;
	CameraConnection(Camera* c, Direction d) : camera(c), direction(d) {}
};