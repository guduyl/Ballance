
#ifndef YLTREE4_H
#define YLTREE4_H

#include <iostream>
#include <cstdlib>
//#include <iterator>

#include <QDebug>





/**
 * 四向树
 */
template <typename T>
class YLTree4
{
public:
	class NODE
	{
	public:
		T *nodeParent;
		T *nodeN;
		T *nodeS;
		T *nodeW;
		T *nodeE;
		size_t nodeDepth;
		T nodeData;

		friend std::ostream &operator<< (std::ostream &os, NODE &n)
		{
			os << "YLTree4::NODE: " << n.nodeData;
			return os;
		}
	};

//	 typedef NODE* iterator;
//	 typedef const NODE* const_iterator;

protected:

private:
	NODE *m_root;
	NODE *m_end;
	const NODE *m_croot;
	const NODE *m_cend;
	size_t m_szDepth;
	size_t m_szAmount;



public:
	YLTree4() :
//		m_croot(m_root),
//		m_cend(m_end),
		m_szDepth(0),
		m_szAmount(0)
	{
		qDebug() << "YLTree4::YLTree4";

		m_end = new NODE;
		m_root->nodeParent = NULL;
		m_root->nodeN = NULL;
		m_root->nodeS = NULL;
		m_root->nodeW = NULL;
		m_root->nodeE = NULL;

		m_root = new NODE;
		m_root->nodeParent = NULL;
		m_root->nodeN = NULL;
		m_root->nodeS = NULL;
		m_root->nodeW = NULL;
		m_root->nodeE = NULL;
	}

	YLTree4(const T &rootdata) :
//		m_croot(m_root),
//		m_cend(m_end),
		m_szDepth(0),
		m_szAmount(0)
	{
		qDebug() << "YLTree4::YLTree4";

		this->YLTree4();
		this->setRootData(rootdata);
	}

	~YLTree4()
	{
		qDebug() << "YLTree4::~YLTree4";

		this->clear();
		delete m_root;
		delete m_end;
	}



//	inline iterator begin() { return m_root; }
//	inline const_iterator begin() const { return &m_croot; }
//	inline const_iterator cbegin() const { return &m_croot; }
//	inline iterator end() {return m_end; }
//	inline const_iterator end() const { return &m_cend; }
//	inline const_iterator cend() const { return &m_cend; }



	/**
	 * void YLTree4<T>::clear
	 *		清空树
	 */
	void clear()
	{
		qDebug() << "YLTree4::clear";

	}



	/**
	 * YLTree4::NODE *YLTree<T>::setRootData
	 * @param T data		叶子结点的数据
	 * @return NODE 		成功返回根结点
	 */
	NODE *setRootData(const T &data)
	{
		m_root->nodeData = data;
		return m_root;
	}



	/**
	 * NODE *YLTree4<T>::pushX
	 *		在X方向上扩展叶子结点
	 * @param NODE *pnode		在结点pnode上扩展叶子结点
	 * @param T data		叶子结点的数据
	 * @return NODE * 		添加成功返回pnode，否则返回尾迭代器
	 */
	NODE *pushN(NODE *pnode, const T &data)
	{
		qDebug() << "YLTree4::pushN";

		if (pnode == NULL || pnode == this->m_end)
			return this->m_end;
		NODE *n = new NODE;
		if (n == NULL)
			return this->m_end;
		++this->m_szAmount;
		if (pnode->nodeDepth == this->m_szDepth)
			++this->m_szDepth;
		n->nodeParent = pnode;
		n->nodeN = this->m_end;
		n->nodeS = this->m_end;
		n->nodeW = this->m_end;
		n->nodeE = this->m_end;
		n->nodeData = data;
		pnode->nodeN = n;
		return pnode;
	}

	NODE *pushS(NODE *pnode, const T &data)
	{
		qDebug() << "YLTree4::pushS";

		if (pnode == NULL || pnode == this->m_end)
			return this->m_end;
		NODE *n = new NODE;
		if (n == NULL)
			return this->m_end;
		++this->m_szAmount;
		if (pnode->nodeDepth == this->m_szDepth)
			++this->m_szDepth;
		n->nodeParent = pnode;
		n->nodeN = this->m_end;
		n->nodeS = this->m_end;
		n->nodeW = this->m_end;
		n->nodeE = this->m_end;
		n->nodeData = data;
		pnode->nodeS = n;
		return pnode;
	}

	NODE *pushW(NODE *pnode, const T &data)
	{
		qDebug() << "YLTree4::pushW";

		if (pnode == NULL || pnode == this->m_end)
			return this->m_end;
		NODE *n = new NODE;
		if (n == NULL)
			return this->m_end;
		++this->m_szAmount;
		if (pnode->nodeDepth == this->m_szDepth)
			++this->m_szDepth;
		n->nodeParent = pnode;
		n->nodeN = this->m_end;
		n->nodeS = this->m_end;
		n->nodeW = this->m_end;
		n->nodeE = this->m_end;
		n->nodeData = data;
		pnode->nodeW = n;
		return pnode;
	}

	NODE *pushE(NODE *pnode, const T &data)
	{
		qDebug() << "YLTree4::pushE";

		if (pnode == NULL || pnode == this->m_end)
			return this->m_end;
		NODE *n = new NODE;
		if (n == NULL)
			return this->m_end;
		++this->m_szAmount;
		if (pnode->nodeDepth == this->m_szDepth)
			++this->m_szDepth;
		n->nodeParent = pnode;
		n->nodeN = this->m_end;
		n->nodeS = this->m_end;
		n->nodeW = this->m_end;
		n->nodeE = this->m_end;
		n->nodeData = data;
		pnode->nodeE = n;
		return pnode;
	}



	friend std::ostream &operator<< (std::ostream &os, YLTree4<T> &tree4)
	{
		os << "operator<<: YLTree4<T>";
		return os;
	}

};

















#endif // YLTREE4_H







