#pragma once

#include <string>
#include <iostream>
#include <vector>
template<class T>
class WeightGreater
{
public:
	bool operator()(const T& a, const T& b) const
	{
		return a.Weight() > b.Weight();
	}

	bool operator()(const T* a, const T* b) const
	{
		return a->Weight() > b->Weight();
	}
};

template<class T>
class WeightLess
{
public:
	bool operator()(const T& a, const T& b) const
	{
		return a.Weight() < b.Weight();
	}

	bool operator()(const T* a, const T* b) const
	{
		return a->Weight() < b->Weight();
	}
};

template<class T>
class DeleteFunc
{
public:
	void operator()(const T* it) const
	{
		delete it;
	}
};


class BaseVertex
{
	int m_nID;
	double m_dWeight;

public:

	int getID() const { return m_nID; }
	void setID(int ID_) { m_nID = ID_; }

	double Weight() const { return m_dWeight; }
	void Weight(double val) { m_dWeight = val; }

	void PrintOut(std::ostream& out_stream)
	{
		int k = m_nID + 65;
		out_stream << (char)k;
	}
};


class BasePath
{
protected:

	int m_nLength;
	double m_dWeight;
	std::vector<BaseVertex*> m_vtVertexList;

public:
	BasePath(const std::vector<BaseVertex*>& vertex_list, double weight)
		:m_dWeight(weight)
	{
		m_vtVertexList.assign(vertex_list.begin(), vertex_list.end());
		m_nLength = m_vtVertexList.size();
	}
	~BasePath(void) {}

	double Weight() const { return m_dWeight; }
	void Weight(double val) { m_dWeight = val; }

	int length() { return m_nLength; }

	BaseVertex* GetVertex(int i)
	{
		return m_vtVertexList.at(i);
	}

	bool SubPath(std::vector<BaseVertex*>& sub_path, BaseVertex* ending_vertex_pt)
	{

		for (std::vector<BaseVertex*>::const_iterator pos = m_vtVertexList.begin();
			pos != m_vtVertexList.end(); ++pos)
		{
			if (*pos != ending_vertex_pt)
			{
				sub_path.push_back(*pos);
			}
			else
			{
				return true;
			}
		}

		return false;
	}

	void PrintOut(std::ostream& out_stream) const
	{
		int k = 0;
		out_stream << "Длина пути: " << m_dWeight << " Количество переходов: " << m_vtVertexList.size() << std::endl;
		for (std::vector<BaseVertex*>::const_iterator pos = m_vtVertexList.begin(); pos != m_vtVertexList.end(); ++pos)
		{
			(*pos)->PrintOut(out_stream);
			k++;
			if (k != m_vtVertexList.size()) {
				out_stream << "->";
			}
		}
		out_stream << std::endl << "*********************************************" << std::endl;
	}
};