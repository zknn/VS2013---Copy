#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
#include <stack>
using namespace std;
template <size_t M, size_t N>
class MazeG
{
protected:
	int _maze[M][N];
public:
	struct Pos
	{
		int _row;
		int _col;
	};
	MazeG(int maze[M][N])
	{
		for (size_t i = 0; i < M; ++i)
		{
			for (size_t j = 0; j < N; ++j)
			{
				_maze[i][j] = maze[i][j];
			}
		}
	}
	bool CheckAccess(Pos next)
	{
		if ((next._row >= 0 && next._col < M) && (next._col >= 0 && next._row < N)
			&& (_maze[next._row][next._col] == 0))
		{
			return true;
		}
		return false;
	}
	bool CheckShortAccess(Pos next, Pos cur)
	{
		if ((next._row >= 0 && next._row < M) && (next._col >= 0 && next._col < N))
		{
			if (_maze[next._row][next._col] == 0)
			{
				return true;
			}
			else if (_maze[next._row][next._col] == 1)
			{
				return false;
			}
			else
			{
				return _maze[next._row][next._col] > _maze[cur._row][cur._col]+1;
			}
		}
		else
		{
			return false;
		}
	}
	void GetShortPathR(Pos entry, stack<Pos>& Path, stack<Pos>& ShortPath)
	{
		Pos cur = entry;
		Path.push(cur);
		if (cur._row == M - 1)
		{
			if ((Path.size() < ShortPath.size()) || ShortPath.empty())
			{
				ShortPath = Path;
			}
			Print();
		}
		Pos next = cur;
		next._row -= 1;
		if (CheckShortAccess(next,cur))
		{
			_maze[next._row][next._col] = _maze[cur._row][cur._col] + 1;
			GetShortPathR(next, Path, ShortPath);
		}
		next = cur;
		next._col += 1;
		if (CheckShortAccess(next, cur))
		{
			_maze[next._row][next._col] = _maze[cur._row][cur._col] + 1;
			GetShortPathR(next, Path, ShortPath);
		}
		next = cur;
		next._row += 1;
		if (CheckShortAccess(next, cur))
		{
			_maze[next._row][next._col] = _maze[cur._row][cur._col] + 1;
			GetShortPathR(next, Path, ShortPath);
		}
		next = cur;
		next._col -= 1;
		if (CheckShortAccess(next, cur))
		{
			_maze[next._row][next._col] = _maze[cur._row][cur._col] + 1;
			GetShortPathR(next, Path, ShortPath);

		}
		Path.pop();
	}
	void Print()
	{
		for (size_t i = 0; i < 10; ++i)
		{
			for (size_t j = 0; j < 10; ++j)
			{
				cout << _maze[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

};

void ReadMazeS(int maze[10][10])
{
	FILE *fout = fopen("maze.txt", "r");
	assert(fout);
	for (size_t i = 0; i < 10; ++i)
	{
		for (size_t j = 0; j < 10;)
		{
			char ch = fgetc(fout);
			if (ch == '0' || ch == '1'||ch=='2')
			{
				maze[i][j] = ch - '0';
				++j;
			}
		}
	}
}

void TestS()
{
	int maze[10][10];
	ReadMazeS(maze);
	stack<MazeG<10, 10>::Pos>  Path, ShortPath;
	MazeG<10, 10> m(maze);
	MazeG<10, 10>::Pos entry;
	entry._row = 2;
	entry._col = 0;
	m.GetShortPathR(entry, Path, ShortPath);
	m.Print();
}