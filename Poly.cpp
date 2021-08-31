//!152120181001---Yakupcan ERGEN
//!152120171067---Furkan Ziya ILIKKAN
#include <stdio.h>
#include<string>
#include<sstream>
#include "Poly.h"
#include <iostream>
#include<math.h>
using namespace std;
//-------------------------------------------------
// Creates a polynomial from an expression.
// Returns a pointer to the first PolyNode in the list (head of the list)
//
// Expression will be of the following sort:
// Ex1: 2.3x^4 + 5x^3 - 2.64x - 4
// Ex2: -4.555x^10 - 45.44
// Ex3: x^6 + 2x^4 - x^3 - 6.3x + 4.223 
// Ex4: 34
// Ex5: -x+1
// Ex6: -3x^4    +   4x
// Ex7: -2x  - 5
//
PolyNode* CreatePoly(char* expr) {
	 string tempStr=expr,termStr,cofStr,expStr;
	 int powerNumber=1,begin=0;
	 double coff=1;
	 PolyNode *head=NULL;
	 PolyNode * temp = NULL;
	 tempStr.erase(remove(tempStr.begin(), tempStr.end(), ' '), tempStr.end());
	 tempStr += "+";
	 for (int i = 1; i < tempStr.length(); i++)
	 {
		   if (tempStr[i] == '+' || tempStr[i] == '-')
		   {
			 termStr = tempStr.substr(begin, i-begin);
			 begin = i;
			 stringstream ss(termStr);
			 getline(ss, cofStr, 'x');
			 if (cofStr.empty())
			 {
				 coff = 1;
			 }
			 else if (cofStr[0] == '+'&&cofStr.length()==1)
			 {
				 coff = 1;
			 }
			 else if (cofStr[0] == '-' && cofStr.length() == 1)
			 {
				 coff = -1;
			 }
			 else
			 {
				 coff = stod(cofStr);
			 }
			 if (termStr[termStr.length() - 1] == 'x')
			 {
				 powerNumber = 1;
			 }
			 else if(termStr.find("x")==-1)
			 {
				 powerNumber = 0;
				 coff = stod(cofStr);
			 }
			 else
			 {
				 expStr = termStr.substr(termStr.find('^') + 1);
				 powerNumber = stod(expStr);
			 }
			 head=AddNode(head, coff, powerNumber);
		 }
	 }
	return head;
} //end-CreatePoly

/// -------------------------------------------------
/// Walk over the poly nodes & delete them
///
void DeletePoly(PolyNode* poly) {
	PolyNode* p = poly;
	while (p != NULL)
	{
		poly = p->next;
		delete p;
		p = poly;
	}
} // end-DeletePoly

//-------------------------------------------------
// Adds a node (coefficient, exponent) to poly. If there already 
// is a node with the same exponent, then you simply add the coefficient
// to the existing coefficient. If not, you add a new node to polynomial
// Returns a pointer to the possibly new head of the polynomial.
//
PolyNode* AddNode(PolyNode* head, double coef, int exp) {
	PolyNode *newNode=new PolyNode;
	newNode->coef = coef;
	newNode->exp = exp;
	newNode->next = NULL;
	bool control = 0;
	PolyNode* p = head;
	PolyNode* q = NULL;
	while (p != NULL)
	{
		if (p->exp == exp)
		{
			control = 1;
			p->coef += coef;
		}
		p = p->next;
	}
	if (control != 1)
	{
		p = head;
		while (p != NULL)
		{
			q = p;
			p = p->next;
		}
		if (q == NULL)
		{
			head = newNode;
		}
		else
		{
			q->next = newNode;
		}
	}
	return head;
} // end-AddNode
//-------------------------------------------------
// Adds two polynomials and returns a new polynomial that contains the result
// Computes: poly3 = poly1 + poly2 and returns poly3
//
PolyNode* Add(PolyNode* poly1, PolyNode* poly2) {
	PolyNode* p = poly1;
	PolyNode* q = poly2;
	PolyNode* poly3 = NULL;
	PolyNode* s = poly3;
	bool control = 0;
	while (p != NULL)
	{
		q = poly2;
		while (q != NULL)
		{
			control = 1;
			if (q->exp == p->exp)
			{
				poly3 = AddNode(poly3, (p->coef) + (q->coef), p->exp);
				break;
			}
			control = 0;
			q = q->next;
		}
		if (control == 0)
		{
			poly3 = AddNode(poly3, p->coef, p->exp);
		}
		p = p->next;
	}
	q = poly2;
	while (q != NULL)
	{
		control = 1;
		p = poly1;
		while (p != NULL)
		{
			if (q->exp == p->exp)
			{
				control = 1;
				break;
			}
			control = 0;
			p = p->next;
		}
		if (control == 0)
		{
			poly3 = AddNode(poly3, q->coef, q->exp);
		}
		q = q->next;
	}
	return poly3;
}
//end-Add

//-------------------------------------------------
// Subtracts poly2 from poly1 and returns the resulting polynomial
// Computes: poly3 = poly1 - poly2 and returns poly3
//
PolyNode* Subtract(PolyNode* poly1, PolyNode* poly2) {
	PolyNode* p = poly1;
	PolyNode* q = poly2;
	PolyNode* poly3 = NULL;
	PolyNode* s = poly3;
	bool control = 0;
	while (p != NULL)
	{
		q = poly2;
		while (q != NULL)
		{
			control = 1;
			if (q->exp == p->exp)
			{
				poly3 = AddNode(poly3, (p->coef)-(q->coef), p->exp);
				break;
			}
			control = 0;
			q = q->next;
		}
		if (control == 0)
		{
			poly3 = AddNode(poly3, p->coef, p->exp);
		}
		p = p->next;
	}
	q = poly2;
	while (q != NULL)
	{
		control = 1;
		p = poly1;
		while (p != NULL)
		{
			if (q->exp == p->exp)
			{
				control = 1;
				break;
			}
			control = 0;
			p = p->next;
		}
		if (control == 0)
		{
			poly3 = AddNode(poly3, -q->coef, q->exp);
		}
		q = q->next;
	}
	return poly3;
} //end-Substract

//-------------------------------------------------
// Multiplies poly1 and poly2 and returns the resulting polynomial
// Computes: poly3 = poly1 * poly2 and returns poly3
//
PolyNode* Multiply(PolyNode* poly1, PolyNode* poly2) {
	PolyNode* p = poly1;
	PolyNode* q = poly2;
	PolyNode* poly3 = NULL;
	//PolyNode* s = poly3;
	bool control = 0;
	while (p != NULL)
	{
		q = poly2;
		while (q != NULL)
		{
			poly3=AddNode(poly3, (p->coef) * (q->coef), p->exp + q->exp);
			q = q->next;
		}
		p = p->next;
	}
	return poly3;
} //end-Multiply

//-------------------------------------------------
// Evaluates the polynomial at a particular "x" value and returns the result
//
double Evaluate(PolyNode* poly, double x) {
	PolyNode* p = poly;
	double sum = 0.0;
	while (p != NULL)
	{
		sum+=(p->coef)*(pow(x, p->exp));
		p = p -> next;
	}
	return sum;
} //end-Evaluate

//-------------------------------------------------
// Computes the derivative of the polynomial and returns it
// Ex: poly(x) = 3x^4 - 2x + 1-->Derivative(poly) = 12x^3 - 2
//
PolyNode* Derivative(PolyNode* poly) {
	PolyNode* p = poly;
	while (p != NULL)
	{
		p->coef *= p->exp;
		if (p->coef == 0)
		{
			p->exp = 0;
		}
		else
		{
			p->exp -= 1;
		}
		p = p->next;
	}
	return poly;
} //end-Derivative

//-------------------------------------------------
// Plots the polynomial in the range [x1, x2].
// -39<=x1<x2<=39
// -12<=y<=12
// On the middle of the screen you gotta have x & y axis plotted
// During evaluation, if "y" value does not fit on the screen,
// then just skip it. Otherwise put a '*' char depicting the curve
//
void Plot(PolyNode* poly, int x1, int x2) {
	double y=0;
	if (x1 > x2)
	{
		int temp=x1;
		x1 = x2;
		x2 = temp;
	}
	for (int i = 12; i >= -12; i--)//y
	{
		for (int j = x1; j <=x2; j++)//x
		{
			y = Evaluate(poly, j);
			int temp=round(y);
		    if(i==0&&j%5==0|| j== 0 && i % 5 == 0)
			{
				cout << "+";
			}
			else if (i == 0 && j % 5 != 0)
			{
				cout << "-";
			}
			else if (j == 0 && i % 5 != 0)
			{
				cout << "|";
			}
			else if (temp<=12 && temp>=-12 &&temp == i)
			{
				cout << "*";
			}
			else
			{
				cout <<" ";
			}
		}
		cout << endl;
	}
} //end-Plot
