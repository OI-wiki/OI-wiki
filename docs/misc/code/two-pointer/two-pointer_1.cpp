#include<iostream>
#include<vector>
using namespace std;
// --8<-- [start:core]
pair<bool, vector<int>> findRing(vector<int> nxt)  // nxt[i]表示i在单向链表中指向的节点（0-indexed），-1表示没有指向任何节点
{
  int fast = 0, slow = 0;
  do  // 先判断有没有环
  {
    if (nxt[fast] == -1 || nxt[nxt[fast]] == -1) {
      return make_pair(false, vector<int>());  // 没有环
    }
    fast = nxt[nxt[fast]];
    slow = nxt[slow];
  } while (fast != -1 && slow != -1 && fast != slow);
  if (fast == -1 || slow == -1) {
    return make_pair(false, vector<int>());  // 没有环
  }
  slow = 0;
  while (slow != fast)  // 再找入环位置
  {
    slow = nxt[slow];
    fast = nxt[fast];
  }
  vector<int> ring;
  do  // 最后找出整个环
  {
    ring.push_back(slow);
    slow = nxt[slow];
  } while (slow != fast);
  return make_pair(true, ring);
}
// --8<-- [end:core]
int main()
{
	int n;
	cin>>n;
	vector<int> nxt;
	nxt.resize(n);
	for(int i=0;i<n;i++)
	{
		cin>>nxt[i];
	}
	pair<bool,vector<int>> ring=findRing(nxt);
	if(ring.first)
	{
		cout<<"Ring:";
		for(int i=0;i<ring.second.size();i++)
		{
			cout<<" "<<ring.second[i];
		}
	}
	else
	{
		cout<<"No ring.\n";
	}
}
