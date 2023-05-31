
#ifndef myset_h
#define myset_h
#include <iostream>
#include <queue>
struct node {
    node* l;
    node* r;
    int val;
    node(int val_) {
        l = nullptr;
        r = nullptr;
        val = val_;
    }
};
class myset {
private:
    node* root = nullptr;
public:
    myset() = default;
    myset(myset& other) {
        if (!root) root = new node(other.root->val);
        else {
            root->val = other.root->val;
        }
        copy(root, other.root);
    }
    void copy(node* t, node* other) {
        if (!other) return;
        if (other->l) {
            t->l = new node(other->l->val);
            copy(t->l, other->l);
        }
        if (other->r) {
            t->r = new node(other->r->val);
            copy(t->r, other->r);
        }
    }
    myset& operator=(const myset& other) {
        if (this == &other) return *this;
        clear();
        root = new node(other.root->val);
        copy(root, other.root);
        return *this;
    }
    bool contains(int key) {
        return contains_real(key, root);
    }
    bool contains_real(int key, node* t) {
        if (!t) return false;
        else if (t->val == key) return true;
        if (t->val > key) return contains_real(key, t->l);
        else {
            return contains_real(key, t->r);
        }
    }
    bool insert(int key) {
        int ret = contains(key);
        root = insert_real(key, root);
        return ret;
    }
    node* insert_real(int key, node* t) {
        if (!t) {
            t = new node(key);
        }
        else if (t->val > key) {
            t->l = insert_real(key, t->l);
        }
        else if (t->val < key) {
            t->r = insert_real(key, t->r);
        }
        return t;
    }
    bool erase(int key) {
        if (!contains(key)) return false;
        return erase_real(root, key) != nullptr;
    }
    node* erase_real(node* t, int key) {
        if (!t) return t;
        if (t->val > key) t->l = erase_real(t->l, key);
        else if (t->val < key) t->r = erase_real(t->r, key);
        else {
            node* mmax = max(t->l);
            node* left;
            node* right;
            if (!mmax) {
                right = t->r;
                if (t == root)
                    root = nullptr;
                delete t;
                return right;
            }
            left = t->l;
            right = t->r;
            if (t == root)
                root = nullptr;
            delete t;
            mmax->r = right;
            mmax->l = erasemax(left);
            return mmax;
        }
        return t;
    }

    node* erasemax(node* t) {
        if (t->r) {
            t->r = erasemax(t->r);
            return t;
        }
        return t->l;
    }
    node* max(node* t) {
        if (t && t->r) return max(t->r);
        else return t;
    }
    void print(node* t) {
        if (!t) return;
        print(t->l);
        std::cout << t->val << " ";
        print(t->r);
    }
    node* getroot() { return root; }
    void delete_node(node* node)
    {
        if (!node) return;
        delete_node(node->l);
        delete_node(node->r);
        delete node;
    }
    void clear() { delete_node(root); root = nullptr; }
    ~myset() { clear(); }
};
void intersect_real(node* t, myset other, std::vector<int>& res) {
    if (!t) return;
    intersect_real(t->l, other, res);
    if (other.contains(t->val)) res.push_back(t->val);
    intersect_real(t->r, other, res);
}


void intersect(myset a, myset b, std::vector<int>& res) {
    intersect_real(a.getroot(), b, res);
}


void substract_real(node* t, myset other, std::vector<int>& res) {
    if (!t) return;
    substract_real(t->l, other, res);
    if (!(other.contains(t->val))) res.push_back(t->val);
    substract_real(t->r, other, res);
}


void substract(myset a, myset b, std::vector<int>& res) {
    substract_real(a.getroot(), b, res);
}

#endif /* myset_h */
