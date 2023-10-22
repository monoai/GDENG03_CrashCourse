#pragma once
class Point
{
public:
	Point() :m_x(0), m_y(0)
	{
	}
	Point(int x, int y) :m_x(x), m_y(y)
	{
	}
	Point(const Point& point) :m_x(point.m_x), m_y(point.m_y)
	{
	}
	~Point()
	{
	}

	int getX() const
	{
		return this->m_x;
	}

	int getY() const
	{
		return this->m_y;
	}

public:
	int m_x = 0, m_y = 0;
};
/*
class Point
{
public:
	Point()
	{
	}

	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	Point(const Point* point)
	{
		this->x = point->x;
		this->y = point->y;
	}

	~Point()
	{

	}

	int getX() const
	{
		return this->x;
	}

	int getY() const
	{
		return this->y;
	}

private:
	int x = 0;
	int y = 0;
};
*/