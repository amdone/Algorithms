/*
 * binaryTree.cpp
 *
 *  Created on: 2017年4月8日
 *      Author: lsn
 */



//测试二叉树

#include "linkedBinaryTree.cpp"

using std::cout;
using std::endl;
//template class linkedBinaryTree<int>;//显式实例化，帮助检查所有函数的实现是不是正确


int main(){
	   linkedBinaryTree<int> a,x,y,z;


	   z.makeTree(2,a,a);
	   x.makeTree(3,y,z);
	   y.makeTree(4,x,a);
	   cout << "Number of nodes = ";
	   cout << y.size() << endl;
	   cout << "Preorder sequence is ";
	   y.preOrderOutput();

	   cout<<"is?:"<<y.isHBLTree();






	return 0;
}






/*
//测试huffmanTree第1种实现方法
#include <iostream>
using std::cout;
using std::endl;

#include "huffmanTree1.cpp"
int main(){
int a[6];
 int n = 5;
 for (int i = 1; i <= n; i++) a[i] = i;
 linkedBinaryTree<int> *x = huffmanTree(a, n);//为了释放内存
 x->postOrderOutput();

 delete x;

 return 0;
}
*/
/*

#include <iostream>
using std::cout;
using std::endl;

//测试huffmanTree第2中实现方法
#include "huffmanTree2.cpp"
int main(){
int a[]={1,2,3,4,5,6};
huffmanTree<int> x(a,6);

cout<<"hello"<<endl;

return 0;
}
*/


/*
#include <iostream>
using std::cout;
using std::endl;

//测试huffmanTree第3种实现方法
#include "huffmanTree3.cpp"
int main(){
int a[]={1,2,3,4,5,6};
huffmanTree<int> x(a,6);


cout<<"hello"<<endl;

 return 0;
}
*/

/*
#include <iostream>
using std::cout;
using std::endl;

//测试huffmanTree第4种实现方法
#include "huffmanTree4.cpp"
int main(){
int a[]={1,2,3,4,5,6};
huffmanTree<int> x(a,6);

cout<<"hello"<<endl;

 return 0;
}
*/


/*
//测试左高树

#include "maxhblt.cpp"

using std::cout;
using std::endl;

int main(void)
{
   maxHblt<int> h, j;
   int a[6] = {0,1, 2, 3, 4, 5};
   h.initialize(a,5);
   cout << "One tree in postorder is" << endl;
   cout << "Tree size is " << h.size() << endl;
   h.output();
   int b[5] = {0, 2, 6, 4, 9};

   j.initialize(b,4);
   cout << "Other tree in postorder is" << endl;
   cout << "Tree size is " << j.size() << endl;
   j.output();

   h.meld(j);
   cout << "After melding, the tree in postorder is" << endl;
   cout << "Tree size is " << h.size() << endl;
   h.output();

   int w = h.top();
   h.pop();
   int x = h.top();
   h.pop();
   int y = h.top();
   h.pop();
   int z = h.top();
   h.pop();
   cout << "After popping four elements, the tree is" << endl;
   cout << "Tree size is " << h.size() << endl;
   h.output();
   cout << "The popped elements, in order, are" << endl;
   cout << w << "  " << x << "  " << y << "  " << z << endl;

   h.push(10);
   h.push(20);
   h.push(5);
   cout << "After pushing 10, 20 & 5, the tree is" << endl;
   cout << "Leftist tree in postorder" << endl;
   cout << "Tree size is " << h.size() << endl;
   h.output();

   h.push(15);
   h.push(30);
   h.push(2);
   cout << "After pushing 15, 30 & 15, the tree is" << endl;
   cout << "Leftist tree in postorder" << endl;
   cout << "Tree size is " << h.size() << endl;
   h.output();

   cout << "The max element is " << h.top() << endl;

   h.pop();
   cout << "Popped max element " << endl;
   cout << "Leftist tree in postorder" << endl;
   cout << "Tree size is " << h.size() << endl;
   h.output();

   x = h.top();
   h.pop();
   cout << "Popped max element " << x << endl;
   cout << "Tree size is " << h.size() << endl;
   cout << "Leftist tree in postorder" << endl;
   h.output();

   while (true)
   {// empty out
      try
      {
         x = h.top();
         h.pop();
         cout << "Popped " << x << endl;
         cout << "Tree size is " << h.size() << endl;
      }
      catch (std::out_of_range &e) {
    	  cout<<e.what();
    	  break;
      }
   }

   return 0;
}
*/


/*

//注意：一定要把前面测试二叉树的代码全部注解掉，特别是include "linkedBinaryTree.cpp"
//测试二叉搜索树

#include "binarySearchTree.cpp"

using std::cout;
using std::endl;



int main(void)
{
   binarySearchTree<int, char> y;
   y.insert(std::pair<int, char>(1, 'a'));
   y.insert(std::pair<int, char>(6, 'c'));
   y.insert(std::pair<int, char>(4, 'b'));
   y.insert(std::pair<int, char>(8, 'd'));


   cout << "Tree size is " << y.size() << endl;
   cout << "Elements in ascending order are" << endl;
   y.ascend();

   std::pair<const int, char> *s = y.find(4);
   cout << "Search for 4 succeeds " << endl;
   cout << s->first << ' ' << s->second << endl;
   y.erase(1);
   cout << "1 deleted " << endl;
   cout << "Tree size is " << y.size() << endl;
   cout << "Elements in ascending order are" << endl;
   y.ascend();

   s = y.find(8);
   cout << "Search for 8 succeeds " << endl;
   cout << s->first << ' ' << s->second << endl;
   y.erase(4);
   cout << "4 deleted " << endl;
   cout << "Tree size is " << y.size() << endl;
   cout << "Elements in ascending order are" << endl;
   y.ascend();

   s = y.find(6);
   cout << "Search for 6 succeeds " << endl;
   cout << s->first << ' ' << s->second << endl;
   y.erase(6);
   cout << "6 deleted " << endl;
   cout << "Tree size is " << y.size() << endl;
   cout << "Elements in ascending order are" << endl;
   y.ascend();

   s = y.find(8);
  cout << "Search for 8 succeeds " << endl;
   cout << s->first << ' ' << s->second << endl;
   y.erase(8);
   cout << "8 deleted " << endl;
   cout << "Tree size is " << y.size() << endl;
   cout << "Elements in ascending order are" << endl;
   y.ascend();

}
*/

/*

//测试索引二叉搜索树

#include "indexedBinarySearchTree.cpp"

using std::cout;
using std::endl;



int main(void)
{
   indexedBinarySearchTree<int, char> y;
   y.insert(std::pair<int, char>(1, 'a'));
   y.insert(std::pair<int, char>(6, 'c'));
   y.insert(std::pair<int, char>(4, 'b'));
   y.insert(std::pair<int, char>(8, 'd'));


   cout << "Tree size is " << y.size() << endl;
   cout << "Elements in ascending order are" << endl;
   y.ascend();

   std::pair<const int, char> *s = y.find(4);
   cout << "Search for 4 succeeds " << endl;
   cout << s->first << ' ' << s->second << endl;

   s = y.get(4);

   cout << s->first << ' ' << s->second << endl;





}

*/

