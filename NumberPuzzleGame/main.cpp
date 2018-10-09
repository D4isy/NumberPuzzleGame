
#include <time.h>
#include <conio.h>
#include <Windows.h>

#include <iostream>

using namespace std;

class NumberPuzzle {
private:
	int SIZE = 2;
	int GAMESIZE = SIZE * SIZE;
	enum { MOVE_UP=0, MOVE_RIGHT, MOVE_DOWN, MOVE_LEFT };
	enum { CTRL_C=0x03, KEY_ESC=0x1B, KEY_UP=0x48, KEY_DOWN=0x50, KEY_LEFT=0x4B, KEY_RIGHT=0x4D };

	bool runFlag = false;

	int *puzzleMap = nullptr;
	int prevX, prevY;
	int posX, posY;

	// �� ������ ����
	void setSize(int size) {
		if (size <= 1) {
			return;
		}

		this->SIZE = size;
		setMapSize(size * size);
	}

	// �� ��ü ������ ����
	void setMapSize(int size) {
		this->GAMESIZE = size;
	}

	// prevXY ��ǥ ����
	void setPrevXY(int posX, int posY) {
		if (posX < 0) {}
		else if ((getSize() - 1) < posX) {}
		else {
			this->prevX = posX;
		}

		if (posY < 0) {}
		else if ((getSize() - 1) < posY) {}
		else {
			this->prevY = posY;
		}
	}

	// prevX ��ǥ ����
	void setPrevX(int posX) {
		if (posX < 0) {
			return;
		}
		else if ((getSize() - 1) < posX) {
			return;
		}
		this->prevX = posX;
	}

	// prevY ��ǥ ����
	void setPrevY(int posY) {
		if (posY < 0) {
			return;
		}
		else if ((getSize() - 1) < posY) {
			return;
		}
		this->prevY = posY;
	}

	// XY ��ǥ ����
	void setPosXY(int posX, int posY) {
		if (posX < 0) {}
		else if ((getSize() - 1) < posX) {}
		else {
			this->posX = posX;
		}

		if (posY < 0) {}
		else if ((getSize() - 1) < posY) {}
		else {
			this->posY = posY;
		}
	}

	// X ��ǥ ����
	void setPosX(int posX) {
		if (posX < 0) {
			return;
		}
		else if ((getSize() - 1) < posX) {
			return;
		}
		this->posX = posX;
	}

	// Y ��ǥ ����
	void setPosY(int posY) {
		if (posY < 0) {
			return;
		}
		else if ((getSize() - 1) < posY) {
			return;
		}
		this->posY = posY;
	}

	// �� �Ҵ�
	void newMap(int mapSize) {
		if (puzzleMap == nullptr) {
			puzzleMap = new int[mapSize];
			if (puzzleMap == nullptr) {
				cout << "Memory Allocation Error" << endl;
				exit(1);
				return;
			}
		}
		else {
			delete puzzleMap;
			newMap(getMapSize());
		}
	}

	// �� ���� or ���� ������ ��ȯ
	int getSize() {
		return this->SIZE;
	}

	// �� ��ü ������ ��ȯ
	int getMapSize() {
		return this->GAMESIZE;
	}

	// �� ��ȯ
	int *getMap() {
		return this->puzzleMap;
	}

	// prevX ��ǥ ��ȯ
	int getPrevX() {
		return this->prevX;
	}

	// prevY ��ǥ ��ȯ
	int getPrevY() {
		return this->prevY;
	}

	// X ��ǥ ��ȯ
	int getPosX() {
		return this->posX;
	}

	// Y ��ǥ ��ȯ
	int getPosY() {
		return this->posY;
	}

	// ���� �÷��� ��ȯ
	bool getRunFlag() {
		return this->runFlag;
	}

	// ���� ���� �÷��� ����
	void runGame() {
		this->runFlag = true;
	}

	// ���� ���� �÷��� ����
	void shutGame() {
		this->runFlag = false;
	}

	// x, y ��ǥ�� pos ��ǥ�� ��������
	int calcPos(int posX, int posY) {
		return posY * getSize() + posX;
	}

	// ���� ����
	void shuffleNumber(int *map, int size, int timesToMix) {
		// (0, 0):0 (1, 0):1, (2, 0):2
		// (0, 1):3 (1, 1):4, (2, 1):5
		// (0, 2):6 (1, 2):7, (2, 2):8

		// �� ��ü ������
		int mapSize = size * size;

		// �� ����
		int pos = mapSize - 1;		// ĳ���� ���� ��ġ ����
		int nextDir, prevDir = -1;	// ���� �������� ����

		int posXY = size;			// X ��ǥ�� Y ��ǥ�� ����
		int posX = getPosX();		// X ��ǥ
		int posY = getPosY();		// Y ��ǥ
		int prevPos, nowPos;		// ���� ��ǥ ��, ���� ��ǥ �� (���� �� �� �ʿ�)
		int value = -1;				// ��ǥ ���

		for (int i = 0; i < timesToMix; i++) {
			// ���� �ൿ ����
			nextDir = rand() % 4;

			// ���� �ൿ�� ���� �ൿ�� ������ ���� ������
			if (nextDir == prevDir) {
				i--;
				continue;
			}
			// ���� �ൿ�� ���� �ൿ�� ���� �� ���� �Ǵ� �ൿ�� �ϸ� �ȵ�
			else if ((prevDir == MOVE_UP && nextDir == MOVE_DOWN) ||
				(prevDir == MOVE_DOWN && nextDir == MOVE_UP) ||
				(prevDir == MOVE_LEFT && nextDir == MOVE_RIGHT) ||
				(prevDir == MOVE_RIGHT && nextDir == MOVE_LEFT)) {
				i--;
				continue;
			}

			// ���� �ൿ ����
			prevDir = nextDir;
			switch (nextDir) {
			case MOVE_UP:
				// Y ��ǥ�� ������ ���
				value = max(0, posY - 1);
				if (value != posY) {
					// ���� ��ǥ�� ���� ��ǥ�� ���� ���� �Ѵ�.
					prevPos = calcPos(posX, posY);
					nowPos = calcPos(posX, value);
					SWAP(map[nowPos], map[prevPos]);
					// ����� ��ġ�� ����
					posY = value;
				}
				else {
					// �� �� ���� ���� ��� �ٽ� ���� ����
					i--;
					continue;
				}
				break;
			case MOVE_DOWN:
				// Y ��ǥ�� ������ ���
				value = min(posXY - 1, posY + 1);
				if (value != posY) {
					// ���� ��ǥ�� ���� ��ǥ�� ���� ���� �Ѵ�.
					prevPos = calcPos(posX, posY);
					nowPos = calcPos(posX, value);
					SWAP(map[nowPos], map[prevPos]);
					// ����� ��ġ�� ����
					posY = value;
				}
				else {
					// �� �� ���� ���� ��� �ٽ� ���� ����
					i--;
					continue;
				}
				break;
			case MOVE_LEFT:
				// X ��ǥ�� ������ ���
				value = max(0, posX - 1);
				if (value != posX) {
					// ���� ��ǥ�� ���� ��ǥ�� ���� ���� �Ѵ�.
					prevPos = calcPos(posX, posY);
					nowPos = calcPos(value, posY);
					SWAP(map[nowPos], map[prevPos]);
					// ����� ��ġ�� ����
					posX = value;
				}
				else {
					// �� �� ���� ���� ��� �ٽ� ���� ����
					i--;
					continue;
				}
				break;
			case MOVE_RIGHT:
				// X ��ǥ�� ������ ���
				value = min(posXY - 1, posX + 1);
				if (value != posX) {
					// ���� ��ǥ�� ���� ��ǥ�� ���� ���� �Ѵ�.
					prevPos = calcPos(posX, posY);
					nowPos = calcPos(value, posY);
					SWAP(map[nowPos], map[prevPos]);
					// ����� ��ġ�� ����
					posX = value;
				}
				else {
					// �� �� ���� ���� ��� �ٽ� ���� ����
					i--;
					continue;
				}
				break;
			}
		}

		// �� ���� �� �� ĳ���� ��ġ ����
		setPrevXY(posX, posY);
		setPosXY(posX, posY);
	}

	// ���� ����Ѵ�
	void mapPrint(int *map) {
		int mapSize = getMapSize();
		int maxPos = getSize();

		for (int i = 0; i < mapSize; i++) {
			(map[i] == INT_MAX) ?
				cout << '*' << '\t' : cout << map[i] << '\t';

			if (((i + 1) % maxPos) == 0) {
				cout << endl;
			}
		}

		cout << endl;
	}

	// ���� ���
	void helpPrint() {
		cout << "w: ��, s: �Ʒ�, a: ����, d: ������" << endl;
		cout << "q: ����" << endl;
	}

	void printGame(int *map) {
		mapPrint(map);
		helpPrint();
	}

public:

	// ���� ����
	static void SWAP(int &a, int &b) {
		int temp = a;
		a = b;
		b = temp;
	}

	NumberPuzzle(int size, int timesToMix) {
		// ó�� �� ũ�� �����ϱ�
		setSize(size);
		newMap(getMapSize());

		// ĳ���� ��ǥ ����
		setPosX(size - 1);
		setPosY(size - 1);

		// �� �ʱ�ȭ
		initGame(getMap(), timesToMix);

		// ���� ���� �÷��� ����
		runGame();
	}

	~NumberPuzzle() {
		// �޸� ���� �ʼ�! (���� ����)
		delete puzzleMap;
		puzzleMap = nullptr;
	}

	// ���� �ʱ�ȭ
	void initGame(int *map, int timesToMix) {

		int i;
		int mapSize = getMapSize();
		// ������ ���� ����
		// ����: Ư���� ���� ����� ����
		for (i = 0; i < mapSize - 1; i++) {
			map[i] = i + 1;
		}

		// ĳ���� ���� ��ġ
		map[mapSize - 1] = INT_MAX;

		// �� ����
		int size = getSize();
		shuffleNumber(map, size, timesToMix);
	}

	// ���� Ű �Է� �ޱ�
	void updateGame(int *map) {
		bool specialKey = false;
		int key = _getch();

		if (key == 0x00 || key == 0xE0) {
			specialKey = true;
			key = _getch();
		}

		int value;					// SWAP�� ���� �ӽ� ��ǥ
		int size = getSize();		// X, Y �ִ� ��ǥ
		int posX = getPosX();		// X ��ǥ
		int posY = getPosY();		// Y ��ǥ
		bool canMove = false;		// �̵� ���� ����

		//cout << "[���� ��ġ] " << posX << ", " << posY << endl;

		if (specialKey == false) {
			switch (key) {
			case 'W':
			case 'w':
				// Y ��ǥ�� ������ ���
				value = max(0, posY - 1);
				// ���� ��ǥ�� ���� ��ǥ�� ���� ���� �Ѵ�.
				if (value != posY) {
					setPrevXY(posX, posY);
					setPosY(value);
					posY = value;
					canMove = true;
				}
				break;
			case 'S':
			case 's':
				// Y ��ǥ�� ������ ���
				value = min(size - 1, posY + 1);
				if (value != posY) {
					setPrevXY(posX, posY);
					setPosY(value);
					posY = value;
					canMove = true;
				}
				break;
			case 'A':
			case 'a':
				// X ��ǥ�� ������ ���
				value = max(0, posX - 1);
				if (value != posX) {
					setPrevXY(posX, posY);
					setPosX(value);
					posX = value;
					canMove = true;
				}
				break;
			case 'D':
			case 'd':
				// X ��ǥ�� ������ ���
				value = min(size - 1, posX + 1);
				if (value != posX) {
					setPrevXY(posX, posY);
					setPosX(value);
					posX = value;
					canMove = true;
				}
				break;
			case 'Q':
			case 'q':
			case KEY_ESC:
			case CTRL_C:
				// ���� ���� �÷��� ����
				shutGame();
				break;
			}
		}
		else {
			switch (key) {
			case KEY_UP:
				// Y ��ǥ�� ������ ���
				value = max(0, posY - 1);
				//printf("value: %d, posY: %d\n", value, posY);
				if (value != posY) {
					setPrevXY(posX, posY);
					setPosY(value);
					posY = value;
					canMove = true;
				}
				break;
			case KEY_DOWN:
				// Y ��ǥ�� ������ ���
				value = min(size - 1, posY + 1);
				if (value != posY) {
					setPrevXY(posX, posY);
					setPosY(value);
					posY = value;
					canMove = true;
				}
				break;
			case KEY_LEFT:
				// X ��ǥ�� ������ ���
				value = max(0, posX - 1);
				if (value != posX) {
					setPrevXY(posX, posY);
					setPosX(value);
					posX = value;
					canMove = true;
				}
				break;
			case KEY_RIGHT:
				// X ��ǥ�� ������ ���
				value = min(size - 1, posX + 1);
				if (value != posX) {
					setPrevXY(posX, posY);
					setPosX(value);
					posX = value;
					canMove = true;
				}
				break;
			}
		}

		//cout << "[canMove] " << canMove << endl;
		//cout << "[�̵��� ��ġ] " << posX << ", " << posY << endl;
		if (canMove == true) {
			// ���� ��ǥ�� ���� ��ǥ�� ����� ������
			int prevPos = calcPos(getPrevX(), getPrevY());
			int nowPos = calcPos(getPosX(), getPosY());

			//cout << "[�̵��� ��ġ] " << nowPos << " to " << prevPos << endl;

			// �� ��ġ�� �̵� ��Ŵ
			SWAP(map[prevPos], map[nowPos]);
		}

		// ���������� ���� �������� Ȯ��
		int count = 0;
		int mapSize = getMapSize();
		for (int i = 0; i < mapSize - 1; i++, count++) {
			if (map[i] != (i + 1)) {
				break;
			}
		}

		if (count == (mapSize-1)) {
			system("cls");
			cout << "Congratulation!" << endl;
			cout << "Complete Game..." << endl;
			cout << "Bye~" << endl;
			_getch();
			shutGame();
		}
	}

	void playGame() {
		int *map = getMap();
		
		while (getRunFlag()) {
			printGame(map);
			updateGame(map);
			system("cls");
		}
	}
};

int main(void)
{
	// ������ ���� ������ �ʿ�
	srand((unsigned int)time(NULL));

	int count = 3;

	while (true) {
		NumberPuzzle game = NumberPuzzle(count, 10000);
		game.playGame();

		count++;
	}
	return 0;
}