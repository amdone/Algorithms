/*
 * BTree.cpp
 *
 *  Created on: 2019��7��13��
 *      Author: Eichi
 */

#include "BTree.h"
using std::cout;
using std::endl;

template<class K,class E>
BTree<K,E>::BTree(){
	root = NULL;
	treeSize = 0;
	rank = 0;
	pointerCollector = NULL;
}

template<class K,class E>
BTree<K,E>::BTree(int rank){
	if(rank<3)throw std::out_of_range("rank must > 2!");
	this->rank = rank;
	root = NULL;
	treeSize = 0;
	pointerCollector = new BTreeNode<std::pair<K,E>>(rank);
	for(int i = 0;i<rank;i++)
	pointerCollector->child[i] = pointerCollector;
}



template<class K, class E>
bool BTree<K,E>::empty() const {
	return 0==treeSize;
}


template<class K, class E>
int BTree<K,E>::size() const {
	return treeSize;
}


template<class K, class E>
void BTree<K,E>::insert(const std::pair<const K,E>&thePair){
	if(NULL == root){
		root = new BTreeNode<std::pair<K,E>>(rank,true);
		for(int i = 0;i<rank;i++) {
			root->element[i] = std::pair<K,E>();
			root->child[i] = pointerCollector;
		}
		root->element[0] = thePair;
		root->keyNum = 1;
	}
	else if(root->keyNum == rank-1){
		int i = root->keyNum-1;
		if(root->child[0]==this->pointerCollector){
			while(thePair.first < root->element[i].first){
				root->element[i+1] = root->element[i];
				--i;
			}
			root->element[i+1]= thePair;

			BTreeNode<std::pair<K,E>> *tmp = new BTreeNode<std::pair<K,E>>(rank,false);
			for(int i = 0;i<rank;i++) {
				tmp->element[i] = std::pair<K,E>();
				tmp->child[i] = pointerCollector;
			}
			tmp->child[0] = root;
			tmp->splitChild(rank,0,root,pointerCollector);

			root = tmp;
		}
		else
			root->insertNode(rank,thePair,pointerCollector);
	}

	else
		root->insertNode(rank,thePair,pointerCollector);
	if(root->keyNum == rank){
		BTreeNode<std::pair<K,E>> *newRoot = new BTreeNode<std::pair<K,E>>(rank,false);
					for(int i = 0;i<rank;i++) {
						newRoot->element[i] = std::pair<K,E>();
						newRoot->child[i] = pointerCollector;
					}
					newRoot->child[0] = root;
					newRoot->splitChild(rank,0,root,pointerCollector);

					root = newRoot;
	}
	++treeSize;
}


template<class T>
void BTreeNode<T>::insertNode(int rank,T theElement,BTreeNode<T>* pc){
	int i = keyNum-1;

	if(leaf){
		while(0 <= i && theElement.first < element[i].first){
			element[1+i] = element[i];
			--i;
		}
		++keyNum;
		element[i+1] = theElement;
	}
	else{
		while(0 <= i && theElement <element[i])--i;
		BTreeNode<T>* testPointer = child[i+1];
		if(child[i+1] == pc){
			child[i+1] = new BTreeNode<T>(rank,true);
			for(int j = 0;j<rank;j++) testPointer->child[j] = pc;
		}
		if(child[i+1]->keyNum == rank-1){

			int j = child[i+1]->keyNum-1;
			while(theElement.first < child[i+1]->element[j].first){
				child[i+1]->element[j+1] = child[i+1]->element[j];
				--j;
			}
			child[i+1]->element[j+1]= theElement;
			splitChild(rank,i+1,child[i+1],pc);

		}
		else
		child[i+1]->insertNode(rank,theElement,pc);

	}


}




template<class T>
void BTreeNode<T>::splitChild(int rank,int index,BTreeNode *fullNode,BTreeNode *pc){
	BTreeNode *tmp = new BTreeNode(rank,fullNode->leaf);
	for(int i = 0;i<rank;i++) {
		tmp->element[i] = T();
		tmp->child[i] = pc;
	}

	tmp->keyNum = (rank-1)/2;

	for(int i = 0;i < (rank-1)/2; i++){
		tmp->element[i] = fullNode->element[i+rank/2+1];
		fullNode->element[i+rank/2+1] = T();
	}

	if(fullNode->keyNum == rank){
		for(int i = 0;i<rank/2+1;i++){
			tmp->child[i] = fullNode->child[i+rank/2+1];
		}
	}

	else if(!fullNode->leaf){
		for(int i = 0;i<rank/2;i++){
			tmp->child[i] = fullNode->child[i+rank/2];
		}
	}



	fullNode->keyNum = rank/2;

	for(int i = keyNum;i >= index+1; i--){
		child[i+1] = child[i];
	}

	child[index+1] = tmp;

	for(int i = keyNum - 1;i >= index; i--){
		element[i+1] = element[i];
	}

	element[index] = fullNode->element[rank/2];
	fullNode->element[rank/2] = T();
	keyNum++;

}



template<class T>
void BTreeNode<T>::output(){
	if(leaf){
		for(int i = 0;i<keyNum;i++){
			cout<<element[i]<<" ";
		}
	}
	int i=0;
	for(;i<keyNum;i++){
		if(leaf == false){
			child[i]->output();
			cout<<element[i]<<" ";
		}
	}
	if(leaf == false)child[i]->output();
}


template<class K,class E>
void BTree<K,E>::output(){
	if(root == NULL)cout<<"null"<<endl;
	else root->output();
	 cout<<endl;
}


template<class K,class E>
void BTree<K,E>::BTree_print(BTreeNode<std::pair<K,E>> *r, BTreeNode<std::pair<K,E>> *pc,int layer)
{
    int i;
    BTreeNode<std::pair<K,E>>* node = r;
    if (node != pc) {
        cout<<"��"<<layer<<"�� , "<<node->keyNum<<"��key: ";
        for (i = 0; i < node->keyNum; ++i) {
           cout<<node->element[i]<<"  ";
        }
        cout<<endl;

        ++layer;
        for (i = 0 ; i <= node->keyNum; i++) {
            if (node->child[i] != pc) {
                BTree_print(node->child[i],pc, layer);
            }
        }
    }
}

template<class K,class E>
void BTree<K,E>::print()
{
	if(root == NULL)
		cout<<"The tree is null;"<<endl;
	BTree_print(root,this->pointerCollector,0);
}

template<class K, class E>
std::pair<K, E> BTree<K, E>::BTreeMaximum(BTreeNode<std::pair<K, E>> *x)
{
	if (x->leaf)
	{
		return x->element[x->keyNum - 1];
	}
	else
	{
		return BTreeMaximum(x->child[x->keyNum]);
	}
}

template<class K, class E>
std::pair<K, E> BTree<K, E>::BTreeMinimum(BTreeNode<std::pair<K, E>> *x)
{
	if (x->leaf)
	{
		return x->element[0];
	}
	else
	{
		return BTreeMinimum(x->child[0]);
	}
}



template<class K, class E>
void BTree<K, E>::Delete(int k) {
	BTreeDelete(root, k);
}

template<class K, class E>
void BTree<K, E>::BTreeDelete(BTreeNode<std::pair<K, E>> *x, int k)
{
	//if(!search(k))
	// throw "***Ԫ�ز�����***";
	int i = 0, t = rank / 2;
	while (i < x->keyNum && k > x->element[i])
	{
		i++;
	}
	if (k == root->element[i] && !root->leaf)
	{
		BTreeNode<std::pair<K, E>> *y = x->child[i];
		std::pair<K, E> k_ = BTreeMaximum(y);
		x->element[i] = k_;
		//BTreeDelete( y, k_.first );
	}
	if (k == root->element[i] && root->leaf) {
		for (int j = i; j < x->keyNum - 1; ++j)
		{
			x->element[j] = x->element[j + 1];
		}
		x->keyNum--;
	}
	// case 1
	if (i < x->keyNum && k == x->element[i] && x->leaf &&x->keyNum > t)
	{
		for (int j = i; j < x->keyNum - 1; ++j)
		{
			x->element[j] = x->element[j + 1];
		}
		x->keyNum--;
	}
	
	else if (x->child[i]->element[SearchNode(x->child[i], k)].first == k)
	{
		if (x->child[i + 1]->keyNum > t) {
			for (int j = SearchNode(x->child[i], k); j < x->child[i]->keyNum - 1; ++j)
			{
				x->child[i]->element[SearchNode(x->child[i], k)] = x->child[i]->element[SearchNode(x->child[i], k) + 1];
			}
			x->child[i]->element[x->child[i]->keyNum - 1] = x->element[i];
			x->element[i ] = x->child[i + 1]->element[0];
			for (int j = 0; j < x->child[i + 1]->keyNum - 1; ++j) {
				x->child[i + 1]->element[j] = x->child[i + 1]->element[j + 1];
			}
			x->child[i + 1]->keyNum--;
		}
		if (x->child[i + 2]->keyNum > t) {
			for (int j = SearchNode(x->child[i], k); j < x->child[i]->keyNum - 1; ++j)
			{
				x->child[i]->element[SearchNode(x->child[i], k)] = x->child[i]->element[SearchNode(x->child[i], k) + 1];
			}
			x->child[i]->element[x->child[i]->keyNum - 1] = x->element[i + 1];
			x->element[i + 1] = x->child[i + 1]->element[0];
			for (int j = 0; j < x->child[i + 1]->keyNum - 1; ++j) {
				x->child[i + 1]->element[j] = x->child[i + 1]->element[j + 1];
			}
			x->child[i + 1]->element[x->child[i + 1]->keyNum - 1] = x->element[i + 2];
			x->element[i + 2] = x->child[i + 2]->element[0];
			for (int j = 0; j < x->child[i + 2]->keyNum - 1; ++j) {
				x->child[i + 2]->element[j] = x->child[i + 2]->element[j + 1];
			}
			x->child[i + 2]->keyNum--;
		}
	}
	// case 2
	else if (i < x->keyNum && k == x->element[i] && !x->leaf)
	{
		BTreeNode<std::pair<K, E>> *y = x->child[i];
		BTreeNode<std::pair<K, E>> *z = x->child[i + 1];
		// 2a
		if (y->keyNum > t)
		{
			std::pair<K, E> k_ = BTreeMaximum(y);
			x->element[i] = k_;
			BTreeDelete(y, k_.first);
		}
		// 2b
		else if (z->keyNum > t)
		{
			std::pair<K, E> k_ = BTreeMinimum(z);
			x->element[i] = k_;
			BTreeDelete(z, k_.first);
		}
		// 2c
		else if (x->child[i + 2]->keyNum > t) {
			x->element[i] = z->element[0];
			for (int j = 0; j < z->keyNum - 1; ++j) {
				z->element[j] = z->element[j + 1];
			}
			z->element[z->keyNum - 1] = x->element[i + 1];
			x->element[i + 1] = x->child[i + 2]->element[0];
			for (int j = 0; j < x->child[i + 2]->keyNum - 1; ++j) {
				x->child[i + 2]->element[j] = x->child[i + 2]->element[j + 1];
			}
			x->child[i + 2]->keyNum--;

		}
		

		else
		{
			// update the node y
//			y->element[t - 1].first = k;
			for (int j = t; j < 2 * t - 1; ++j)
			{
				y->element[j] = z->element[j - t];
				y->child[j] = z->child[j - t];
			}
			y->child[2 * t - 1] = z->child[t - 1];
			y->keyNum = y->keyNum + z->keyNum + 1;

			// update the node x
			for (int j = i; j < x->keyNum - 1; ++j)
			{
				x->element[j] = x->element[j + 1];
				x->child[j + 1] = x->child[j + 2];
			}
			x->keyNum--;

			// delete z
			delete z;
			BTreeDelete(y, k);
		} // end else 2c
	} // end if case 2
		else
		{
			BTreeDelete(x->child[i], k);
		}
		//
	//}

}




template<class K, class E>
bool operator<(const std::pair<const K, E>& a, std::pair<K, E>& b) {
	return a.first < b.first;
}

template<class K, class E>
bool operator>(K a, std::pair<K, E>& b) {
	return a > b.first;
}

template<class K, class E>
bool operator==(K a, std::pair<K, E>& b) {
	return a == b.first;
}

template<class K,class E>
bool operator>(const std::pair<const K,E>& a,std::pair<K,E>& b){
	return a.first > b.first;
}
