
#ifndef YLTREE4_H
#define YLTREE4_H

#include <iostream>
#include <cstdlib>
//#include <iterator>

#ifdef YL_WIN32_QT
#include <QDebug>
#endif





/**
 * 四向树
 */
template<typename T>
class YLTree4
{
public:
	class NODE
	{
	public:
		NODE *nodeParent;
		NODE *nodeN;
		NODE *nodeS;
		NODE *nodeW;
		NODE *nodeE;
		size_t nodeDepth;
		T nodeData;

#ifdef YL_WIN32_QT
		friend QDebug operator<<(QDebug qd, NODE &n)
		{
			qd << "YLTree4::NODE:::operator<<" << n.nodeData;
			return qd;
		}
#else
		friend std::ostream &operator<< (std::ostream &os, NODE &n)
		{
			os << "YLTree4::NODE:::operator<<" << n.nodeData;
			return os;
		}
#endif
	};

//	 typedef NODE* iterator;
//	 typedef const NODE* const_iterator;

protected:

private:
	NODE *m_root;
	NODE *m_end;
	NODE *m_lastpushed;
//	NODE *m_end;
//	const NODE *m_croot;
//	const NODE *m_cend;
	size_t m_szDepth;
	size_t m_szAmount;



public:
	YLTree4() :
//		m_croot(m_root),
//		m_cend(m_end),
		m_szDepth(0),
		m_szAmount(0)
	{
//		qDebug() << "YLTree4::YLTree4";

		this->m_end = new NODE;
		this->m_end->nodeParent = NULL;
		this->m_end->nodeN = NULL;
		this->m_end->nodeS = NULL;
		this->m_end->nodeW = NULL;
		this->m_end->nodeE = NULL;

		this->m_root = new NODE;
		this->m_root->nodeParent = this->m_end;
		this->m_root->nodeN = this->m_end;
		this->m_root->nodeS = this->m_end;
		this->m_root->nodeW = this->m_end;
		this->m_root->nodeE = this->m_end;
		this->m_root->nodeDepth = 0;
		memset(&(this->m_root->nodeData), 0, sizeof(T));

		this->m_lastpushed = this->m_root;
	}

	YLTree4(const T &rootdata) :
//		m_croot(m_root),
//		m_cend(m_end),
		m_szDepth(1),
		m_szAmount(1)
	{
//		qDebug() << "YLTree4::YLTree4(rootdata)";

		this->m_end = new NODE;
		this->m_end->nodeParent = NULL;
		this->m_end->nodeN = NULL;
		this->m_end->nodeS = NULL;
		this->m_end->nodeW = NULL;
		this->m_end->nodeE = NULL;

		this->m_root = new NODE;
		this->m_root->nodeParent = this->m_end;
		this->m_root->nodeN = this->m_end;
		this->m_root->nodeS = this->m_end;
		this->m_root->nodeW = this->m_end;
		this->m_root->nodeE = this->m_end;

		this->setRootData(rootdata);
	}

	~YLTree4()
	{
//		qDebug() << "YLTree4::~YLTree4";

		this->clear();
		delete this->m_root;
		delete this->m_end;
	}



//	inline iterator begin() { return m_root; }
//	inline const_iterator begin() const { return &m_croot; }
//	inline const_iterator cbegin() const { return &m_croot; }
//	inline iterator end() {return m_end; }
//	inline const_iterator end() const { return &m_cend; }
//	inline const_iterator cend() const { return &m_cend; }



	size_t depth() const { return this->m_szDepth; }
	size_t getDepth() const { return this->m_szDepth; }
	size_t size() const { return this->m_szAmount; }
	size_t getSize() const { return this->m_szAmount; }
	size_t getAmount() const { return this->m_szAmount; }



	/**
	 * @brief clear
	 *		清空树
	 */
	void clear()
	{
//		qDebug() << "YLTree4::clear";

		this->traversalPostorder([&](T &t, NODE *n)
		{
			delete n;
		});

//		NODE **nodestack = new NODE*[this->m_szDepth];
//		size_t *indexnodestack = new size_t[this->m_szDepth];
//		int index = 0;

//		nodestack[index] = this->m_root;
//		indexnodestack[index] = 3;

//		NODE *p = NULL;
//		while (index >= 0)
//		{
//			if (indexnodestack[index] == -1)
//			{
//				delete nodestack[index];
//				--index;
//				continue;
//			}
//			p = *(&(nodestack[index]->nodeN) + indexnodestack[index]);
//			--indexnodestack[index];
//			if (p == this->m_end)
//			{
//				continue;
//			}
//			nodestack[++index] = p;
//			indexnodestack[index] = 3;
//		}

		this->m_root = new NODE;
		this->m_root->nodeParent = this->m_end;
		this->m_root->nodeN = this->m_end;
		this->m_root->nodeS = this->m_end;
		this->m_root->nodeW = this->m_end;
		this->m_root->nodeE = this->m_end;
		this->m_root->nodeDepth = 0;
		memset(&(this->m_root->nodeData), 0, sizeof(T));

		this->m_szDepth = 0;
		this->m_szAmount = 0;
	}



	/**
	 * @brief setRootData
	 * @param data		叶子结点的数据
	 * @return		成功返回根结点
	 */
	NODE *setRootData(const T &data)
	{
		this->m_root->nodeDepth = 1;
		this->m_root->nodeData = data;
		this->m_lastpushed = this->m_root;
		this->m_szDepth = 1;
		return this->m_root;
	}



	/**
	 * @brief pushN
	 *		在X方向上扩展叶子结点
	 * @param pnode		在结点pnode上扩展叶子结点
	 * @param data		叶子结点的数据
	 * @return
	 */
	YLTree4<T> *pushN(NODE *pnode, const T &data)
	{
//		qDebug() << "YLTree4::pushN";

		if (pnode == NULL || pnode == this->m_end || pnode->nodeN != this->m_end)
			return NULL;
		NODE *n = new NODE;
		if (n == NULL)
			return NULL;
		++this->m_szAmount;
		if (pnode->nodeDepth == this->m_szDepth)
			++this->m_szDepth;
		n->nodeParent = pnode;
		n->nodeN = this->m_end;
		n->nodeS = this->m_end;
		n->nodeW = this->m_end;
		n->nodeE = this->m_end;
		n->nodeDepth = this->m_szDepth;
		n->nodeData = data;
		pnode->nodeN = n;
		this->m_lastpushed = pnode;
		return this;
	}

	YLTree4<T> *pushS(NODE *pnode, const T &data)
	{
//		qDebug() << "YLTree4::pushS";

		if (pnode == NULL || pnode == this->m_end || pnode->nodeS != this->m_end)
			return NULL;
		NODE *n = new NODE;
		if (n == NULL)
			return NULL;
		++this->m_szAmount;
		if (pnode->nodeDepth == this->m_szDepth)
			++this->m_szDepth;
		n->nodeParent = pnode;
		n->nodeN = this->m_end;
		n->nodeS = this->m_end;
		n->nodeW = this->m_end;
		n->nodeE = this->m_end;
		n->nodeDepth = this->m_szDepth;
		n->nodeData = data;
		pnode->nodeS = n;
		this->m_lastpushed = pnode;
		return this;
	}

	YLTree4<T> *pushW(NODE *pnode, const T &data)
	{
//		qDebug() << "YLTree4::pushW";

		if (pnode == NULL || pnode == this->m_end || pnode->nodeW != this->m_end)
			return NULL;
		NODE *n = new NODE;
		if (n == NULL)
			return NULL;
		++this->m_szAmount;
		if (pnode->nodeDepth == this->m_szDepth)
			++this->m_szDepth;
		n->nodeParent = pnode;
		n->nodeN = this->m_end;
		n->nodeS = this->m_end;
		n->nodeW = this->m_end;
		n->nodeE = this->m_end;
		n->nodeDepth = this->m_szDepth;
		n->nodeData = data;
		pnode->nodeW = n;
		this->m_lastpushed = pnode;
		return this;
	}

	YLTree4<T> *pushE(NODE *pnode, const T &data)
	{
//		qDebug() << "YLTree4::pushE";

		if (pnode == NULL || pnode == this->m_end || pnode->nodeE != this->m_end)
			return NULL;
		NODE *n = new NODE;
		if (n == NULL)
			return NULL;
		++this->m_szAmount;
		if (pnode->nodeDepth == this->m_szDepth)
			++this->m_szDepth;
		n->nodeParent = pnode;
		n->nodeN = this->m_end;
		n->nodeS = this->m_end;
		n->nodeW = this->m_end;
		n->nodeE = this->m_end;
		n->nodeDepth = this->m_szDepth;
		n->nodeData = data;
		pnode->nodeE = n;
		this->m_lastpushed = pnode;
		return this;
	}



	/**
	 * @brief pushN
	 *		在X方向上扩展叶子结点
	 * @param pnode		在结点pnode上扩展叶子结点
	 * @param data		叶子结点的数据
	 * @return
	 */
	NODE *pushNl(NODE *pnode, const T &data)
	{
//		qDebug() << "YLTree4::pushN";

		if (pnode == NULL || pnode == this->m_end || pnode->nodeN != this->m_end)
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
		n->nodeDepth = this->m_szDepth;
		n->nodeData = data;
		pnode->nodeN = n;
		this->m_lastpushed = pnode;
		return n;
	}

	NODE *pushSl(NODE *pnode, const T &data)
	{
//		qDebug() << "YLTree4::pushS";

		if (pnode == NULL || pnode == this->m_end || pnode->nodeS != this->m_end)
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
		n->nodeDepth = this->m_szDepth;
		n->nodeData = data;
		pnode->nodeS = n;
		this->m_lastpushed = pnode;
		return n;
	}

	NODE *pushWl(NODE *pnode, const T &data)
	{
//		qDebug() << "YLTree4::pushW";

		if (pnode == NULL || pnode == this->m_end || pnode->nodeW != this->m_end)
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
		n->nodeDepth = this->m_szDepth;
		n->nodeData = data;
		pnode->nodeW = n;
		this->m_lastpushed = pnode;
		return n;
	}

	NODE *pushEl(NODE *pnode, const T &data)
	{
//		qDebug() << "YLTree4::pushE";

		if (pnode == NULL || pnode == this->m_end || pnode->nodeE != this->m_end)
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
		n->nodeDepth = this->m_szDepth;
		n->nodeData = data;
		pnode->nodeE = n;
		this->m_lastpushed = pnode;
		return n;
	}



	/**
	 * @brief getNodeX
	 * @param pnode
	 * @return
	 */
	NODE *getNodeRoot() const
	{
		return this->m_root;
	}

	NODE *getNodeEnd() const
	{
		return this->m_end;
	}

	NODE *getNodeParent(NODE *pnode) const
	{
		return pnode->nodeParent;
	}

	NODE *getNodeN(NODE *pnode) const
	{
		return pnode->nodeN;
	}

	NODE *getNodeS(NODE *pnode) const
	{
		return pnode->nodeS;
	}

	NODE *getNodeW(NODE *pnode) const
	{
		return pnode->nodeW;
	}

	NODE *getNodeE(NODE *pnode) const
	{
		return pnode->nodeE;
	}



	NODE *getLastPushed() const
	{
		return this->m_lastpushed;
	}



	/**
	 * @brief getDataX
	 * @param pnode
	 * @return
	 */
	T &getDataRoot() const
	{
		return this->m_root->nodeData;
	}

	T &getDataParent(NODE *pnode) const
	{
		return pnode->nodeParent->nodeData;
	}

	T &getDataN(NODE *pnode) const
	{
		return pnode->nodeN->nodeData;
	}

	T &getDataS(NODE *pnode) const
	{
		return pnode->nodeS->nodeData;
	}

	T &getDataW(NODE *pnode) const
	{
		return pnode->nodeW->nodeData;
	}

	T &getDataE(NODE *pnode) const
	{
		return pnode->nodeE->nodeData;
	}



	/**
	 * @brief traversalPreorder
	 *		DLR 先序遍历
	 */
	template<typename Func> void traversalPreorder(Func func)
	{
//		qDebug() << "YLTree4::preorderTraversal";

		if (this->m_szAmount == 0)
			return ;

		NODE **nodestack = new NODE*[this->m_szDepth];
		size_t *indexnodestack = new size_t[this->m_szDepth];
		int index = 0;

		func(this->m_root->nodeData, this->m_root);
		nodestack[index] = this->m_root;
		indexnodestack[index] = 0;

		NODE *p = NULL;
		while (index >= 0)
		{
			if (indexnodestack[index] == 4)
			{
				--index;
				continue;
			}
			p = *(&(nodestack[index]->nodeN) + indexnodestack[index]);
			++indexnodestack[index];
			if (p == this->m_end)
			{
				continue;
			}
			func(p->nodeData, p);
			nodestack[++index] = p;
			indexnodestack[index] = 0;
		}
	}



	/**
	 * @brief traversalInorder
	 *		LDR 中序遍历
	 */
	template<typename Func> void traversalInorder(Func func)
	{
//		qDebug() << "YLTree4::inorderTraversal";

		if (this->m_szAmount == 0)
			return ;

		NODE **nodestack = new NODE*[this->m_szDepth];
		size_t *indexnodestack = new size_t[this->m_szDepth];
		int index = 0;

		nodestack[index] = this->m_root;
		indexnodestack[index] = 0;

		NODE *p = NULL;
		while (index >= 0)
		{
			if (indexnodestack[index] == 4)
			{
				func(nodestack[index]->nodeData, nodestack[index]);
				--index;
				continue;
			}
			p = *(&(nodestack[index]->nodeN) + indexnodestack[index]);
			++indexnodestack[index];
			if (p == this->m_end)
			{
				continue;
			}
			nodestack[++index] = p;
			indexnodestack[index] = 0;
		}
	}



	/**
	 * @brief traversalPostorder
	 *		LRD 后序遍历
	 */
	template<typename Func> void traversalPostorder(Func func)
	{
//		qDebug() << "YLTree4::postorderTraversal";

		if (this->m_szAmount == 0)
			return ;

		NODE **nodestack = new NODE*[this->m_szDepth];
		size_t *indexnodestack = new size_t[this->m_szDepth];
		int index = 0;

		nodestack[index] = this->m_root;
		indexnodestack[index] = 4;

		NODE *p = NULL;
		while (index >= 0)
		{
			if (indexnodestack[index] == 0)
			{
				func(nodestack[index]->nodeData, nodestack[index]);
				--index;
				continue;
			}
			p = *(&(nodestack[index]->nodeN) + indexnodestack[index] - 1);
			--indexnodestack[index];
			if (p == this->m_end)
			{
				continue;
			}
			nodestack[++index] = p;
			indexnodestack[index] = 3;
		}
	}



#ifdef YL_WIN32_QT
		friend QDebug operator<<(QDebug qd, YLTree4<T> &tree4)
		{
			qd << "YLTree4::operator<<";
			return qd;
		}
#else
	friend std::ostream &operator<< (std::ostream &os, YLTree4<T> &tree4)
	{
		os << "YLTree4::operator<<";
		return os;
	}
#endif

};


















#endif // YLTREE4_H







