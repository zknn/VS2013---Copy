//
//template<size_t M,size_t N>
//class MazeR
//{
//public:
//	struct Pos
//	{
//		int _row;
//		int _col;
//	};
//		MazeR(int maze[M][N])
//		{
//			for (size_t i = 0; i < M; ++i)
//			{
//				for (size_t j = 0; j < N; ++j)
//				{
//					_maze[i][j] = maze[i][j];
//				}
//			}
//		}
//	bool CheckAccess(Pos next)
//	{
//		if ((next._row >= 0 && next._col < M) && (next._col >= 0 && next._row < N)
//			&& (_maze[next._row][next._col] == 0))
//		{
//			return true;
//		}
//		return false;
//	}
//	bool GetMazePathR(Pos entry)
//	{
//		Pos cur = entry;
//		Pos next = cur;
//		_maze[cur._row][cur._col] = 2;
//		if (entry._row == N - 1)
//		{
//			return true;
//		}
//		next._row -= 1;
//		if (CheckAccess(next))
//		{
//			_maze[next._row][next._col] = _maze[cur._row][cur._col] + 1;
//			if (GetMazePathR(next))
//			{
//				return true;
//			}
//		}
//		next = cur;
//		next._col += 1;
//		if (CheckAccess(next))
//		{
//			_maze[next._row][next._col] = _maze[cur._row][cur._col] + 1;
//			if (GetMazePathR(next))
//			{
//				return true;
//			}
//		}
//		next = cur;
//		next._row += 1;
//		if (CheckAccess(next))
//		{
//			_maze[next._row][next._col] = _maze[cur._row][cur._col] + 1;
//			if (GetMazePathR(next))
//			{
//				return true;
//			}
//		}
//		next = cur;
//		next._col -= 1;
//		if (CheckAccess(next))
//		{
//			_maze[next._row][next._col] = _maze[cur._row][cur._col] + 1;
//			if (GetMazePathR(next))
//			{
//				return true;
//			}
//		}
//
//		_maze[cur._row][cur._col] = 3;
//		return false;
//	}
//	void Print()
//	{
//		for (size_t i = 0; i < 10; ++i)
//		{
//			for (size_t j = 0; j < 10; ++j)
//			{
//				cout << _maze[i][j] << " ";
//			}
//			cout << endl;
//		}
//		cout << endl;
//	}
//protected:
//	int _maze[M][N];
//};
//
//void ReadMazeR(int maze[10][10])
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
//void TestR()
//{
//	int maze[10][10];
//	ReadMazeR(maze);
//	MazeR<10, 10> m(maze);
//    MazeR<10,10>::Pos entry;
//	entry._row = 2;
//	entry._col = 0;
//	bool judje = m.GetMazePathR(entry);
//	if (judje == true)
//	{
//		m.Print();
//	}
//
//}