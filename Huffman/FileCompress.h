#include <string>
#include <assert.h>
#include <algorithm>
#include "HuffmanTree.h"
typedef long long  LongType;

struct CharInfo
{
	char _ch;
	LongType _count;
	string _code;
	CharInfo(LongType count = 0)
		:_ch(0)
		, _count(count)
		, _code("")
	{}
	bool operator != (const CharInfo& infos)const
	{
		return _count != infos._count;
	}
	CharInfo operator + (const CharInfo& infos)const
	{
		CharInfo ret;
		ret._count = _count + infos._count;
		return ret;
	}
	bool operator<(const CharInfo& infos) const
	{
		return _count < infos._count;
	}
};

class FileCompress
{
	typedef HuffmanTreeNode<CharInfo> Node;
public:
	//建立一个内部类，保存节点信息
	struct _HuffmanCharInfo
	{
		char _ch;
		LongType _count;
	};
	FileCompress()
	{
		for (size_t i = 0; i < 256; ++i)
		{
			_infos[i]._ch = (unsigned char)i;
			_infos[i]._count = 0;
		}
	}
	 void Compress(const char* filename)
	 {
		 assert(filename);
		 FILE* fout = fopen(filename, "r");
		 assert(fout);
		 //统计字符出现的次数
		 int chcount1=0;
		 char ch = fgetc(fout);
		 while (ch != EOF)
		 {
			 _infos[(unsigned char)ch]._count++;
			 ch = fgetc(fout);
			 chcount1++;
		 }
		 cout << "原文件共有字符数为：" << chcount1 << endl;
		 //构建哈夫曼树
		 CharInfo invalid;
		 invalid._count = 0;
		 HuffmanTree<CharInfo> tree(_infos, 256, invalid);
		 //哈夫曼编码
		 string code;
		 GenerateHuffman(tree.GetRoot(),code);
		 //写入字符信息
		 string compressfile = filename;
		 compressfile += ".Huffman";
		 FILE* fin = fopen(compressfile.c_str(), "wb");
		 for (size_t i = 0; i < 256; ++i)
		 {
			 if (_infos[i]._count)
			 {
				 _HuffmanCharInfo info;
				 info._ch = _infos[i]._ch;
				 info._count = _infos[i]._count;
				 fwrite(&info, sizeof(_HuffmanCharInfo), 1, fin);
			 }
		 }
		 _HuffmanCharInfo info;
		 info._count = -1;
		 fwrite(&info, sizeof(_HuffmanCharInfo), 1, fin);
		 //压缩

		 char value = 0;
		 int count = 1;
		 fseek(fout, 0, SEEK_SET);
		 int chcount = 0;
		 ch = fgetc(fout);
		 while (ch != EOF)
		 {
			 string& code = _infos[(unsigned char)ch]._code;
			 for (size_t i = 0; i < code.size(); ++i)
			 {
				 value <<= 1;
				 if (code[i] == '1')
				 {
					 value |= 1;
				 }
				 else
				 {
					 value |= 0;
				 } 
				 ++count;
				 if (count == 9)
				 {
					 fputc(value, fin);
					 value = 0;
					 count = 1;
				 }
			 }
			 ch = fgetc(fout);
			 chcount++;
		 }
		 cout << "压缩字符数为：" << chcount << endl;
		 if (count != 1)
		 {
			 value <<= (9 - count);
			 fputc(value, fin);
		 }
		 fclose(fout);
		 fclose(fin);
	 }
	 void GenerateHuffman(Node* root, string code)
	 {
		 if (root == NULL)
		 {
			 return;
		 }
		 if (root->_left == NULL&&root->_right == NULL)
		 {
			 _infos[(unsigned char)root->_w._ch]._code = code;
			 return;
		 }
		 GenerateHuffman(root->_left, code + '0');
		 GenerateHuffman(root->_right, code + '1');
	 }
	 void  GenerateHuffman(Node* root)
	 {
		 string& code = _infos[(unsigned char)root->_w._ch]._code;
		 if (root == NULL)
			 return;
		 if (root->_left == NULL&&root->_right == NULL)
		 {
			 Node* cur = root;
			 Node* parent = cur->_parent;
			 while (parent)
			 {
				 if (parent->_left == cur)
				 {
					 code.push_back('0');
				 }
				 else
				 {
					 code.push_back('1');
				 }
				 cur = parent;
				 parent = cur->_parent;
			 }
			 reverse(code.begin(), code.end());
			 return;
		 }
		 GenerateHuffman(root->_left);
		 GenerateHuffman(root->_right);
	 }
	 void Uncompress(const char* filename)
	 {
		 assert(filename);

		 string uncompressfile = filename;
		 size_t pos = uncompressfile.rfind('.');
		 assert(pos != string::npos);
		 uncompressfile = uncompressfile.substr(0, pos);
		 uncompressfile += ".unhuffman";
		 FILE* fin = fopen(uncompressfile.c_str(), "wb");
		 assert(fin);
		 FILE* fout = fopen(filename, "rb");
		// 读取字符信息
		 int p;
		 while (1)
		 {
			 _HuffmanCharInfo info;
			 size_t size = fread(&info, sizeof(_HuffmanCharInfo), 1, fout);
			 p = size;
			 assert(size=sizeof(_HuffmanCharInfo));
			 if (info._count>0)
			 {
				 _infos[(unsigned char)info._ch]._ch = info._ch;
				 _infos[(unsigned char)info._ch]._count = info._count;
			 }
			 else
			 {
				 break;
			 }
		 } 
		 //重建哈夫曼树
		 CharInfo invalid;
		invalid._count = 0;
		HuffmanTree<CharInfo> tree(_infos, 256, invalid);
		 Node* root = tree.GetRoot();
		 LongType charcount = root->_w._count;
		 Node* cur = root;
		// 解压缩
		 int chcount = 0;
		 char value = fgetc(fout);
		 while (value !=feof(fout))
		 {
			 for (int pos = 7; pos >= 0; --pos)
			 {
				 if (value & (1 << pos))
				 {
					 cur = cur->_right;
				 }
				 else
				 {
					 cur = cur->_left;
				 }
				 if (cur->_left == NULL&&cur->_right == NULL)
				 {
					 fputc(cur->_w._ch, fin);
					 cur = root;
					 if (--charcount == 0)
					 {
						 break;
					 }
				 }
			 }
			 value = fgetc(fout);
			 chcount++;
		 }
		 cout << "解压字符数为："<<chcount << endl;
		 fclose(fout);
		 fclose(fin);
	 }
protected:
	CharInfo _infos[256];
};

void test()
{
	FileCompress fc;
	fc.Compress("Input.txt");
	//fc.Uncompress("Input.txt.Huffman");
}
void testUnCompress()
{
	FileCompress fc;
	fc.Uncompress("Input.txt.Huffman");
}

