//============================================================================
// Name        : curr.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "currency.h"
#include "currency2.h"
#include "MemoryCell.cpp"

int main() {

//测试第一种实现
	currency g, h(Plus,3, 50), j,i;//编译器生成了对象g，调用了哪个构造函数  -->默认的构造函数
	currency y = h;//调用了复制构造函数
	currency x(y);//   -->该函数并未定义，在currency.cpp中已经被注释掉了，但会调用默认的复制构造函数
	x.output();//调用了复制构造函数，自己定义了复制构造函数没有？

	float a;
	a = y;//为什么能赋值？ -->currency.cpp定义了operator float()类型转换函数
	cout <<a<<endl;


	g.setValue(Minus, 2, 25);
	j = h.add(g);//j= h+g=1.25
	j=h.increment(g); //j,h = h+g=1.25
	i = j.add(g).add(h); //i = j+g+h=0.25
	i = j.increment(g).increment(h);//i,j=j+g+h=0.25

	i.output();
	j.output();
	g.output();
	h.output();

	g = h;//为什么能操作？没定义operator=，但是为什么能操作？  -->如果没有定义operator=操作，编译器会提供一个默认的operator=操作。
	      //对于一个类，编译器会提供非无用的operator=操作
	g.output();

	//测试catch
	currency *tmp;
	try{
		tmp = new currency(Plus,3,110);
		delete tmp;
	}
	catch(bad_alloc &e){
		cout <<e.what()<<endl;
	}
		//catch(...) {
	catch(invalid_argument &e){
		cout <<e.what()<<endl;
	}
/*
//测试第二种实现

	currency2 g2, h2(currency2::plus,3, 50), j2,i2;
	currency2 y2 = h2;
	float a2;
	a2 = y2;
	cout <<a2<<endl;

	g2.setValue(currency2::minus, 2, 25);
	j2 = h2.add(g2);//j= h+g=1.25
	j2=h2.increment(g2); //j,h = h+g=1.25
	i2 = j2.add(g2).add(h2); //i = j+g+h=0.25
	i2 = j2.increment(g2).increment(h2);//i,j=j+g+h=0.25

	i2.output();
	j2.output();
	g2.output();
	h2.output();

	//测试catch
	currency2 *tmp2;
	try{
		tmp2 = new currency2(currency2::plus,3,110);
		delete tmp2;
	}
	catch(bad_alloc &e){
		cout <<e.what()<<endl;
	}
		//catch(...) {
	catch(invalid_argument &e){
		cout <<e.what()<<endl;
	}

	//测试opertor=
	currency2 x;
	x = 1199;
	cout << "x="<<x<<endl;
	x = -1199;
	cout << "x="<<x<<endl;

	x = 11.994;
	cout << "x="<<x<<endl;
	x = 11.995;
	cout << "x="<<x<<endl;

	x = -11.994;
	cout << "x="<<x<<endl;
	x = -11.995;
	cout << "x="<<x<<endl;


//测试cell
  	MemoryCell<int> m(1);
	MemoryCell<double> m2(3.14);
	cout << m.read()<< "  " << m2.read()<<endl;
	m.write(10);
	m2.write(13.14);
	cout << m.read()<< "  " << m2.read()<<endl;
*/
	return 0;
}




