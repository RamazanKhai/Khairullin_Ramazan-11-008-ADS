#include <iostream>
#include <stack>
using namespace std;

void kernels(int quantity, stack<int> &from, stack<int> &to, stack<int> &buf_peg)
{
	if (quantity != 0)
	{
		kernels(quantity - 1, from, buf_peg, to);
        
        int topElem = from.top();
        from.pop();
        to.push(topElem);
 
		kernels(quantity - 1, buf_peg, to, from);
	}
}

int main()
{
    stack<int> peg1;
    for (int i = 8; i >= 1; i--)
    {
        peg1.push(i);
    }
    stack<int> peg2;
    stack<int> peg3;

    kernels(8, peg1, peg2, peg3);
    while (!peg2.empty())
    {
        cout << peg2.top() <<' ';
        peg2.pop();
    }

    return 0;
}
