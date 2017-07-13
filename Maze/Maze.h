//
//
//template <size_t M,size_t N>
//class Maze
//{
//public:
//	struct Pos
//	{
//		int _row;
//		int _col;
//	};
//	Maze(int maze[M][N])
//	{
//		for (size_t i = 0; i < M; ++i)
//		{
//			for (size_t j = 0; j < N; ++j)
//			{
//				_maze[i][j] = maze[i][j];
//			}
//		}
//	}
//	bool CheckAccess(Pos next)
//	{
//		if ((next._row >= 0 && next._col < M) && (next._col >= 0 && next._row < N)
//			&& (_maze[next._row][next._col] == 0))
//		{
//			return true;
//		}
//		return false;
//	}
//	bool GetMazePath(Pos entry)
//	{
//		stack<Pos> Paths;
//		Paths.push(entry);
//		while (!Paths.empty())
//		{
//			Pos cur = Paths.top();
//			_maze[cur._row][cur._col] = 2;
//			if (cur._row == M - 1)
//			{
//				return true;
//			}
//			Pos next = cur;
//			next._row -= 1;
//			if (CheckAccess(next))
//			{
//				Paths.push(next);
//				continue;
//			}
//			next = cur;
//			next._row += 1;
//			if (CheckAccess(next))
//			{
//				Paths.push(next);
//				continue;
//			}
//			next = cur;
//			next._col -= 1;
//			if (CheckAccess(next))
//			{
//				Paths.push(next);
//				continue;
//			}
//			next = cur;
//			next._col += 1;
//			if (CheckAccess(next))
//			{
//				Paths.push(next);
//				continue;
//			}
//			Pos back = Paths.top();
//			_maze[back._row][back._col] = 3;
//			Paths.pop();
//		}
//		return false;
//	}
//
//	void Print()
//	{
//		for (size_t i = 0; i < 10; ++i)
//		{
//			for (size_t j = 0; j < 10;++j)
//			{
//				cout << _maze[i][j] << " ";
//			}
//			cout << endl;
//		}
//		cout << endl;
//	}
//protected:
//	int _maze[M][N];
//
//};
//void ReadMaze(int maze[10][10])
//{
//	FILE *fout = fopen("maze.txt", "r");
//	assert(fout);
//	for (size_t i = 0; i < 10; ++i)
//	{
//		for (size_t j = 0; j < 10;)
//		{
//			char ch = fgetc(fout);
//			if (ch == '0' || ch == '1')
//			{
//				maze[i][j] = ch - '0';
//				++j;
//			}
//		}
//	}
//}
//void Test()
//{
//	int maze[10][10];
//	ReadMaze(maze);
//	Maze<10, 10> m(maze);
//	Maze<10,10>::Pos entry;
//	entry._row = 2;
//	entry._col = 0;
//	m.GetMazePath(entry);
//	m.Print();
//}
//
