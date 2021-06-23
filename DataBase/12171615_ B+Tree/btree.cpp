#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h> // for File I/O
#include <fstream>
#include <vector>
using namespace std;


class indexEntry {
private:
	int key;
	int BID;
public:
	indexEntry() {
		key = 0;
		BID = 0;
	}

	indexEntry(int _key, int _BID) {
		key = _key;
		BID = _BID;
	}
	int getKey() {
		return key;
	}

	int getBID() {
		return BID;
	}

	void setKey(int _key) {
		key = _key;
	}

	void setBID(int _BID) {
		BID = _BID;
	}
};


class dataEntry {
private:
	int key;
	int value;

public:
	dataEntry() {
		key = 0;
		value = 0;
	}

	dataEntry(int _key, int _value) {
		key = _key;
		value = _value;
	}

	int getKey() {
		return key;
	}

	int getValue() {
		return value;
	}

	void setKey(int _key) {
		key = _key;
	}

	void setValue(int _value) {
		value = _value;
	}
};


class BTree {
private:
	FILE* bptree_File;
	vector<dataEntry> leafNode;
	vector<indexEntry> nonLeafNode;

	const char* fileName;
	int blockSize, rootBID, depth;

	int lastBID; // ���� ������ block�� BID
	int maxEntryNum; 
	int minEntryNumLeaf;
	int minEntryNumNonLeaf;

public:
	BTree(const char* _fileName);
	BTree(const char* _fileName, int _blockSize);

	bool isTreeEmpty();
	bool insert(int key, int value);
	void print(char* outputTextFile);
	void search(int key, char* fileName); // point search
	void search(int startRange, int endRange, char* rangeSearchOutputFileName); // range search
};

BTree::BTree(const char* _fileName) {
	fileName = _fileName; // btree.bin
	blockSize = 0; // ���Ƿ� �־���
	rootBID = 0;
	depth = 0;
}


BTree::BTree(const char* _fileName, int _blockSize) {
	/* 
	fileName = btree.bin
	�� ���� �ȿ� File header�� node ���� �ִ�. 
	file header�� block size, RootBID, Depth�� ����հ�, block size�� ó�� �־��� ������ ����,
	RootBID, Depth�� insert, delete ���ٶ����� update ����� �Ѵ�. 
	*/

	fileName = _fileName; // btree.bin
	blockSize = _blockSize; // ���Ƿ� �־���
	rootBID = 0;
	depth = 0;

	maxEntryNum = (blockSize - 4) / 8;


	if (maxEntryNum % 2 == 0) { // entry�� �ִ� ������ ¦���̸�  
		minEntryNumLeaf = maxEntryNum / 2;
		minEntryNumNonLeaf = maxEntryNum / 2;
	}
	else { // entry�� �ִ� ������ Ȧ���̸�
		minEntryNumLeaf = maxEntryNum / 2;
		minEntryNumNonLeaf = maxEntryNum / 2 + 1;
	}

	bptree_File = fopen(fileName, "wb"); 
	if (bptree_File == NULL) {
		cout << "File open error\n";
		exit(0);
	}

	// header ���� write
	// header�� 12 byte�� write	
	// block size�� 4byte ��ŭ, 
	int Header[3];
	Header[0] = blockSize;
	Header[1] = 0;
	Header[2] = 0;
    fwrite(Header, 1, sizeof(Header), bptree_File);

	fclose(bptree_File);
}

bool BTree::isTreeEmpty() {
	return (rootBID == 0);
}


bool BTree::insert(int key, int value) {
	// btree.bin file open
	bptree_File = fopen(fileName, "ab");
	if (bptree_File == NULL) {
		cout << "File open error\n";
		exit(0);
	}

	if (isTreeEmpty) { // Tree�� �ƹ� node�� ���� ��, �� ����ִ� ����
		vector<dataEntry> tmpNode(maxEntryNum);
		// dataEntry�� ��� tmpNode -> �� dataEntry ��ü (0, 0)���� �ʱ�ȭ

		tmpNode[0].setKey(key);
		tmpNode[0].setValue(value);

		lastBID++;
		rootBID = lastBID;
		// ���ο� block�� ���� ���̹Ƿ� lastBID, rootBID update����

		fseek(bptree_File, 0, SEEK_END);
		// ���� �����͸� �� ������, �� header �κ� �ٷ� �ڷ�

		for (int i = 0; i < maxEntryNum; i++) {
			fwrite(&tmpNode[i], 1, sizeof(tmpNode[i]), bptree_File);
		}
		// �� for�� ��� 
		// fwrite(&tmpNode, 1, sizeof(tmpNode), bptree_File); �̷��� �ѹ��� ���ָ� �ȵǳ�
		fwrite(&rootBID, 1, sizeof(rootBID), bptree_File);
	}
	else {

	}
}

void BTree::print(char* outputTextFile) {
}

void BTree::search(int key, char *searchOutputFileName){ // point search

	bptree_File = fopen(fileName, "rb"); // btree.bin file�� binray mode�� read�� �� ���̹Ƿ�
	if (bptree_File == NULL) {
		cout << "File open error\n";
		exit(0);
	}

	// insert�� �������� �������Ƿ�
	// insert �Ϸ�� btree.bin���� blockSize, rootBID, depth�� read�ؼ� �̸� �̿��� search �Ѵٰ� ����
	fseek(bptree_File, 0, SEEK_SET);
	fread(&blockSize, 1, sizeof(blockSize), bptree_File);
	fread(&rootBID, 1, sizeof(rootBID), bptree_File);
	fread(&depth, 1, sizeof(depth), bptree_File);


	maxEntryNum = (blockSize - 4) / 8;

	dataEntry tmpDataEntry;
	indexEntry tmpIndexEntry;

	int BIDOfNextLevel;
	int nowOffset = 12 + ((rootBID - 1) * blockSize);
	int nowBID = rootBID;
	int nowDepth = 0;

	while (nowDepth < depth) {
		fseek(bptree_File, nowOffset, SEEK_SET);
		fread(&BIDOfNextLevel, 1, sizeof(BIDOfNextLevel), bptree_File);
		for (int i = 0; i < maxEntryNum; i++) {
			fread(&tmpIndexEntry, 1, sizeof(indexEntry), bptree_File);
			if (tmpIndexEntry.getKey() != 0 && tmpIndexEntry.getKey() <= key)
				BIDOfNextLevel = tmpIndexEntry.getBID();
			else
				break;
		}
		nowBID = BIDOfNextLevel;
		nowOffset = 12 + ((nowBID - 1) * blockSize);
		nowDepth++;
	}

	fseek(bptree_File, nowOffset, SEEK_SET);
	
	int val = 0;

	for (int i = 0; i < maxEntryNum; i++) {
		fread(&tmpDataEntry, 1, sizeof(dataEntry), bptree_File);
		if (tmpDataEntry.getKey() == key) {
			val = tmpDataEntry.getValue();
			break;
		}
	}

	fclose(bptree_File);

	FILE* searchOutputFile = fopen(searchOutputFileName, "a"); // �̾�� ����, �ؽ�Ʈ����
	if (searchOutputFile == NULL) {
		cout << "File open error\n";
		exit(0);
	}

	char char_comma = ',';
	char char_newLine = '\n';

	// ASCII ��ȯ
	char keyResult = '0' + key;
	char valResult = '0' + val;
	
	fwrite(&keyResult, 1, sizeof(keyResult), searchOutputFile);
	fwrite(&char_comma, 1, sizeof(char_comma), searchOutputFile);
	fwrite(&valResult, 1, sizeof(valResult), searchOutputFile);
	fwrite(&char_newLine, 1, sizeof(char_newLine), searchOutputFile);

	fclose(searchOutputFile);
}

void BTree::search(int startRange, int endRange, char* rangeSearchOutputFileName) { // range search

	bptree_File = fopen(fileName, "rb"); // btree.bin file�� binray mode�� read�� �� ���̹Ƿ�
	if (bptree_File == NULL) {
		cout << "File open error\n";
		exit(0);
	}

	// insert�� �������� �������Ƿ�
	// insert �Ϸ�� btree.bin���� blockSize, rootBID, depth�� read �Ѵٰ� ����
	fseek(bptree_File, 0, SEEK_SET);
	fread(&blockSize, 1, sizeof(blockSize), bptree_File);
	fread(&rootBID, 1, sizeof(rootBID), bptree_File);
	fread(&depth, 1, sizeof(depth), bptree_File);


	maxEntryNum = (blockSize - 4) / 8;

	dataEntry tmpDataEntry;
	indexEntry tmpIndexEntry;

	int BIDOfNextLevel;
	int nowOffset = 12 + ((rootBID - 1) * blockSize);
	int nowBID = rootBID;
	int nowDepth = 0;

	while (nowDepth < depth) {
		fseek(bptree_File, nowOffset, SEEK_SET);
		fread(&BIDOfNextLevel, 1, sizeof(BIDOfNextLevel), bptree_File);
		for (int i = 0; i < maxEntryNum; i++) {
			fread(&tmpIndexEntry, 1, sizeof(indexEntry), bptree_File);
			if (tmpIndexEntry.getKey() != 0 && tmpIndexEntry.getKey() <= startRange)
				BIDOfNextLevel = tmpIndexEntry.getBID();
			else
				break;
		}
		nowBID = BIDOfNextLevel;
		nowOffset = 12 + ((nowBID - 1) * blockSize);
		nowDepth++;
	}

	FILE* rangeSearchOutputFile = fopen(rangeSearchOutputFileName, "a"); // �̾�� ����, �ؽ�Ʈ����
	if (rangeSearchOutputFile == NULL) {
		cout << "File open error\n";
		exit(0);
	}

	bool findComplete = false;
	while (1)
	{
		fseek(bptree_File, nowOffset, SEEK_SET);
		for (int i = 0; i < maxEntryNum; i++) {
			fread(&tmpDataEntry, 1, sizeof(dataEntry), bptree_File);

			if (tmpDataEntry.getKey() != 0 && startRange <= tmpDataEntry.getKey()) {
				if (endRange >= tmpDataEntry.getKey()) {
					// ASCII ��ȯ
					char keyResult = '0' + tmpDataEntry.getKey();
					char valResult = '0' + tmpDataEntry.getValue();

					char char_comma = ',';
					char char_tab = '\t';

					fwrite(&keyResult, 1, sizeof(keyResult), rangeSearchOutputFile);
					fwrite(&char_comma, 1, sizeof(char_comma), rangeSearchOutputFile);
					fwrite(&valResult, 1, sizeof(valResult), rangeSearchOutputFile);
					fwrite(&char_tab, 1, sizeof(char_tab), rangeSearchOutputFile);
				}
				else {
					findComplete = true;
					break;
				}
			}
		}

			if (findComplete)
				break;

			fseek(bptree_File, nowOffset + blockSize - 4, SEEK_SET);
			fread(&nowBID, 1, sizeof(nowBID), bptree_File);

			if (nowBID != 0)
				nowOffset = 12 + (nowBID - 1) * blockSize;
			else
				break;
	}
	char char_newLine = '\n';
	fwrite(&char_newLine, 1, sizeof(char_newLine), rangeSearchOutputFile);

	fclose(rangeSearchOutputFile);
}


int main(int argc, char* argv[])
{
	char command = argv[1][0];
	char* btree_binary_file = argv[2]; // argv[1][0], argv[2]�� ��� ��ɾ� �������� �־����Ƿ�
	BTree* myBtree = new BTree(btree_binary_file);
	char buffer[20]; 

	switch (command)
	{
	case 'c':
		// create index file
		// Generates [btree binary file] with only header
	{	
		int block_size = atoi(argv[3]);
		myBtree = new BTree(btree_binary_file, block_size);
		break; 
	}

	case 'i': // insert (key, vakue)
	{
		FILE* insertionInputfile = fopen(argv[3], "r");
		if (insertionInputfile== NULL) {
			cout << "File open error\n";
			exit(0);
		}

		while (fgets(buffer, sizeof(buffer), insertionInputfile)) {
			char* ptr = strtok(buffer, ",");
			int insertKey = atoi(ptr);
			ptr = strtok(NULL, "\c\n");
			int insertValue = atoi(ptr);
			myBtree->insert(insertKey, insertValue);
		}
		
		fclose(insertionInputfile);
		break;
	 }
	
	case 's': {  // point search for search key at sample_search_input.txt
		FILE* searchInputFile = fopen(argv[3], "r");
		if (searchInputFile == NULL) {
			cout << "File open error\n";
			exit(0);
		}

		while (fgets(buffer, sizeof(buffer), searchInputFile)) {
			int searchKey = atoi(buffer);
			myBtree->search(searchKey, argv[4]);
		}

		fclose(searchInputFile);
		break; 
	}

	case 'r': // range search for search range at sample_range_search
	{
		FILE* rangeSearchInputFile = fopen(argv[3], "r");
		if (rangeSearchInputFile == NULL) {
			cout << "File open error\n";
			exit(0);
		}

		while (fgets(buffer, sizeof(buffer), rangeSearchInputFile)) {
			char* wholeRange = strtok(buffer, ",");
			int startRange = atoi(wholeRange);
			wholeRange = strtok(NULL, "\0");
			int endRange = atoi(wholeRange);
			myBtree->search(startRange, endRange, argv[4]);
		}

		fclose(rangeSearchInputFile);
		break;
	}


	case 'p':
		myBtree->print(argv[3]);
		// print B+-Tree structure to [output file]
		break;
	}

	return 0;
}
