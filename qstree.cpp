#include <QtCore>
#include "qstree.h"

static void updateNodeToRoot(QSTreeNode* node) {
    node->update();

    if (node->parent() != 0) {
        updateNodeToRoot(node->parent());
    }
}

QSTree::QSTree()
{
    m_min = m_max = m_sum = m_height = 0;
    m_root = 0;
}

QSTree::~QSTree()
{
    if (m_root) {
        delete m_root;
    }
}

int QSTree::min() const
{
    return m_min;
}

void QSTree::setMin(int min)
{
    m_min = min;
}

void QSTree::updateFromRoot()
{
    if (m_root) {
        m_sum = m_root->sum();
        m_height = m_root->height();
    } else {
        m_sum = 0;
        m_height = 0;
    }
}

void QSTree::simpleRemove(QSTreeNode *node)
{
    QSTreeNode* child = 0;

    if (node->hasLeft()) {
        child = node->takeLeft();
    } else if (node->hasRight()) {
        child = node->takeRight();
    }

    QSTreeNode * parent = node->parent();

    if (parent) {
        if (parent->left() == node) {
            parent->setLeft(child);
        } else {
            parent->setRight(child);
        }
    } else {
        // It is root node
        m_root = child;
        updateFromRoot();
    }

    delete node;
}

int QSTree::max() const
{
    return m_max;
}

void QSTree::setMax(int max)
{
    m_max = max;
}

int QSTree::sum() const
{
    return m_sum;
}

void QSTree::setSum(int sum)
{
    m_sum = sum;
}

int QSTree::height() const
{
    return m_height;
}

void QSTree::setHeight(int depth)
{
    m_height = depth;
}

QSTreeNode *QSTree::root() const
{
    return m_root;
}

void QSTree::setRoot(QSTreeNode *root)
{
    m_root = root;
    if (root) {
        m_min = root->key();
        m_max = root->key();
        m_sum = root->count();
    } else {
        m_min = 0;
        m_max = 0;
        m_sum = 0;
    }
}

QSTreeNode *QSTree::insert(int key, int count)
{
    QSTreeNode* node = new QSTreeNode(key, count);
    insert(node);
    return node;
}

void QSTree::remove(int key)
{
    if (m_root == 0) {
        return;
    }

    QSTreeNode *node = search(key);

    if (node == 0) {
        return;
    }

    if (node->hasLeft() && node->hasRight()) {
        QSTreeNode* minNode = searchMin(node->right());
        QSTreeNode* maxNode = searchMax(node->right());
        node->setCount(minNode->count());
        node->setKey(minNode->key());

        bool isMinMaxSame = minNode == maxNode;
        simpleRemove(minNode);

        if (!isMinMaxSame) {
            updateNodeToRoot(maxNode);
        } else {
            updateNodeToRoot(node);
        }
    } else {
        QSTreeNode* parent = node->parent();
        simpleRemove(node);

        if (parent) {
            // Node is not root element
            updateNodeToRoot(parent);
        }
    }

    if (key == m_min && m_root != 0) {
        QSTreeNode* minNode = searchMin(m_root);
        m_min = minNode->key();
    }

    updateFromRoot();
}

QSTreeNode *QSTree::search(int key) const
{
    if (m_root == 0) {
        return 0;
    }

    return search(m_root, key);
}

int QSTree::countLessThan(int key) const
{
    QSTreeNode* node = search(key);

    if (node == 0) {
        return 0;
    }

    return countLessThan(node);
}

int QSTree::countLessThan(QSTreeNode *node) const
{
    int sum = 0;
    bool fromRightChild = false;
    int key = node->key();

    while (node != 0) {

        if (!fromRightChild && node->left()) {
            sum += node->left()->sum();
        }

        if (node->key() < key) {
            sum += node->count();
        }

        if (node->parent()) {
            fromRightChild = node->parent()->right() != node;
        }

        node = node->parent();
    }

    return sum;
}

void QSTree::insert(QSTreeNode *node)
{
    if (m_root == 0) {
        setRoot(node);
    } else {

        searchNodeToInsert(m_root, node);

        if (m_min > node->key()) {
            m_min = node->key();
        }
        if (m_max < node->key()) {
            m_max = node->key();
        }
    }

    m_sum = m_root->sum();
    m_height = m_root->height();
}

void QSTree::searchNodeToInsert(QSTreeNode *current, QSTreeNode *node)
{
    if (node->key() < current->key()) {

        if (current->left() == 0) {
            current->setLeft(node);
            node->setParent(current);
        } else {
            searchNodeToInsert(current->left(), node);
        }

    } else {

        if (current->right() == 0) {
            current->setRight(node);
            node->setParent(current);
        } else {
            searchNodeToInsert(current->right(), node);
        }

    }

    current->update();
}

QSTreeNode* QSTree::search(QSTreeNode *node, int key) const
{
    QSTreeNode* res = 0;

    if (node->key() == key) {
        return node;
    } else if (key < node->key() ) {
        if (node->left() != 0) {
            res = search(node->left(), key);
        }
    } else {
        if (node->right() != 0) {
            res = search(node->right(), key);
        }
    }
    return res;
}

QSTreeNode *QSTree::searchMin(QSTreeNode *node) const
{
    if (!node->hasLeft()) {
        return node;
    } else {
        return searchMin(node->left());
    }
}

QSTreeNode *QSTree::searchMax(QSTreeNode *node) const
{
    if (!node->hasRight()) {
        return node;
    } else {
        return searchMax(node->right());
    }
}

QDebug operator<<(QDebug dbg, const QSTree& tree) {

    QQueue<QSTreeNode*> queue;
    QStringList links;

    if (tree.root() != 0) {
        queue.enqueue(tree.root());
        links.append(QString("[%1]").arg(tree.root()->key()));
    }

    while (queue.size() > 0) {
        QSTreeNode* node = queue.dequeue();

        if (node->parent() != 0) {
            links << QString("%1 -> %2").arg(node->parent()->key()).arg(node->key());
        }

        if (node->hasLeft()) {
            queue.enqueue(node->left());
        }

        if (node->hasRight()) {
            queue.enqueue(node->right());
        }

    }

    dbg << links.join(",");
    return dbg;
}

