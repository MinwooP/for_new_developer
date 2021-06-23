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

	int lastBID; // 가장 마지막 block의 BID
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
	blockSize = 0; // 임의로 주어짐
	rootBID = 0;
	depth = 0;
}


BTree::BTree(const char* _fileName, int _blockSize) {
	/* 
	fileName = btree.bin
	이 파일 안에 File header와 node 들이 있다. 
	file header에 block size, RootBID, Depth가 들어잇고, block size는 처음 주어진 값으로 고정,
	RootBID, Depth는 insert, delete 해줄때마다 update 해줘야 한다. 
	*/

	fileName = _fileName; // btree.bin
	blockSize = _blockSize; // 임의로 주어짐
	rootBID = 0;
	depth = 0;

	maxEntryNum = (blockSize - 4) / 8;


	if (maxEntryNum % 2 == 0) { // entry의 최대 개수가 짝수이면  
		minEntryNumLeaf = maxEntryNum / 2;
		minEntryNumNonLeaf = maxEntryNum / 2;
	}
	else { // entry의 최대 개수가 홀수이면
		minEntryNumLeaf = maxEntryNum / 2;
		minEntryNumNonLeaf = maxEntryNum / 2 + 1;
	}

	bptree_File = fopen(fileName, "wb"); 
	if (bptree_File == NULL) {
		cout << "File open error\n";
		exit(0);
	}

	// header 내용 write
	// header에 12 byte를 write	
	// block size를 4byte 만큼, 
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

	if (isTreeEmpty) { // Tree에 아무 node도 없을 때, 즉 비어있는 상태
		vector<dataEntry> tmpNode(maxEntryNum);
		// dataEntry를 담는 tmpNode -> 각 dataEntry 객체 (0, 0)으로 초기화

		tmpNode[0].setKey(key);
		tmpNode[0].setValue(value);

		lastBID++;
		rootBID = lastBID;
		// 새로운 block이 생길 것이므로 lastBID, rootBID update해줌

		fseek(bptree_File, 0, SEEK_END);
		// 파일 포인터를 맨 앞으로, 즉 header 부분 바로 뒤로

		for (int i = 0; i < maxEntryNum; i++) {
			fwrite(&tmpNode[i], 1, sizeof(tmpNode[i]), bptree_File);
		}
		// 이 for문 대신 
		// fwrite(&tmpNode, 1, sizeof(tmpNode), bptree_File); 이렇게 한번에 써주면 안되나
		fwrite(&rootBID, 1, sizeof(rootBID), bptree_File);
	}
	else {

	}
}

void BTree::print(char* outputTextFile) {
}

void BTree::search(int key, char *searchOutputFileName){ // point search

	bptree_File = fopen(fileName, "rb"); // btree.bin file은 binray mode로 read만 할 것이므로
	if (bptree_File == NULL) {
		cout << "File open error\n";
		exit(0);
	}

	// insert를 구현하지 못했으므로
	// insert 완료된 btree.bin에서 blockSize, rootBID, depth를 read해서 이를 이용해 search 한다고 가정
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

	FILE* searchOutputFile = fopen(searchOutputFileName, "a"); // 이어쓰기 형식, 텍스트파일
	if (searchOutputFile == NULL) {
		cout << "File open error\n";
		exit(0);
	}

	char char_comma = ',';
	char char_newLine = '\n';

	// ASCII 변환
	char keyResult = '0' + key;
	char valResult = '0' + val;
	
	fwrite(&keyResult, 1, sizeof(keyResult), searchOutputFile);
	fwrite(&char_comma, 1, sizeof(char_comma), searchOutputFile);
	fwrite(&valResult, 1, sizeof(valResult), searchOutputFile);
	fwrite(&char_newLine, 1, sizeof(char_newLine), searchOutputFile);

	fclose(searchOutputFile);
}

void BTree::search(int startRange, int endRange, char* rangeSearchOutputFileName) { // range search

	bptree_File = fopen(fileName, "rb"); // btree.bin file은 binray mode로 read만 할 것이므로
	if (bptree_File == NULL) {
		cout << "File open error\n";
		exit(0);
	}

	// insert를 구현하지 못했으므로
	// insert 완료된 btree.bin에서 blockSize, rootBID, depth를 read 한다고 가정
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

	FILE* rangeSearchOutputFile = fopen(rangeSearchOutputFileName, "a"); // 이어쓰기 형식, 텍스트파일
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
					// ASCII 변환
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
	char* btree_binary_file = argv[2]; // argv[1][0], argv[2]는 모든 명령어 공통으로 주어지므로
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
